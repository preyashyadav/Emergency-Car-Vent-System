// The load resistance on the board
#include <SPI.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
int val;
int sensorPin = A1;
int sensorValue = 0;
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.display();
}
void loop() {
  val = analogRead(A1);
  Serial.print ("raw = ");
  Serial.println (val);
 // float zero = gasSensor.getRZero();
 // Serial.print ("rzero: ");
  //Serial.println (zero);
  float ppm = gasSensor.getPPM();
  Serial.print ("ppm: ");
  Serial.println (ppm);
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
  delay(2000);
}