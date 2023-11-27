#include "WiFi.h"
#define ssid "WE_B244C9"
#define pw "j9c06147"
#define Wifi_timeout 20000
void connectToWiFi()
{
Serial.print("Connecting to WiFi");
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, pw);
unsigned long startattempttime = millis();
while(WiFi.status() != WL_CONNECTED && millis()-startattempttime < Wifi_timeout){
Serial.print(".");
delay(100);

if(WiFi.status() !=WL_CONNECTED)
{
  Serial.println("Failed to connect");
}
else{
  Serial.print("Connected ");
Serial.println(WiFi.localIP());
}
}
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
connectToWiFi();
}

void loop() {
  // put your main code here, to run repeatedly:
delay(10000);
}
