/*This code isn't tested yet*/
/* Using incremental optical encoder of Omron with 1000 pulse/rev with open collector output */

//define the used encoder/s
#define encoder1      
#define encoder2

#ifdef encoder1
  #define en1A 23
  #define en1B 19
#endif

#ifdef encoder2
  #define en2A 18
  #define en2B 5
#endif 
   
volatile int32_t pos1 = 0;
volatile int32_t pos2 = 0;


void IRAM_ATTR readEncoder1(){
if(digitalRead(en1B) == LOW) pos1++;
else pos1--;
}


void IRAM_ATTR readEncoder2(){
if(digitalRead(en2B) == LOW) pos2++;
else pos2--;
}

void setup() {
  // put your setup code here, to run once:
#ifdef encoder1
  pinMode(en1A, INPUT_PULLUP);
  pinMode(en1B, INPUT_PULLUP);
  attachInterrupt(en1A, readEncoder1, RISING);
#endif

#ifdef encoder2
  pinMode(en2A, INPUT_PULLUP);
  pinMode(en2B, INPUT_PULLUP);
  attachInterrupt(en2A, readEncoder2, RISING);
#endif

Serial.begin(115200);
while(!Serial){}

}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print("Position of Encoder1 is ");
Serial.print(pos1);

Serial.print(", Position of Encoder2 is ");
Serial.println(pos2);

delay(50);   //so you can read the serial monitor
}
