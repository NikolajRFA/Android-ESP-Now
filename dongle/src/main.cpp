#include <Arduino.h>

char command[255];

char macAddressData[18];

char data[239];

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Ready to receive");
}

void parseMacAddressAndData(){
  int avaliableBytes = Serial.available();
  if (avaliableBytes > 0){
    for (int i=0; i<avaliableBytes; i++){
      command[i] = Serial.read();
    }
    strncpy(macAddressData, command, 17);
    Serial.print("MacAddress:");
    Serial.println(macAddressData);
    strncpy(data, command+17, 238);
    Serial.print("Data:");
    Serial.println(data);
  }
}

void loop()
{
  parseMacAddressAndData();
}
