/*This code is tested and Working*/
#define encoder2 //define your used encoder        

#ifdef encoder1
  #define enphaseA 23
  #define enphaseB 19
#endif

#ifdef encoder2
  #define enphaseA 18
  #define enphaseB 5
#endif 
   
volatile int32_t pos = 0;


void IRAM_ATTR readFunction(){
  
if(digitalRead(enphaseB) == LOW) pos++;
else pos--;
}

void setup() {
  // put your setup code here, to run once:
pinMode(enphaseA, INPUT_PULLUP);
pinMode(enphaseB, INPUT_PULLUP);

attachInterrupt(enphaseA, readFunction, RISING);
Serial.begin(115200);
while(!Serial){}


}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print("Position of Encoder is ");
Serial.println(pos);

delay(50);  //so you can read the serial monitor
}
