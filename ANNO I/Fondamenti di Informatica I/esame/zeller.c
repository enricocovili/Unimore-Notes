extern int day_of_week(int d, int m, int y) {
  if (d < 1 || d > 31 || m < 1 || m > 12 || y < 0) {
    return -1;
  }
  int w = 0;
  if (m == 1) {
    y--;
    m = 13;
  }
  if (m == 2) {
    y--;
    m = 14;
  }
  w = (d + ((13 * m + 8) / 5) + y + y / 4 - y / 100 + y / 400) % 7;
  return w;
}