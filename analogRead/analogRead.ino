#define POT 25
void setup() {
  // put your setup code here, to run once:
  //Never do pinMode input to any pin needed to be read with analogRead
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(analogRead(POT));
}
