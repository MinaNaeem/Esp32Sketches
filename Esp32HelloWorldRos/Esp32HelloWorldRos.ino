/*
 * rosserial Publisher Example
 * Prints "hello world!"
 * This intend to connect to a Wifi Access Point
 * and a rosserial socket server.
 * You can launch the rosserial socket server with
 * roslaunch rosserial_server socket.launch
 * The default port is 11411
 *
 */
#include <WiFi.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>


const char* ssid     = "WE_B244C9";
const char* password = "j9c06147";
// Set the rosserial socket server IP address
IPAddress server(192,168,1,13);
// Set the rosserial socket server port
const uint16_t serverPort = 11411;

ros::NodeHandle nh;
// Make a chatter publisher
std_msgs::String msg;
ros::Publisher chatter("chatter", &msg);
// Be polite and say hello
char hello[] = "Thanks";





void messageCb( const std_msgs::Int32& incoming_msg){
  Serial.println(incoming_msg.data);
}
ros::Subscriber<std_msgs::Int32> sub("Esp32", &messageCb );



void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect the ESP8266 the the wifi AP
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set the connection to rosserial socket server
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();

  // Another way to get IP
  Serial.print("IP = ");
  Serial.println(nh.getHardware()->getLocalIP());

  // Start to be polite
  nh.advertise(chatter);
  nh.subscribe(sub);
}

void loop()
{

  if (nh.connected()) {
    // Serial.println("Connected");
    // Say hello
    msg.data = hello;
    chatter.publish( &msg );
  } else {
    Serial.println("Not Connected");
    nh.getHardware()->setConnection(server, serverPort);
    
  }
  nh.spinOnce();
  // Loop exproximativly at 2Hz
  delay(500);
}
