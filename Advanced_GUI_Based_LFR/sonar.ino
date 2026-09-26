bool wallf_read(bool mode) {
  if (tf - millis() > 50 || mode) {
    tf = millis();
    sf = sonarF.ping_cm();
    if (sf <= 2) sf = 50;
  }
  if (sf < wall_distance) return 1;
  else return 0;
}

bool sonarf_read(bool mode) {
  if (tf - millis() > 50 || mode) {
    tf = millis();
    sf = sonarF.ping_cm();
    if (sf <= 2) sf = 50;
  }
  if (sf < obstacle_distance) return 1;
  else return 0;
}

bool sonarr_read(bool mode) {
  if (tr - millis() > 50 || mode) {
    tr = millis();
    sr = sonarR.ping_cm();
    if (sr <= 2) sr = 50;
  }
  if (sr < wall_limit) return 1;
  else return 0;
}

bool sonarl_read(bool mode) {
  if (tl - millis() > 50 || mode) {
    tl = millis();
    sl = sonarL.ping_cm();
    if (sl <= 2) sl = 50;
  }
  if (sl < wall_limit) return 1;
  else return 0;
}

void wall_follow() {
  while (!b_sum) {
    reading();
    while (sonarr_read(1)) {
      int error = (wall_mid - sr) * wallp;
      if (abs(error) < 2) motor(150 + error, 150 - error);
      else motor(150, 150);
    }
    while (sonarl_read(1)) {
      int error = (wall_mid - sl) * wallp;
      if (abs(error) < 2) motor(150 - error, 150 + error);
      else motor(150, 150);
    }
    motor(150, 150);
  }

  counter++;
  cont = 0;
  digitalWrite(led, HIGH);
  m1 = millis();
}

void obstacle(char s) {
  brake();
  motor_turn(s);
  reading();
  (s == 'l') ? motor(spl, spr * 0.5) : motor(spl * 0.5, spr);  //this should be adjusted
  while (!b_sum) reading();
  while (b_sum) reading();
  delay(node_delay);
  motor(0, 0);
  delay(100);
  motor_turn(s);
  counter++;
  cont = 0;
  cross = turn = 's';
  digitalWrite(led, HIGH);
  m1 = millis();
}