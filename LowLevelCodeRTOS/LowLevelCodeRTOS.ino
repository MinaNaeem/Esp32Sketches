// ---------------------------------------------------------------------------------------------------------------------------------------------
//This code will be our low level control over DC motors and Servo Motor(Steering Motor)
//Every Serial.println() is used for debegging and monitoring
// ---------------------------------------------------------------------------------------------------------------------------------------------
// Our includes
#include <ESP32Servo.h>
#include <WiFi.h>
#include <ros.h>
#include <std_msgs/Int32.h>

//Our macros
#define Servopin  26
#define Motor1en1 13 
#define Motor1en2 12
#define Motor2en1 14
#define Motor2en2 27

#define Wifi_timeout 20000

//Our variables
uint32_t currentspeed = 0;

Servo steerServo;
//-------------------------------------------------------------------------------------------------------
const char* ssid     = "WE_B244C9"; //Router Name
const char* password = "j9c06147";  //Router Password

IPAddress server(192,168,1,13); //IP Address of ROS Master Device (Raspberry pi)
//-------------------------------------------------------------------------------------------------------

const uint16_t serverPort = 11411;

ros::NodeHandle nh; //Definition of ROS handle

//-----------------------------------------------------
//This is How to make a publisher
//std_msgs::String msg; Or std_msgs::Int32 msg;
//ros::Publisher chatter("chatter", &msg);
// and don't forget to write nh.advertise(chatter); in void setup()
//-----------------------------------------------------
//This is how to make a subscriber
//void messageCb( const std_msgs::Int32& incoming_msg){
//   Serial.println(incoming_msg.data);
// }
// ros::Subscriber<std_msgs::Int32> sub("Esp32", &messageCb );
//And don't forget to wirte nh.subscibe(sub); in void setup()
//-----------------------------------------------------
void velCb( const std_msgs::Int32& velocity_msg){
  Serial.print("Received velocity from Master = ");
  Serial.println(velocity_msg.data);
  if(velocity_msg.data != currentspeed) currentspeed = velocity_msg.data;
}
ros::Subscriber<std_msgs::Int32> sub1("cmd_vel", &velCb );

void angleCb( const std_msgs::Int32& angle_msg){
  Serial.print("Received angle from Master = ");
  Serial.println(angle_msg.data);
  // if(angle_msg.data < 110 && angle_msg.data > 70)
  steerServo.write(angle_msg.data);
}
ros::Subscriber<std_msgs::Int32> sub2("cmd_angle", &angleCb );


void DCMotor(void * parameters){
  for(;;){
  switch (currentspeed)
  {case 1: 
          digitalWrite(Motor1en1, HIGH);
          digitalWrite(Motor2en1, HIGH);
          digitalWrite(Motor1en2, LOW);
          digitalWrite(Motor2en2, LOW);
          break;
  case -1: 
          digitalWrite(Motor1en1, LOW);
          digitalWrite(Motor2en1, LOW);
          digitalWrite(Motor1en2, HIGH);
          digitalWrite(Motor2en2, HIGH);     
          break;
  case 0:
          digitalWrite(Motor1en1, LOW);
          digitalWrite(Motor2en1, LOW);
          digitalWrite(Motor1en2, LOW);
          digitalWrite(Motor2en2, LOW);  
          break;   
  default:
          digitalWrite(Motor1en1, LOW);
          digitalWrite(Motor2en1, LOW);
          digitalWrite(Motor1en2, LOW);
          digitalWrite(Motor2en2, LOW);  
  }                
  vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}



void KeepWiFiAlive( void * parameters)
{
for(;;){
if(WiFi.status() == WL_CONNECTED)
{
// Serial.println("Wifi still connected");
// Serial.println(WiFi.localIP());     
vTaskDelay(5000/ portTICK_PERIOD_MS);
continue;
}
Serial.print("Connecting to WiFi");
WiFi.begin(ssid, password);
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
Serial.begin(115200);
steerServo.attach(Servopin);
steerServo.write(90);

pinMode(Motor1en1, OUTPUT);
pinMode(Motor1en2, OUTPUT);
pinMode(Motor2en1, OUTPUT);
pinMode(Motor2en2, OUTPUT);


WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println(WiFi.localIP()); //after connecting to wifi print the local ip of the esp32

nh.getHardware()->setConnection(server, serverPort);

nh.initNode();
  //To check that esp32 in sync with raspberry pi
Serial.println(nh.getHardware()->getLocalIP());

nh.subscribe(sub1);
nh.subscribe(sub2);

xTaskCreatePinnedToCore(
DCMotor,
"DCMotor",
1000,
NULL,
1,
NULL,
1);

xTaskCreatePinnedToCore(
KeepWiFiAlive,
"WiFi Check",
2000,
NULL,
1,
NULL,
0);




}

void loop() {

  nh.spinOnce();
  delay(100);

}
