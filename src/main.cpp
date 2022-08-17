#include <Arduino.h>

#include "WiFi.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"

uint64_t chipid;  

bool initBluetooth(){
  if (!btStart()) {
    Serial.println("Failed to initialize controller");
    return false;
  }
   if (esp_bluedroid_init() != ESP_OK) {
    Serial.println("Failed to initialize bluedroid");
    return false;
  }
   if (esp_bluedroid_enable() != ESP_OK) {
    Serial.println("Failed to enable bluedroid");
    return false;
  }
  return true;
}
 
void printBtAddress() {
  const uint8_t* point = esp_bt_dev_get_address();
  for (int i = 0; i < 6; i++) {
    char str[3];
    sprintf(str, "%02X", (int)point[i]);
    Serial.print(str);
    if (i < 5){
      Serial.print(":");
    }
  }
}
void setup() {
	Serial.begin(115200);
  // CHIPID
  chipid=ESP.getEfuseMac();
  Serial.printf("ESP32 Chip ID:  %04X%08X",(uint16_t)(chipid>>32), (uint32_t)chipid);//print High 2 bytes
  // WIFI MAC Address
  Serial.println();
  Serial.print("ESP Board WiFi MAC Address:  ");
  Serial.println(WiFi.macAddress());
  // BT MAC Address
  initBluetooth();
  Serial.print("ESP Board BT MAC Address:  ");
  printBtAddress();
}

void loop() {

}
