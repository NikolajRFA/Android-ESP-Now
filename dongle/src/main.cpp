#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

constexpr int INPUT_LENGTH = 255;
constexpr int MAC_ADDRESS_LENGTH = 17;
constexpr int DATA_LENGTH = 238;
constexpr int NULL_TERMINATOR_LENGTH = 1;
char input[INPUT_LENGTH];
char macAddressData[MAC_ADDRESS_LENGTH + NULL_TERMINATOR_LENGTH];
char data[DATA_LENGTH + NULL_TERMINATOR_LENGTH];
uint8_t broadcastAddress[6];
bool peerAdded = false;

esp_now_peer_info_t peerInfo;

void macAddressToUint8Array(const char *macAddress, uint8_t *array)
{
  for (int i = 0; i < 6; ++i)
  {
    char byteString[3] = {macAddress[i * 3], macAddress[i * 3 + 1], '\0'};
    array[i] = static_cast<uint8_t>(strtoul(byteString, nullptr, 16));
  }

  Serial.print("Parsed Mac address: ");
  for (int i = 0; i < 6; i++)
  {
    Serial.print(broadcastAddress[i], HEX);
    Serial.print("-");
  }
}

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
}

void parseMacAddressAndData()
{
  int avaliableBytes = Serial.available();
  if (avaliableBytes > 0)
  {
    for (int i = 0; i < avaliableBytes; i++)
    {
      input[i] = Serial.read();
    }
    strncpy(macAddressData, input, MAC_ADDRESS_LENGTH);
    strncpy(data, input + MAC_ADDRESS_LENGTH, DATA_LENGTH);
    macAddressToUint8Array(macAddressData, broadcastAddress);

    if (!peerAdded)
    {
      // Register peer
      memcpy(peerInfo.peer_addr, broadcastAddress, 6);
      peerInfo.channel = 0;
      peerInfo.encrypt = false;

      // Add peer
      if (esp_now_add_peer(&peerInfo) != ESP_OK)
      {
        Serial.println("Failed to add peer");
        return;
      }
      peerAdded = true;
    }

    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&data, sizeof(data));

    if (result == ESP_OK)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
    }
    else
    {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
    }
    delay(2000);
  }
}

void loop()
{
  parseMacAddressAndData();
}
