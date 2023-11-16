#include "MQ135.h"
#include <SPI.h>
#include <Servo.h>   //servo library
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4

#include <stdlib.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <Wire.h>

SoftwareSerial nodemcu(2,3);

boolean dataArray[3];

Adafruit_SSD1306 display(OLED_RESET);
MQ135 gasSensor = MQ135(A1);
int val;
int sensorPin = A1;
int sensorValue = 0;
Servo servo;
int servoPin =9;
int buzzer=11;
void setup() {
  Wire.begin(4);                // join i2c bus with address #4
  //Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  nodemcu.begin(9600); 
  pinMode(sensorPin, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.clearDisplay();
  display.display();

    servo.attach(servoPin);
    servo.write(0);         //close cap on power on
    delay(100);
}
float temp;
void loop() {
  //servo.attach(servoPin);
//  val = analogRead(A1);
//  Serial.print ("raw = ");
//  Serial.println (val);
    float ppm = gasSensor.getPPM();
    Serial.print ("ppm: ");
    Serial.println (ppm);
    
  
  if(ppm>2){
    //buzzer
    servo.attach(servoPin);
    servo.write(270);
    delay(1000);
    servo.detach();
    tone(buzzer, 1000);
  }
  else
  {
    servo.attach(servoPin);
    servo.write(0);
    delay(1000);
    servo.detach();
  noTone(buzzer);
  }
  
 display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(18,43);
  display.println("CO2");
  display.setCursor(63,43);
  display.println("(PPM)");
  display.setTextSize(2);
  display.setCursor(28,5);
  display.println(ppm);
  display.display();
  display.clearDisplay();
  
  //delay(1000);
}

/*
void receiveEvent(int howMany)
{
  for(int i=0; i<howMany; i++)
  {
    dataArray[i] = Wire.read(); 
    //Serial.print(dataArray[i], HEX);  
  }
}*/
