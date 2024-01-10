/* --------------------------------------------------------------------------------------------------------
This sketch explains how you can use Interrupts in an application like a frequency counter (Code is tested)
---------------------------------------------------------------------------------------------------------*/

#define freqChannel 0
#define freq 10000
#define resolution 8
#define freqPin1        //Choose the pin you want to need (I used 2 pins as a validation of the reading)
#ifdef freqPin1
  #define freqPin 25
#endif
#ifdef freqPin2
  #define freqPin 26
#endif        
#define interruptPin 23

volatile long counter = 0;
typedef unsigned long long Timer_t;
Timer_t previous = 0;

void IRAM_ATTR isr()
{
  counter++;
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
while(!Serial){}   //wait to initiate the serial

ledcSetup(freqChannel, freq, resolution);  //initiate a channel
ledcAttachPin(freqPin, freqChannel);      //attaching a pin to our channel

attachInterrupt(interruptPin, isr , RISING);
previous = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
ledcWrite(freqChannel, 127);
if(millis()-previous >= 1000)
{
  Serial.print("Frequency = ");
  Serial.print(counter);
  Serial.println(" Hz");
  counter = 0;
  previous = millis();
}
}
