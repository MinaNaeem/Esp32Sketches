// -------------------------------------------------------------

// -------------------------------------------------------------
// Our includes
#include <WiFi.h>
#include <ros.h>
#include <std_msgs/Int32>


const char* ssid     = "WE_B244C9"; //Router Name
const char* password = "j9c06147";  //Router Password

IPAddress server(192,168,1,13); //IP Address of ROS Master Device (Raspberry pi)
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
}
ros::Subscriber<std_msgs::Int32> sub1("cmd_vel", &velCb );

void angleCb( const std_msgs::Int32& angle_msg){
  Serial.print("Received angle from Master = ");
  Serial.println(angle_msg.data);
}
ros::Subscriber<std_msgs::Int32> sub2("cmd_angle", &angleCb );

void setup() {
Serial.begin(115200);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println(WiFi.localIP()); //after connecting to wifi print the local ip of the esp32

while(!nh.connected())
{
nh.getHardware()->setConnection(server, serverPort);
}  //To check that esp32 in sync with raspberry pi
Serial.println(nh.getHardware()->getLocalIP());

nh.initNode();
nh.subscribe(sub1);
nh.subscribe(sub2);

}

void loop() {
  if(!nh.connected()) nh.getHardware()->setConnection(server, serverPort); //if the connection is down for any reason
 
  nh.spinOnce();
  delay(500);

}
