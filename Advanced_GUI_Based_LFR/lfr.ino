void line_follow() {
  display.clearDisplay();
  c_text("LFR");
  display.display();
  errorP = errorL = 0;

  while (1) {
    reading();
    if (b_sum == 0) {
      if (turn != 's') {
        brake();
        (turn == 'l') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);
        while (bin_s[2] == 0 && bin_s[5] == 0) reading();  // Spin until line is found again
        if (turn_brake) {
          (turn == 'r') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);
          delay(turn_brake);
        }
        turn = 's';
      }
    }

    else if (b_sum < 4) {
      if (cross != 's') {
        brake();
        (cross == 'l') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);
        while (bin_s[5] != 0 && bin_s[6] != 0) reading();
        while (bin_s[3] == 0 && bin_s[4] == 0) reading();
        if (turn_brake) {
          (cross == 'r') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);
          delay(turn_brake);
        }
        cross = turn = 's';
      }

      errorP = (float)avg + target;
      PID = (float)P * errorP + D * (errorP - errorL);
      motor(spl + PID, spr - PID);
      errorL = errorP;
    }

    else {
      if (!bin_s[9] && bin_s[0]) {
        turn = 'r';
      }

      else if (!bin_s[0] && bin_s[9]) {
        turn = 'l';
      }
    }
  }
}