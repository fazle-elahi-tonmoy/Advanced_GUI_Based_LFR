String menu_list(byte a) {
  if (a == 1) return "Adjustment        ";
  else if (a == 2) return "Path Adjust       ";
  else if (a == 3) return "Side Adjust       ";
  else if (a == 4) return "Calibration       ";
  else if (a == 5) return "Analog Display    ";
  else if (a == 6) return "Sonar Display     ";
  else if (a == 7) return "Go Forward        ";
  else if (a == 8) return "Rotation Test     ";
  else if (a == 9) return "Path Clear        ";
  else if (a == 10) return "Memory Clear      ";
}

byte menu() {
  display.setTextSize(1);
  byte base = 1, peak = 8, temp = 0, ind = 1, limit = 10;
  bool u_flag = 0, d_flag = 0;
  while (1) {
    if (temp != ind) {
      display.clearDisplay();
      temp = ind;
      for (byte i = 0; i < 8; i++) {
        (i == ind - base) ? display.setTextColor(0, 1) : display.setTextColor(1);
        text(String(i + base) + ") " + menu_list(i + base), 0, i * 8);
      }
      display.display();
    }

    if (push(db)) {
      ind++;
      if (ind > limit) {
        ind = 1;
        base = ind;
        peak = base + 7;
      } else if (ind > peak) {
        peak = ind;
        base = peak - 7;
      }
    }

    if (push(ub)) {
      ind--;
      if (ind < 1) {
        ind = limit;
        peak = ind;
        base = peak - 7;
      } else if (ind < base) {
        base = ind;
        peak = base + 7;
      }
    }

    byte r = push(mb);
    if (r) {
      if (r == 1) return ind;
      else return 0;
    }
  }
}