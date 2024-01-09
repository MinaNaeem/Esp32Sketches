/*This code isn't tested yet*/
#define encoder1 //define your used encoder        

#ifdef encoder1
  #define enphaseA 23
  #define enphaseB 19
#endif

#ifdef encoder2
  #define enphaseA 18
  #define enphaseB 5
#endif 
//-------------------------Macros-----------------------------------------------------
#define TIMESAMPLE 100 //100 milliseconds
#define GearRatio 70 //Change this line to your gear ratio
#define TicksPerRev 1000 //1000 Pulse/Rev
//------------------------------------------------------------------------------------
//------------------------Globals-----------------------------------------------------
volatile uint32_t prevT = 0;
volatile int reading = 0;
float vel = 0;
//------------------------------------------------------------------------------------

void IRAM_ATTR readFunction(){
if(digitalRead(enphaseB) == HIGH) reading++;
else reading--;
}

void setup() {
  // put your setup code here, to run once:
pinMode(enphaseA, INPUT_PULLUP);
pinMode(enphaseB, INPUT_PULLUP);

attachInterrupt(enphaseA, readFunction, RISING);
Serial.begin(115200);
while(!Serial){}

Serial.println("Program Started Successfully!");
prevT = millis();
}

void loop() {
if(millis() - prevT > TIMESAMPLE)
{
detachInterrupt(enphaseA);
vel = float(reading) / (TicksPerRev * TIMESAMPLE);
if(vel > 0)
{
  Serial.print("Velocity of Encoder is ");
  Serial.print(fabs(vel));
  Serial.print(" encoderRev/s Positive Direction,\t");
  Serial.print(fabs(GearRatio*vel*60.0));
  Serial.println(" Motor Rev per Minute");
}
else{
  Serial.print("Velocity of Encoder is ");
  Serial.print(fabs(vel));
  Serial.print(" encoderRev/s Negative Direction,\t");
  Serial.print(fabs(GearRatio*vel*60.0));
  Serial.println(" Motor Rev per Minute");
}
reading = 0;
attachInterrupt(enphaseA, readFunction, FALLING);
prevT = millis();
}
}
