#include <Arduino.h>

String command;

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Ready to receive");
}

void commands(){
  if (Serial.available())
  {
    command = Serial.readString();
    if (command.equals("ON\n")) 
    {
      digitalWrite(BUILTIN_LED, HIGH);
    }
    else if (command.equals("OFF\n"))
    {
      digitalWrite(BUILTIN_LED, LOW);
    }
  }
}

void loop()
{
  commands();
}
