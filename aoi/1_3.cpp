#include <bits/stdc++.h>
#include <cmath>

bool subtask3(std::vector<int> &v, int x) {

  int lo = 0, hi = v.size();

  do {
    int m = lo + floor(hi - lo / 2.0);
    int e = v[m];
    if (e == x) {
      return true;
    } else if (e < x) {
      lo = m + 1;
    } else {
      hi = m;
    }
  } while (lo < hi);

  return false;
}
