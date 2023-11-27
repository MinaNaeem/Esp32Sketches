#include <WiFi.h>
#define ssid "WE_B244C9"
#define pw "j9c06147"
#define Wifi_timeout 20000

void KeepWiFiAlive( void * parameters)
{
for(;;){
    if(WiFi.status() == WL_CONNECTED)
    {
    Serial.println("Wifi still connected");
    Serial.println(WiFi.localIP());     
    vTaskDelay(5000/ portTICK_PERIOD_MS);
    continue;
    }
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
  vTaskDelay(5000/portTICK_RATE_MS);
  continue;
}
else{
  Serial.print("Connected ");
Serial.println(WiFi.localIP());
}
}
}
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
xTaskCreatePinnedToCore(KeepWiFiAlive, "Wifi Check", 2000, NULL, 1, NULL, 1);
}


void loop() {
  // put your main code here, to run repeatedly:

}
