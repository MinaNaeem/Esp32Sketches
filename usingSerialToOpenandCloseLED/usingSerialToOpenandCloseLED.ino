void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

if (Serial.available())
{
  char a = Serial.read();
  if(a == '1')
    {
      digitalWrite(2, HIGH);
      Serial.println("LED is HIGH");
    }
  else if(a == '0')
    {
      digitalWrite(2,LOW);
      Serial.println("LED is LOW");
    }
}
}
