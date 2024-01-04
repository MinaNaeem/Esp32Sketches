#define dacPin 25
#define dimingDelay 5
#define upperThershold 255
#define lowerThershold 120

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
for(int i = lowerThershold ; i <= upperThershold ; i++)
{
dacWrite(dacPin ,i);
Serial.print("DAC voltage: ");
Serial.println(i/256.0 * 3.3);
delay(dimingDelay);
}
for(int j =upperThershold; j >= lowerThershold ; j--)
{
dacWrite(dacPin ,j);
Serial.print("DAC voltage: ");
Serial.println(j/256.0 *3.3);
delay(dimingDelay);
}
}
