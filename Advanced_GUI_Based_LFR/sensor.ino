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