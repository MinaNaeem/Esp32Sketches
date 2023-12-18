#define Motor1en1 13 
#define Motor1en2 12

void setup() {
  // put your setup code here, to run once:
pinMode(Motor1en1, OUTPUT);
pinMode(Motor1en2, OUTPUT);

}

void loop() 
{
  // put your main code here, to run repeatedly:

digitalWrite(Motor1en1, HIGH);
digitalWrite(Motor1en2, LOW);
delay(2000);
digitalWrite(Motor1en1, LOW);
digitalWrite(Motor1en2, LOW);
delay(2000);
digitalWrite(Motor1en1, LOW);
digitalWrite(Motor1en2, HIGH);
delay(2000);
digitalWrite(Motor1en1, LOW);
digitalWrite(Motor1en2, LOW);
delay(2000);
}
