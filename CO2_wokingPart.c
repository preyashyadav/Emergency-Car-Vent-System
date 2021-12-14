#include "MQ135.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
MQ135 gasSensor = MQ135(A1);
int val;
int sensorPin = A1;
int sensorValue = 0;
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.clearDisplay();
  display.display();
}

float temp;
void loop() {
  val = analogRead(A1);
  temp= analogRead(A0);
  temp=temp*0.48828125;
  Serial.print ("raw = ");
  Serial.println (val);
  float ppm = gasSensor.getPPM();
  Serial.print ("ppm: ");
  Serial.println (ppm);
 
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("*C");
  Serial.println();
 
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
  delay(1000);
}