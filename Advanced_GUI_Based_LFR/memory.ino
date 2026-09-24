void memory_load() {
  for (byte i = 0; i < 10; i++) {
    minimum[i] = EEPROM.read(i) * 4;
    maximum[i] = EEPROM.read(i + 10) * 4;
  }
}