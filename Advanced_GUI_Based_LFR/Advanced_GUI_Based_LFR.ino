#include "icon.h"
#include <NewPing.h>
#include <EEPROM.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire);

const byte ub = 15, mb = 17, db = 19;
byte sonarPin[6] = { 34, 32, 38, 36, 42, 40 };
byte IR_pins[10] = { 12, 10, 8, 6, 4, 2, 0, 1, 3, 5 };
byte motorPin[6] = { 10, 8, 6, 4, 2, 9 };

NewPing sonarL(sonarPin[0], sonarPin[1], 30);
NewPing sonarF(sonarPin[2], sonarPin[3], 30);
NewPing sonarR(sonarPin[4], sonarPin[5], 30);
int s[10], sensor, sum;
float avg;

byte sf, sl, sr;

void setup() {
  Serial.begin(115200);
  pinMode(ub, INPUT_PULLUP);
  pinMode(mb, INPUT_PULLUP);
  pinMode(db, INPUT_PULLUP);
  for (byte i = 0; i < 6; i++) pinMode(motorPin[i], OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.invertDisplay(false);
  default_screen();
  delay(1000);
  // motor(255, 255);
}

void loop() {
  byte r = push(mb);
  if (r == 1) menu();
  reading();
  drawBars();
}
