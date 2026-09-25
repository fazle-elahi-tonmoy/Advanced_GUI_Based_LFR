void memory_load() {
  for (byte i = 0; i < 10; i++) {
    minimum[i] = EEPROM.read(i) * 4;
    maximum[i] = EEPROM.read(i + 10) * 4;
  }

  counter = EEPROM.read(20);
  speed = EEPROM.read(21);
  error = EEPROM.read(22) * 2 - 250;
  node_delay = EEPROM.read(23);
  turn_speed = EEPROM.read(24);
  turn_brake = EEPROM.read(25);
  brake_time = EEPROM.read(26) * 10;
  turn90_delay = EEPROM.read(27) * 10;
  u_turn_timer = EEPROM.read(28) * 10;
  stop_timer = EEPROM.read(29) * 10;
  i_timer = EEPROM.read(30) * 10;
  obstacle_distance = EEPROM.read(31);
  wall_distance = EEPROM.read(32);
  wall_mid = EEPROM.read(33);
  wallp = EEPROM.read(34);
  (error > 0) ? spr = speed - error : spr = speed;
  (error < 0) ? spl = speed + error : spl = speed;
}

void PID_load() {
  P = EEPROM.read(40);
  I = EEPROM.read(41);
  D = EEPROM.read(42) * 10;
}

void PID_save() {
  EEPROM.update(40, P);
  EEPROM.update(41, I);
  EEPROM.update(42, D / 10);
}

void path_load() {
  for (byte i = 0; i < 50; i++) {
    path[i] = EEPROM.read(i + memory);
    Serial.print(String(path[i]) + " ");
  }
  Serial.println();
}