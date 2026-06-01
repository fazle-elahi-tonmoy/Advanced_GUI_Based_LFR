void text(String t, byte x, byte y) {
  display.setCursor(x, y);
  display.print(t);
}

void default_screen() {
  display.clearDisplay();
  display.drawBitmap(0, 0, techtopia, 128, 64, 1);
  display.display();
}

void drawBars() {
  display.clearDisplay();
  for (int i = 0; i < 10; i++)
    display.fillRect(4 + (9 - i) * 12, 63 - s[i] * 7, 10, s[i] * 7, 1);
  display.display();
}