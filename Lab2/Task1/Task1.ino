#define REDLED 47
#define GREENLED 48
#define BLUELED 49

void setup() {
  // put your setup code here, to run once:
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(BLUELED, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(REDLED, HIGH);
  delay(333);
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, HIGH);
  delay(333);
  digitalWrite(GREENLED, LOW);
  digitalWrite(BLUELED, HIGH);
  delay(333);
  digitalWrite(BLUELED, LOW);

}
