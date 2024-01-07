/*----------------------------------------------------------------------------------------------------------------
  This code was a test to ensure that I can attach Interrupts to different cores on esp32 but after test It didn't 
  Work as I planned, so it will be modified later...                  (NOT WORKING)
  ----------------------------------------------------------------------------------------------------------------*/

#define pbPin1 26
#define pbPin2 27

void IRAM_ATTR isr0()
{
Serial.print("isr0 ");
Serial.println(xPortGetCoreID());
}


void IRAM_ATTR isr1()
{
Serial.print("isr1 ");
Serial.println(xPortGetCoreID());
}


void Task1( void *pvParameters)
{
attachInterrupt(pbPin1, isr0, FALLING);
Serial.print("Running TaskPB0 on core =  ");
Serial.println(xPortGetCoreID());
for(;;)
{
vTaskDelay(500/portTICK_PERIOD_MS);
}
}

void Task2( void *pvParameters)
{
attachInterrupt(pbPin2, isr1, FALLING);
Serial.print("Running TaskPB1 on core =  ");
Serial.println(xPortGetCoreID()); 
for(;;)
{
vTaskDelay(500/portTICK_PERIOD_MS);
}
}


void setup() {
  // put your setup code here, to run once:
pinMode(pbPin1, INPUT_PULLUP);
pinMode(pbPin2, INPUT_PULLUP);

Serial.begin(115200);
while(!Serial){}

Serial.println("Program Has Started!!");

xTaskCreatePinnedToCore(Task1,"PushButton1", 4096 , NULL, 1, NULL, 0);
xTaskCreatePinnedToCore(Task2,"PushButton2", 4096 , NULL, 1, NULL, 1);

vTaskDelete(NULL);    //To delete setup and loop function to work only on the given two tasks (Task1, Task2)
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println("LOOP FUNCTION");
vTaskDelay(1000/portTICK_PERIOD_MS); //the code shouldn't excute this but to ensure not to flood the serial monitor incase of anything wrong
}
