#include "icon.h"
#include <NewPing.h>
#include <EEPROM.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire);

const byte ub = 15, mb = 17, db = 19;
byte sonarPin[6] = { 34, 32, 38, 36, 42, 40 };
byte IR_pins[10] = { 12, 10, 8, 6, 4, 2, 0, 1, 3, 5 };
byte motorPin[6] = { 10, 8, 6, 4, 2, 9 };
int weight[10] = { 5, 4, 3, 2, 1, -1, -2, -3, -4, -5 };
NewPing sonarL(sonarPin[0], sonarPin[1], 30);
NewPing sonarF(sonarPin[2], sonarPin[3], 30);
NewPing sonarR(sonarPin[4], sonarPin[5], 30);
byte sf, sl, sr;
int s[10], sensor, sum, b_sum;
bool bin_s[10];
int minimum[10], maximum[10];
float avg, errorP, errorL, target = 0, PID;

int speed, error, spl, spr, turn_speed;
int brake_time, turn_brake, turn90_delay, node_delay, stop_timer, u_turn_timer, i_timer;
int obstacle_distance, wall_distance, wall_mid, wallp, wall_limit = 25;
int P, I, D;
char side = 'r', turn = 's', cross = 's';
int pos;
bool i_mode = 0;
bool cont = 0;

byte path[50];
byte memory = 50;
int counter;

uint32_t m1, m2, tf, tr, tl;

void c_text(String text, int y = 24, int size = 2);

void setup() {
  memory_load();
  PID_load();
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
}

void loop() {
  byte r = push(mb);
  if (r == 1) {
    r = menu();
    if (r == 1) adjustment_panel();
    if (r == 2) PID_adjust();
    if (r == 3) cal();
    if (r == 4) analog_display();
    if (r == 5) sonar_display();
    if (r == 6) {
      display.clearDisplay();
      c_text("STARTING");
      display.display();
      delay(1000);
      motor(spl, spr);
      delay(3000);
      motor(0, 0);
    }
  }
  else if(r == 2) line_follow();

  r = push(ub);
  if (r) counter_adjust();

  reading();
  drawBars();
}
