#include <stdlib.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <Wire.h>

SoftwareSerial nodemcu(2,3);

#define relay1 5

boolean dataArray[3];


void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);  
  nodemcu.begin(9600); 
  pinMode(relay1,OUTPUT);
}
void loop()
{  
  StaticJsonDocument<1000> jsonBuffer;
  JsonObject data = jsonBuffer.to<JsonObject>();
  data["notify"] = 0;
  serializeJson(data,nodemcu);
  jsonBuffer.clear();
      
  if(dataArray[0] == 0){
    digitalWrite(relay1,HIGH);
  }
  else{
    digitalWrite(relay1,LOW);
  }

  delay(2000);

}

void receiveEvent(int howMany)
{
  for(int i=0; i<howMany; i++)
  {
    dataArray[i] = Wire.read(); 
    Serial.print(dataArray[i], HEX);  
  }
}
