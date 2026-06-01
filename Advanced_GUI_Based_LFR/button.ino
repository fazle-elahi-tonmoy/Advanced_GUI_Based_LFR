byte push(byte pin) {
  bool longPressed = 0;
  if (!digitalRead(pin)) {
    delay(50);
    byte t = 0;
    while (!digitalRead(pin)) {
      delay(50);
      t++;
      if (t > 10 && !longPressed) {
        longPressed = 1;
        display.clearDisplay();
        display.setTextSize(2);
        text("LONG PRESS", 04, 24);
        display.display();
      }
    }
    if (longPressed) return 2;
    return 1;
  } else return 0;
}