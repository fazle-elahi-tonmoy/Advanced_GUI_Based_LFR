String adjustment_list(byte a) {
  if (a == 1) return "Top Speed     ";
  else if (a == 2) return "Motor Error   ";
  else if (a == 3) return "Node Delay    ";
  else if (a == 4) return "Turn Speed    ";
  else if (a == 5) return "Turn Brake    ";
  else if (a == 6) return "Brake Delay   ";
  else if (a == 7) return "Turn 90 Delay ";
  else if (a == 8) return "U Turn Timer  ";
  else if (a == 9) return "Stop Timer    ";
  else if (a == 10) return "Inv. Timer   ";
  else if (a == 11) return "Obj Dist.    ";
  else if (a == 12) return "Wall Dist.   ";
  else if (a == 13) return "Wall Mid     ";
  else if (a == 14) return "Wall Prop.   ";
}

void adjustment_panel() {
  display.setTextSize(1);
  byte base = 1, peak = 8, temp = 0, ind = 1, limit = 14;
  bool lpu = 0, lpb = 0;
  int value;
  while (1) {
    if (temp != ind) {
      temp = ind;
      display.clearDisplay();
      for (byte i = 0; i < 8; i++) {
        (i == ind - base) ? display.setTextColor(0, 1) : display.setTextColor(1);
        if (i + base >= 6 && i + base <= 10) value = EEPROM.read(i + base + 20) * 10;
        else if (i + base == 2) value = EEPROM.read(i + base + 20) * 2 - 250;
        else value = EEPROM.read(i + base + 20);
        text(String(i + base) + ") " + adjustment_list(i + base) + String(value), 0, i * 8);
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

    p = push(mb);
    if (p) {
      if (p == 1) set_adjust(ind);
      else {
        memory_load();
        return;
      }
      temp = 0;
    }
  }
}

void set_adjust(int indicator) {
  display.setTextSize(2);
  display.setTextColor(1);
  display.clearDisplay();
  int value;
  bool lpu = 0, lpb = 0;
  if (indicator >= 6 && indicator <= 10) value = EEPROM.read(indicator + 20) * 10;
  else value = EEPROM.read(indicator + 20);

  int temp = -1, limit = 255;
  if (indicator >= 6 && indicator <= 10) limit = 2500;

  while (1) {
    if (temp != value) {
      temp = value;
      display.clearDisplay();
      if (indicator == 2) text("SET: " + String(value * 2 - 250), 5, 24);
      else text("SET: " + String(value), 5, 24);
      display.display();
    }

    byte p = press(ub, lpu);
    if (p) {
      if (p == 2) lpu = 1;
      (indicator >= 6 && indicator <= 10) ? value += 10 : value++;
      if (value > limit) value = limit;
    } else lpu = 0;

    p = press(db, lpb);
    if (p) {
      if (p == 2) lpb = 1;
      (indicator >= 6 && indicator <= 10) ? value -= 10 : value--;
      if (value < 0) value = 0;
    } else lpb = 0;

    byte r = push(mb);
    if (r) {
      if (r == 1) {
        (indicator >= 6 && indicator <= 10) ? EEPROM.update(20 + indicator, value / 10)
                                            : EEPROM.update(20 + indicator, value);
        delay(10);
        display.setTextSize(1);
        return;
      } else return;
    }
  }
}

void counter_adjust() {
  display.setTextSize(2);
  display.clearDisplay();
  counter = EEPROM.read(20);
  byte temp = -1, limit = 50;
  bool lpu = 0, lpb = 0;
  while (1) {
    if (temp != counter) {
      temp = counter;
      display.clearDisplay();
      text("SET: " + String(counter), 5, 24);
      display.display();
    }

    byte p = press(ub, lpu);
    if (p) {
      if (p == 2) lpu = 1;
      counter++;
      if (counter > limit) counter = limit;
    } else lpu = 0;

    p = press(db, lpb);
    if (p) {
      counter--;
      if (counter < 0) counter = 0;
    } else lpb = 0;


    byte r = push(mb);
    if (r) {
      if (r == 1) EEPROM.update(20, counter);
      else counter = EEPROM.read(20);
      return;
    }
  }
}

void PID_adjust() {
  PID_load();
  display.setTextSize(2);
  byte temp = 10, ind = 0;
  bool lpu = 0, lpb = 0;
  String s;
  while (1) {
    if (temp != ind) {
      temp = ind;
      display.clearDisplay();
      for (byte i = 0; i < 3; i++) {
        if (i == 0) s = "P: " + String(P);
        else if (i == 1) s = "I: " + String(I);
        else s = "D: " + String(D);
        (i == ind) ? display.setTextColor(0, 1) : display.setTextColor(1);
        text(s, 0, i * 21);
      }
      display.display();
    }

    byte p = press(db, lpb);
    if (p) {
      if (p == 2) lpb = 1;
      if (ind == 0) P--;
      else if (ind == 1) I--;
      else if (ind == 2) D -= 10;
      temp = 10;
    } else lpb = 0;

    p = press(ub, lpu);
    if (p) {
      if (p == 2) lpu = 1;
      if (ind == 0) P++;
      else if (ind == 1) I++;
      else if (ind == 2) D += 10;
      temp = 10;
    } else lpu = 0;

    P = constrain(P, 0, 255);
    I = constrain(I, 0, 255);
    D = constrain(D, 0, 2550);

    p = push(mb);
    if (p) {
      if (p == 1) {
        ind++;
        if (ind >= 3) ind = 0;
      }

      else {
        PID_save();
        return;
      }
    }
  }
}
