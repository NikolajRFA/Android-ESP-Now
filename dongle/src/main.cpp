#include <Arduino.h>

constexpr int INPUT_LENGTH = 255; 
constexpr int MAC_ADDRESS_LENGTH = 17;
constexpr int DATA_LENGTH = 238;
char input[INPUT_LENGTH +1];
char macAddressData[MAC_ADDRESS_LENGTH +1];
char data[DATA_LENGTH +1];

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
      input[i] = Serial.read();
    }
    strncpy(macAddressData, input, MAC_ADDRESS_LENGTH);
    Serial.print("MacAddress:");
    Serial.println(macAddressData);
    strncpy(data, input+MAC_ADDRESS_LENGTH, DATA_LENGTH);
    Serial.print("Data:");
    Serial.println(data);
  }
}

void loop()
{
  parseMacAddressAndData();
}
