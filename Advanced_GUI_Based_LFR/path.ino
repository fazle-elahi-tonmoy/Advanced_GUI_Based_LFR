String path_list(byte a) {
  if (a == 0) return "EMPTY               ";
  else if (a == 1) return "LEFT                ";
  else if (a == 2) return "STRAIGHT            ";
  else if (a == 3) return "RIGHT               ";
  else if (a == 4) return "T-DETECT            ";
  else if (a == 5) return "CROSS DET.          ";
  else if (a == 6) return "90 DETECT           ";
  else if (a == 7) return "U TURN              ";
  else if (a == 8) return "LINE GAP            ";
  else if (a == 9) return "WALL FOLLOW         ";
  else if (a == 10) return "OBSTACLE            ";
  else if (a == 11) return "INVERSE             ";
  else if (a == 12) return "CONTINUE            ";
  else return "INVALID             ";
}

void path_panel() {
  display.setTextSize(1);
  byte base = 1, peak = 8, temp = 0, ind = 1, limit = 50;
  bool lpu = 0, lpb = 0;
  while (1) {
    if (temp != ind) {
      temp = ind;
      display.clearDisplay();
      for (byte i = 0; i < 8; i++) {
        (i == ind - base) ? display.setTextColor(0, 1) : display.setTextColor(1);
        text(String(i + base) + ") " + path_list(path[i + base - 1]), 0, i * 8);
      }
      display.display();
    }

    byte p = press(db, lpb);
    if (p) {
      if (p == 2) lpb = 1;
      ind++;
      if (ind > limit) {
        ind = 1;
        base = ind;
        peak = base + 7;
      } else if (ind > peak) {
        peak = ind;
        base = peak - 7;
      }
    } else lpb = 0;

    p = press(ub, lpu);
    if (p) {
      if (p == 2) lpu = 1;
      ind--;
      if (ind < 1) {
        ind = limit;
        peak = ind;
        base = peak - 7;
      } else if (ind < base) {
        base = ind;
        peak = base + 7;
      }
    } else lpu = 0;

    byte r = push(mb);
    if (r) {
      if (r == 1) path_adjust(ind - 1);
      else {
        path_load();
        return;
      }
      temp = 0;
    }
  }
}

void path_adjust(int indicator) {
  display.setTextSize(2);
  int value = path[indicator];
  int temp = -1, limit = 12;
  bool lpu = 0, lpb = 0;
  while (1) {
    if (temp != value) {
      temp = value;
      display.clearDisplay();
      String s = path_list(value);
      s.trim();
      c_text(s);
      display.display();
    }


    byte p = press(db, lpb);
    if (p) {
      if (p == 2) lpb = 1;
      value--;
    } else lpb = 0;

    p = press(ub, lpu);
    if (p) {
      if (p == 2) lpu = 1;
      value++;
    } else lpu = 0;

    value = constrain(value, 0, limit);

    byte r = push(mb);
    if (r) {
      display.setTextSize(1);
      if (r == 1) {
        path[indicator] = value;
        EEPROM.update(memory + indicator, value);
        return;
      }

      else return;
    }
  }
}
