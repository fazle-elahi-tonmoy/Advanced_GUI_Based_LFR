void text(String t, byte x, byte y) {
  display.setCursor(x, y);
  display.print(t);
}

void c_text(String text, int y, int size = 2) {
  display.setTextSize(size);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, y, &x1, &y1, &w, &h);
  int x = (128 - w) / 2;
  display.setCursor(x, y);
  display.print(text);
}

void default_screen() {
  display.clearDisplay();
  display.drawBitmap(0, 0, meet_the_bots, 128, 64, 1);
  display.display();
}

void drawBars() {
  display.clearDisplay();
  for (int i = 0; i < 10; i++) {
    int barHeight = map(s[i], 0, 9, 0, 54);
    int x = 4 + (9 - i) * 12;
    int y = 53 - barHeight;
    if (barHeight > 0) display.fillRect(x, y, 10, barHeight, SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(x + 2, 55);
    display.print(s[i]);
  }
  display.display();
}