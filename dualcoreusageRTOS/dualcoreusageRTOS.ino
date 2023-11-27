#include <ESP32Servo.h>
#define servopin 26
#define Red 25
#define Blue 27

Servo myservo;
int count1 = 0;
int count2 = 0;

void ServoTask(void * parameters)
{
  for(;;)  
{
for(int pos = 0; pos <= 180 ; pos ++)
{
myservo.write(pos);
delay(5);
}
for(int pos = 180; pos >=0 ; pos --)
{
myservo.write(pos);
delay(5);
}
}
}

void RedTask(void * parameters)
{
for(;;)
{
Serial.print("Red Task Counter: ");
Serial.println(count1++);
digitalWrite(Red, HIGH);
vTaskDelay(500 / portTICK_PERIOD_MS);
digitalWrite(Red, LOW);
Serial.print("Red Task Counter: ");
Serial.println(count1++);
vTaskDelay(500 / portTICK_PERIOD_MS);
}
}

void BlueTask(void * parameters)
{
for(;;)
{
Serial.print("Blue Task Counter: ");
Serial.println(count2++);
digitalWrite(Blue, HIGH);
vTaskDelay(1000 / portTICK_PERIOD_MS);
digitalWrite(Blue, LOW);
Serial.print("Blue Task Counter: ");
Serial.println(count2++);
vTaskDelay(1000 / portTICK_PERIOD_MS);
}
}

void setup() {
  // put your setup code here, to run once:
pinMode(Red, OUTPUT);
pinMode(Blue, OUTPUT);
myservo.attach(servopin);
Serial.begin(9600);
xTaskCreatePinnedToCore(
RedTask,
"RedTask",
1000,
NULL,
1,
NULL,
0
);

xTaskCreatePinnedToCore(
BlueTask,
"BlueTask",
1000,
NULL,
1,
NULL,
0
);

xTaskCreatePinnedToCore(
ServoTask,
"ServoTask",
1000,
NULL,
1,
NULL,
1
);

}

void loop() {
  // put your main code here, to run repeatedly:
delay(1000);
}
