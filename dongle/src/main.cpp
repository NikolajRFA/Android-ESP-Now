#include <Arduino.h>

String command;



void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Ready to receive");
}

void commands(){
  if (Serial.available())
  {
    command = Serial.read();
    Serial.println(command);
    if (command.equals("On\n")) 
    {
      digitalWrite(BUILTIN_LED, HIGH);

    }
    else if (command.equals("Off\n")) 
    {
      digitalWrite(BUILTIN_LED, LOW);
    }
  }
}

void loop()
{
  commands();
}


