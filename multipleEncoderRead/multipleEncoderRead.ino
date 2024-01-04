/*This code isn't tested yet*/
/* Using optical encoder of Omron with 1000 pulse/rev with open collector output */

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
   
volatile uint32_t pos1 = 0;
volatile uint32_t pos2 = 0;


void IRAM_ATTR readEncoder1(){
if(digitalRead(en1B) > 0) pos1++;
else pos1--;
}


void IRAM_ATTR readEncoder2(){
if(digitalRead(en2B) > 0) pos2++;
else pos2--;
}

void setup() {
  // put your setup code here, to run once:
#ifdef encoder1
  pinMode(en1A, INPUT_PULLUP);
  pinMode(en1B, INPUT_PULLUP);
  attachInterrupt(en1A, readEncoder1, FALLING);
#endif

#ifdef encoder2
  pinMode(en2A, INPUT_PULLUP);
  pinMode(en2B, INPUT_PULLUP);
  attachInterrupt(en1B, readEncoder2, FALLING);
#endif

Serial.begin(115200);
delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print("Position of Encoder1 is ");
Serial.println(pos1);

Serial.print("Position of Encoder2 is ");
Serial.println(pos1);

delay(100);   //so you can read the serial monitor
}
