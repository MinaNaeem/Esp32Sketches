#define POT 25
#define Led 26

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
 

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
ledcSetup(ledChannel, freq, resolution);
ledcAttachPin(Led, ledChannel);

}

void loop() {
  // put your main code here, to run repeatedly:
float read = analogRead(POT);
int dutycycle = read * 255.0 / 4095.0;
Serial.println(dutycycle);
ledcWrite(ledChannel, dutycycle);
}
