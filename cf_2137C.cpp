#include <bits/stdc++.h>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    long long a, b;
    cin >> a >> b;

    long long max = -1;
    if ((1 + a * b) % 2 == 0) {
      cout << 1 + a * b << '\n';
      continue;
    }
    for (int i = b / 2; i > 0; i--) {
      if (b % i != 0)
        continue;

      long long r = (a * i) + (b / i);
      if (r % 2 == 0 && max < r) {
        max = r;
        break;
      }
    }

    cout << max << "\n";
  }
}
