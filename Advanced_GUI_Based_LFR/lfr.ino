void line_follow() {
  while (1) {
    reading();
    if (cross != 's') {
      (cross == 'l') ? motor(-tsp, tsp) : motor(tsp, -tsp);
      while (bin_s[2] || bin_s[3] || bin_s[4] || bin_s[5] || bin_s[6] || bin_s[7]) reading();
      while (!bin_s[4] && !bin_s[5]) reading();
      cross = turn = 's';
    }

    if (b_sum == 0) {
    }

    if (bin_s[9] && !bin_s[0] && b_sum > 3) {
      turn = 'l';
      if (side == 'l') {
        while (bin_s[9] && !bin_s[0]) reading();
        delay(node_delay);
        if (!bin_s[9] && b_sum > 0) cross = 'l';
      }
    }

    if (bin_s[9] && bin_s[0]) {
    }
  }
}