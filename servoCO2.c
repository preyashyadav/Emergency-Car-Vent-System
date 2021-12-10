#include "MQ135.h"
#include <SPI.h>
#include <Servo.h>   //servo library
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
MQ135 gasSensor = MQ135(A1);
int val;
int sensorPin = A1;
int sensorValue = 0;
Servo servo;       
int servoPin =9;
int buzzer=11;
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.clearDisplay();
  display.display();

   servo.attach(servoPin);   
    servo.write(0);         //close cap on power on
    delay(100);
    servo.detach(); 
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

  if(ppm>1){
    servo.attach(servoPin);
    delay(1);
    servo.write(0);  
    delay(3000);       
    servo.write(150);    
    delay(1000);
    servo.detach();

    //buzzer
    tone(buzzer, 45);
    delay(1000);
    noTone(buzzer);
    delay(1000);
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
  delay(1000);
}