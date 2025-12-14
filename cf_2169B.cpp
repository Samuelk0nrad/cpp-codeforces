#include <bits/stdc++.h>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;

    if (s.length() == 1) {
      cout << 1 << "\n";
      continue;
    }

    char last = 0;
    int vmin = -1;
    int vmax = -1;
    bool inf = false;
    int i = 1;
    for (auto c : s) {
      if (c == '*') {
        if (last == '>' || last == '*') {
          inf = true;
          break;
        }
      } else if (c == '<') {
        vmax = i;
        if (last == '*') {
          inf = true;
          break;
        }
      } else if (c == '>') {
        if (vmin == -1) {
          vmin = i;
        }
      }
      last = c;
      i++;
    }

    if ((vmin == -1 || vmax == -1) && !inf) {
      cout << s.length();
    } else if (vmin < vmax || inf) {
      cout << -1;
    } else {
      int tmin = s.length() - (vmin - 1);
      if (s[vmin - 2] == '*')
        tmin++;

      if (s[vmax] == '*')
        vmax++;

      cout << max(vmax, tmin);
    }
    cout << "\n";
  }
}
