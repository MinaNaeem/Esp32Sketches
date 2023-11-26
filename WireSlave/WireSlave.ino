#include "Wire.h"
#define I2C_DEV_ADDR 20

void onReceive(int len) {
  Serial.printf("onReceive[%d]: ", len);
  while (Wire.available()) {
    char a = Wire.read();
    Serial.write(a);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  Wire.onReceive(onReceive);
  Wire.begin(I2C_DEV_ADDR);
  Serial.println("I2C Slave has started!");
}

void loop() {
  delay(2000);
}
