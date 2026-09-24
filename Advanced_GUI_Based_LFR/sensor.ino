void reading() {
  sensor = 0;
  for (byte i = 0; i < 10; i++) {
    s[i] = analogRead(IR_pins[i]);
    s[i] = map(s[i], 0, 1023, 0, 9);
    s[i] = constrain(s[i], 0, 9);
    // Serial.print(String(s[i]) + " ");
  }
  // Serial.println();
}

void sonarRead() {
  sf = sonarF.ping_cm();
  sr = sonarR.ping_cm();
  sl = sonarL.ping_cm();
  // Serial.println(String(sl) + " " + String(sf) + " " + String(sr));
}

void analog_display() {
  display.setTextSize(1);
  while (!push(mb)) {
    display.clearDisplay();
    for (int i = 0; i < 10; i++) {
      (i < 5) ? text(String(analogRead(IR_pins[i])), i * 9, 40 - i * 8) : text(String(analogRead(IR_pins[i])), (i - 4) * 9 + 58, (i - 4) * 8);
    }
    display.display();
  }
}

void sonar_display() {
  display.setTextSize(2);
  while (!push(mb)) {
    sonarRead();
    display.clearDisplay();
    text(String(sl), 0, 24);
    c_text(String(sf), 24);
    text(String(sr), 100, 24);
    display.display();
    delay(30);
  }
}

void calibration(){
  
}