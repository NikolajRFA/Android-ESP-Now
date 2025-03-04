#include <Arduino.h>

char command[32];

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Ready to receive");
}

void commands(){
  if (Serial.available() > 0) {
    int avaliableBytes = Serial.available();
    for (int i=0; i<avaliableBytes; i++){
      command[i] = Serial.read();
    }
    Serial.println(command);

    if (command[0]=='O' && command[1]=='N' && command[2]=='\n')
    {
      digitalWrite(BUILTIN_LED, HIGH);
    }
    else if (command[0]=='O' && command[1]=='F' && command[2] == 'F' && command[3] == '\n')
    {
      digitalWrite(BUILTIN_LED, LOW);
    }
  }
}

void loop()
{
  commands();
}
