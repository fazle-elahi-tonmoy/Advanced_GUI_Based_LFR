void i_detection() {
  if (bin_s[9] && bin_s[0]) {  //inverse line detection
    uint32_t timer = millis();
    while ((bin_s[9] || bin_s[0]) && b_sum < 10) {
      reading();
      if (millis() - timer > i_timer) {
        i_mode = !i_mode;
        digitalWrite(led, i_mode);
        cross = 's';
        if (!i_mode) {
          counter++;
          cont = 0;
          digitalWrite(led, HIGH);
          m1 = millis();
        }
      }
    }
    turn = side;  //specific guided turn for Y section
  }
}
