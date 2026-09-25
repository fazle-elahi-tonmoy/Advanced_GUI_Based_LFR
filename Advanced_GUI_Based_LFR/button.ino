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
        c_text("LONG PRESS");
        display.display();
      }
    }
    if (longPressed) return 2;
    return 1;
  } else return 0;
}


byte press(byte pin, bool longPress) {
  if (!digitalRead(pin)) {
    byte t = 0;
    while (!digitalRead(pin)) {
      if (t > 10 || longPress) return 2;
      delay(50);
      t++;
    }
    return 1;
  } else return 0;
}
