void motor(int a, int b) {
  digitalWrite(motorPin[1], a > 0);
  digitalWrite(motorPin[2], a < 0);
  digitalWrite(motorPin[3], b > 0);
  digitalWrite(motorPin[4], b < 0);
  analogWrite(motorPin[0], constrain(abs(a), 0, 255));
  analogWrite(motorPin[5], constrain(abs(b), 0, 255));
}

void motor_turn(char t) {
  (t == 'l') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);
  delay(turn90_delay);
  (t == 'r') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);
  delay(turn_brake);
  motor(0, 0);
}