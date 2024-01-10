/* This code is PI control for velocity */
/* This code isn't tested yet */
//---------------------------------Macros-------------------------------------------------
#define en1A 23
#define en1B 19
#define en2A 18
#define en2B 5
#define Rmotorp1 13
#define Rmotorp2 12
#define Rmotorpwm 26
#define Lmotorp1 14
#define Lmotorp2 27
#define Lmotorpwm 25

#define freq 5000
#define pwmChannel 0
#define resolution 8

#define encoderCounts 1000
#define GearRatio 70 //Change this number

#define Forward 1
#define Reverse -1
//------------------------------------------------------------------------------------------

//----------------------------------------Globals-------------------------------------------
volatile uint32_t pos1 = 0;
uint32_t prevPos1 = 0;
volatile uint32_t pos2 = 0;
uint32_t prevPos2 = 0;
unsigned long long prevT = 0;
float integralerror = 0;

int kp = 1;
int ki = 5;
//------------------------------------------------------------------------------------------
void IRAM_ATTR readEncoder1(){
if(digitalRead(en1B) == HIGH) pos1++;
else pos1--;
}

void IRAM_ATTR readEncoder2(){
if(digitalRead(en2B) == HIGH) pos2++;
else pos2--;
}

void SetMotor(int dir, int pwr){
if(dir == Forward){
digitalWrite(Rmotorp1,HIGH);
digitalWrite(Lmotorp1,HIGH);
digitalWrite(Rmotorp2,LOW);
digitalWrite(Lmotorp2,LOW);
}else if(dir == Reverse)
{
digitalWrite(Rmotorp1,LOW);
digitalWrite(Lmotorp1,LOW);
digitalWrite(Rmotorp2,HIGH);
digitalWrite(Lmotorp2,HIGH);
}
ledcWrite(pwmChannel, pwr);
}

void setup() {
  // put your setup code here, to run once:
pinMode(Rmotorp1,OUTPUT);
pinMode(Rmotorp2,OUTPUT);
pinMode(Rmotorpwm,OUTPUT);
pinMode(Lmotorp1,OUTPUT);
pinMode(Lmotorp2,OUTPUT);
pinMode(Lmotorpwm,OUTPUT);

pinMode(en1A, INPUT_PULLUP);
pinMode(en1B, INPUT_PULLUP);
pinMode(en2A, INPUT_PULLUP);
pinMode(en2B, INPUT_PULLUP);

attachInterrupt(en1A, readEncoder1, RISING);
attachInterrupt(en1B, readEncoder2, RISING);

ledcSetup(pwmChannel, freq, resolution);
ledcAttachPin(Rmotorpwm, pwmChannel);
ledcAttachPin(Lmotorpwm, pwmChannel);


Serial.begin(115200);
while(!Serial){}


}

void loop() {
  // put your main code here, to run repeatedly:
unsigned long long currT = micros();
float deltaT = ((float)(currT-prevT))/1.0e6;
float velocity1 = (pos1 - prevPos1)/deltaT;
float velocity2 = (pos2 - prevPos2)/deltaT;
float v1 = velocity1 * 60.0 / GearRatio;
float v2 = velocity2 * 60.0 / GearRatio;

prevPos1 = pos1;
prevPos2 = pos2;
prevT = currT;

float vavg = (v1+v2)/2;
float vtarget = 100*(sin(currT/1e6)>0); //100 rpm and 0 rpm
float error = vtarget - vavg;
integralerror = integralerror + error*deltaT;
float controlsignal = kp*error + ki*integralerror;

int dir = Forward;
if(controlsignal<0){
  dir = Reverse;
}
int pwr = (int)fabs(controlsignal);
if(pwr > 255) pwr = 255;
SetMotor(dir, pwr);

Serial.print(vavg);     //velocity in rpm
Serial.println();
}
