#include <ESP32Servo.h>
#define servopin 26
Servo myservo;
void setup() {
  // put your setup code here, to run once:
myservo.attach(servopin);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
for(int pos = 0; pos <= 180 ; pos ++)
{
myservo.write(pos);
Serial.println(pos);
delay(50);
}
for(int pos = 180; pos >=0 ; pos --)
{
myservo.write(pos);
Serial.println(pos);
delay(50);
}
}
