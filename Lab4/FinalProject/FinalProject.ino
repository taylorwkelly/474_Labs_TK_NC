#include "Lab4.h"
#include <queue.h>


void LEDControl(void*);
void LCDControl(void*);
void ScrollHandler(void*);
void SelectHandler(void*);


int rs = PIN22, enable = PIN23, d0 = PIN24, d1 = PIN25, d2 = PIN26, d3 = PIN27,
d4 = PIN28, d5 = PIN29, d6 = PIN30, d7 = PIN31;
LiquidCrystal lcd(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7);

int LED1 = PIN12, LED2 = PIN11, LED3 = PIN10, LED4 = PIN9, LED5 = PIN8;

QueueHandle_t scrollQueue, lcdQueue, ledQueue;

void setup() {
    scrollQueue = xQueueCreate(2, sizeof(int));
    lcdQueue = xQueueCreate(2, sizeof(int));
    ledQueue = xQueueCreate(2, sizeof(int));
    int joyVal = 500;
    int ledVal = 0;
    xQueueSendToBack(ledQueue, &ledVal, 0);
    xQueueSendToBack(lcdQueue, &joyVal, 0);
    xQueueSendToBack(scrollQueue, &joyVal, 0);
    lcd.begin(16,2);
    lcd.clear();

    int led_pins[5] = {LED1, LED2, LED3, LED4, LED5};
    for (int pin = 0; pin < 5; pin++) 
        pinMode(led_pins[pin], OUTPUT);

    xTaskCreate(
        LEDControl,
        "LED Controller",
        128,
        NULL,
        0,
        NULL
    );

    xTaskCreate(
        ScrollHandler,
        "X Value Reader",
        128,
        NULL,
        3,
        NULL
    );

    xTaskCreate(
        SelectHandler,
        "Y Value Reader",
        128,
        NULL,
        3,
        NULL
    );

    xTaskCreate(
        LCDControl,
        "LCD Controller",
        1024,
        NULL,
        0,
        NULL
    );
    
    vTaskStartScheduler();
}
void loop() { /*no looping?*/  }


String sendToPython(char* selections[5]) {
    Serial.begin(19200);

    while (!Serial) {
        ;
    }

    Serial.write("Requesting Pair\n");

    while (Serial.available() > 0) {
        String str = Serial.readStringUntil('\n');
        if (str == "Paired") break;
    }
    
    
    String inbytes = "";
    char message[100];
    snprintf(message, 100, "%s %s %s %s %s\n", selections[0],
    selections[1], selections[2], selections[3], selections[4]);

    Serial.write(message);

    while(Serial.available() > 0) {
        inbytes = Serial.readStringUntil('\n');
        if (inbytes != "") break;
    }
    Serial.end();
    return inbytes;
}

void LEDControl(void* pvParameters) {
    int num_selected = 0;
    int leds[5] = {LED1, LED2, LED3, LED4, LED5};
    int value;
    for (;;) {
        while (num_selected < 5) {
            xQueueReceive(ledQueue, &value, 0);
            num_selected += value > 980 ? 1 : 0;
            for (int led = 0; led < 5; led++) {
                if (num_selected > led) {
                    digitalWrite(leds[led], LOW);
                } else {
                    digitalWrite(leds[led], HIGH);
                }
            }
            value = 0;
            vTaskDelay(50 / portTICK_PERIOD_MS);
        }
    }
}

void LCDControl(void* pvParameters) {
    int index = 0, num_selected = 0;
    char* selected[5];
    int value;
    int select;
    int displayed = 0;
    for (;;) {
        while (num_selected < 5) {
            xQueueReceive(scrollQueue, &value, 1);
            xQueueReceive(lcdQueue, &select, 1);
            if (select > 980) {
                selected[num_selected] = adjectives[index];
                num_selected++;
            }
            int up = value > 980 ? 1 : 0;
            int down = value < 95 ? 1 : 0;

            if (up && !down) {
                index++;
            } else if (down && !up) {
                index--;
            }

            if (index > 90) index = 0;
            else if (index < 0) index = 90;

            lcd.setCursor(0,0);
            lcd.print(adjectives_lcd[index]);
            lcd.setCursor(0,1);
            lcd.print(adjectives_lcd[(index + 1 > 90) ? 0 : index + 1]);
            lcd.setCursor(14, 0);
            lcd.print("<");
            lcd.setCursor(15, 0);
            lcd.blink();
            vTaskDelay(50 / portTICK_PERIOD_MS);
            value = 500;
            select = 0;
        }
        if (displayed == 0) {
            lcd.noBlink();
            // char message[100];
            // snprintf(message, 100, "You are %sand %sand %sand %sand %s", selected[0], selected[1], selected[2],
            //                                                 selected[3], selected[4]);
            String message = sendToPython(selected);
            int len = 0;
            char* temp = message.begin();
            while (*temp != '\0') {
                len++;
                temp += 1;
            }
            int layers = (len / 16) + 1;
            char message_split[layers][17];
            for (int i = 0; i < layers; i++) {
                for (int j = 0; j < 16; j++) {
                    if (i*16 + j > 100) {
                        char* space = " ";
                        message_split[i][j] = *space;
                    } else {
                        message_split[i][j] = message[i*16 + j];
                    }
                }
                message_split[i][16] = '\0';
            }
            lcd.clear();        
            lcd.setCursor(15, 0);
            for (int i = 0; i < layers - 1; i++) {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print(message_split[i]);
                lcd.setCursor(0, 1);
                lcd.print(message_split[i + 1]);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
            lcd.clear();
            }
            displayed = 1;
    }
}

void ScrollHandler(void* pvParameters) {
    int value;
    int wait = 0;
    for (;;) {
        value = analogRead(XVALUEPIN);
        if ((value > 980 || value < 95) && !wait) {
            xQueueSendToBack(scrollQueue, &value, 1);
            wait = 1;
        } else {
            vTaskDelay(200 / portTICK_PERIOD_MS);
            wait = 0;
        }
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}

void SelectHandler(void* pvParameters) {
    int value;
    int wait = 0;
    for (;;) {
        value = analogRead(YVALUEPIN);
        if (value > 980 && !wait) {
            xQueueSendToBack(ledQueue, &value, 1);
            xQueueSendToBack(lcdQueue, &value, 1);
            wait = 1;
        } else {
            vTaskDelay(200 / portTICK_PERIOD_MS);
            wait = 0;
        }
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}

