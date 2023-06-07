// #include "Lab4.h"
// #include <queue.h>
// int rs = PIN22, enable = PIN23, d0 = PIN24, d1 = PIN25, d2 = PIN26, d3 = PIN27,
// d4 = PIN28, d5 = PIN29, d6 = PIN30, d7 = PIN31;
// LiquidCrystal lcd(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7);

// int LED1 = PIN12, LED2 = PIN11, LED3 = PIN10, LED4 = PIN9, LED5 = PIN8;

// int UPBTN = PIN7, DWNBTN = PIN6, SCTBTN = PIN5;

// int index;

// void setup() {
//     lcd.begin(16,2);
//     lcd.clear();

//     pinMode(LED1, OUTPUT);
//     pinMode(LED2, OUTPUT);
//     pinMode(LED3, OUTPUT);
//     pinMode(LED4, OUTPUT);
//     pinMode(LED5, OUTPUT);

//     pinMode(UPBTN, INPUT_PULLUP);
//     pinMode(DWNBTN, INPUT_PULLUP);
//     pinMode(SCTBTN, INPUT_PULLUP);
//     index = 0;


//     int numWords = 0;
//     char* selected[5];
//     int leds_to_turn_on[5] = {LED1, LED2, LED3, LED4, LED5};
//     while (numWords < 5) {

//         delay(50);
//         int udvalue = analogRead(A0);
//         int lrvalue = analogRead(A1);
//         // int up = digitalRead(UPBTN);
//         // int down = digitalRead(DWNBTN);
//         // int select = digitalRead(SCTBTN);

//         int up = udvalue > 980 ? 1 : 0;
//         int down = udvalue < 75 ? 1 : 0;
//         int select = lrvalue > 980 ? 1 : 0;

//         delay(50);

//         if (index > 90) index = 0;
//         else if (index < 0) index = 90;

//         delay(50);

//         lcd.setCursor(0,0);
//         lcd.print(adjectives_lcd[index]);
//         lcd.setCursor(0,1);
//         if (index + 1 > 90) {
//             lcd.print(adjectives_lcd[0]);
//         } else {
//             lcd.print(adjectives_lcd[index + 1]);
//         }
//         lcd.setCursor(14, 0);
//         lcd.print("<-");

//         delay(100);

//         for (int i = numWords; i < 5; i++) {
//             digitalWrite(leds_to_turn_on[i], HIGH);
//         }

//         delay(50);

//         if (select) {
//             selected[numWords++] = adjectives[index];
//             for (int i = 0; i < numWords; i++) {
//                 digitalWrite(leds_to_turn_on[i], LOW);
//             }
//         } else if (up && !down) {
//             index += 1;
//         } else if (down && !up) {
//             index -= 1;
//         }
//         delay(50);
//         up = down = select = udvalue = lrvalue = 0;
//         delay(50);
//     }
//     char message[100];
//     snprintf(message, 100, "You are %sand %sand %sand %sand %s", selected[0], selected[1], selected[2],
//                                                         selected[3], selected[4]);
    
//     char message_split[7][17] = {"                ","                ","                ",
//     "                ","                ","                ","                "};
//     for (int i = 0; i < 7; i++) {
//         for (int j = 0; j < 16; j++) {
//             if (i*16 + j > 100) {
//                 char* space = " ";
//                 message_split[i][j] = *space;
//             } else {
//                 message_split[i][j] = message[i*16 + j];
//             }
//         }
//         message_split[i][16] = '\0';
//     }
//     lcd.clear();        
//     lcd.setCursor(15, 0);
//     for (int i = 0; i < 6; i++) {
//         lcd.clear();
//         lcd.setCursor(0,0);
//         lcd.print(message_split[i]);
//         lcd.setCursor(0, 1);
//         lcd.print(message_split[i + 1]);
//         delay(1000);
//     }
//     lcd.clear();
    



//     delay(1000);
// }

// void loop() { 

// }