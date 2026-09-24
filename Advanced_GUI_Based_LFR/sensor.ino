void reading() {
  sensor = 0;
  sum = 0;
  b_sum = 0;
  for (byte i = 0; i < 10; i++) {
    s[i] = analogRead(IR_pins[i]);
    s[i] = map(s[i], minimum[i], maximum[i], 0, 9);
    s[i] = constrain(s[i], 0, 9);
    bin_s[i] = (s[i] > 4);
    sensor += s[i] * weight[i];
    sum += s[i];
    b_sum += bin_s[i];
    // Serial.print(String(s[i]) + " ");
  }
  if (sum) avg = (float)sensor / sum;
  // Serial.print(avg);
  // Serial.println("  " + String(b_sum));
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
      (i < 5) ? text(String(analogRead(IR_pins[9 - i])), i * 9, 40 - i * 8) : text(String(analogRead(IR_pins[9 - i])), (i - 5) * 9 + 64, (i - 4) * 8);
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

void cal() {
  for (byte i = 0; i < 10; i++) {
    minimum[i] = 1023;
    maximum[i] = 0;
  }
  display.clearDisplay();
  c_text("CALIBRATE");
  display.display();
  while (!push(mb)) {
    for (byte i = 0; i < 10; i++) {
      s[i] = analogRead(IR_pins[i]);
      minimum[i] = min(s[i], minimum[i]);
      maximum[i] = max(s[i], maximum[i]);
    }
  }

  display.clearDisplay();
  c_text("DONE!");
  display.display();
  delay(1000);

  for (byte i = 0; i < 10; i++) {
    EEPROM.update(i, (minimum[i] + 50) / 4);
    EEPROM.update(i + 10, (maximum[i] - 50) / 4);
  }

  display.clearDisplay();
  display.setTextSize(1);
  for (byte i = 0; i < 10; i++) {
    (i < 5) ? text(String(minimum[i]), i * 25, 12) : text(String(minimum[i]), (i - 5) * 25, 20);
    (i < 5) ? text(String(maximum[i]), i * 25, 44) : text(String(maximum[i]), (i - 5) * 25, 52);
  }
  display.setTextColor(0, 1);
  c_text("MINIMUM", 0, 1);
  c_text("MAXIMUM", 32, 1);
  display.display();
  display.setTextColor(1);

  while (!push(mb))
    ;
}
