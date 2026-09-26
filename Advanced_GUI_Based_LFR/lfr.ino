void line_follow() {
  display.clearDisplay();
  c_text("LFR");
  display.display();
  errorP = errorL = 0;
  
  while (1) {
    reading();

    if (b_sum > 6) {
      if (bin_s[1] && bin_s[8]) {
        cross = 'l'; 
      }
    }

    if (cross != 's') {
      (cross == 'l') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);
      while (bin_s[5] != 0 && bin_s[6] != 0) reading();
      while (bin_s[5] == 0 && bin_s[6] == 0) reading(); 

      cross = 's';
      turn = 's';
      continue; 
    }

    if (b_sum > 4) {
      if (bin_s[8] != 0 && bin_s[1] == 0) {
        turn = 'l';
      } else if (bin_s[8] == 0 && bin_s[1] != 0) {
        turn = 'r';
      }
    }

    if (b_sum == 0 && turn != 's') {
      (turn == 'l') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);
      while (b_sum == 0) reading();
      motor(0, 0);
      turn = 's'; 
      continue;
    }

    if (b_sum < 4 && b_sum > 0) {
      errorP = (float)avg + target;
      PID = (float)P * errorP + D * (errorP - errorL);
      motor(spl + PID, spr - PID);
      errorL = errorP;
    }
  }
}