void line_follow() {
  display.clearDisplay();
  c_text("LFR");
  display.display();
  errorP = errorL = 0;
  counter = EEPROM.read(20);
  while (1) {
start:
    reading();
    if (path[counter] == 12) {
      cont = 1;
      counter++;
    }

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

      else {
        // if (path[counter] == 9)
        // if (sonarl_read(0) || sonarr_read(0)) wall_follow();
        m2 = millis();
        while (!b_sum) {
          reading();
          if (millis() - m2 > u_turn_timer) {
            turn = side;
            if (path[counter] == 7) {
              counter++;
              cont = 0;
              digitalWrite(led, HIGH);
            }
            m1 = millis();
            break;
          }
        }
        if (path[counter] == 8) {
          counter++;
          cont = 0;
          digitalWrite(led, HIGH);
          m1 = millis();
        }
      }
    }

    else if (b_sum < 4) {
      // if (path[counter] == 10)
      // if (sonarf_read(0)) obstacle('l');
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
        if (path[counter] == 3 || path[counter] == 2 || (cont == 1 && side == 'r')) {
          while (!bin_s[9] && bin_s[0]) reading();
          if (bin_s[0] == 0) {
            delay(node_delay);
            reading();
            if (sum) {
              if (path[counter] == 3 || cont == 1) cross = side = 'r';
              if (path[counter] == 3 || path[counter] == 2) {
                counter++;
                digitalWrite(led, HIGH);
              }
            }
          }
        }
      }

      else if (!bin_s[0] && bin_s[9]) {
        turn = 'l';
        if (path[counter] == 1 || path[counter] == 2 || (cont == 1 && side == 'l')) {
          while (!bin_s[0] && bin_s[9]) reading();
          if (bin_s[9] == 0) {
            delay(node_delay);
            reading();
            if (b_sum) {
              if (path[counter] == 1 || cont == 1) cross = side = 'l';
              if (path[counter] == 1 || path[counter] == 2) {
                counter++;
                digitalWrite(led, HIGH);
              }
            }
          }
        }
      }

      else if (bin_s[0] && bin_s[9]) {
        // if (path[counter] == 11) i_detection();
        if (b_sum == 10) {
          reading();
          if (millis() - m2 > stop_timer) {
            motor(0, 0);
            turn = cross = 's';
            goto start;
          }
        }
        delay(node_delay);
        reading();
        if (b_sum) {
          if (path[counter] == 5) {
            counter++;
            if (path[counter] == 1) cross = side = 'l';
            else if (path[counter] == 3) cross = side = 'r';
            else cross = 's';
            counter++;
            cont = 0;
            digitalWrite(led, 1);
          } else if (cont == 1) cross = side;
        }

        else if (path[counter] == 4) {
          counter++;
          if (path[counter] == 1) turn = side = 'l';
          else if (path[counter] == 2) turn = 's';
          else if (path[counter] == 3) turn = side = 'r';
          counter++;
          cont = 0;
          digitalWrite(led, 1);
        }
      }
      m1 = millis();
    }
  }

  if (!bin_s[9] && bin_s[0]) {
    turn = 'r';
    m1 = millis();
  }

  else if (!bin_s[0] && bin_s[9]) {
    turn = 'l';
    m1 = millis();
  }

  if (millis() - m1 > cancel_timer) {
    turn = 's';
    digitalWrite(led, LOW);
  }
}