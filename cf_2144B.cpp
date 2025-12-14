#include <algorithm>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vector<int> p;
    int sz = 0;
    for (int i = 0; i < n; i++) {
      int e;
      cin >> e;
      p.push_back(e);
      if (e == 0)
        sz++;
    }

    int l = n;
    int r = 0;
    int single = -1;
    for (int i = 1; i <= n; i++) {
      if (p[i - 1] != i) {
        if (p[i - 1] == 0 && sz <= 1) {
          single = i;
        } else {
          if (l > i)
            l = i;
          if (r - 1 < i)
            r = i + 1;
        }
      }
    }

    if (single != -1 && (l != n || r != 0)) {
      sort(p.begin(), p.end());
      int c = 0;
      for (; c < n; c++) {
        if (p[c] != c) {
          break;
        }
      }
      if (c != single) {
        if (l > single)
          l = single;
        if (r - 1 < single)
          r = single + 1;
      }
    }

    int res = r - l;
    cout << ((res < 0) ? 0 : r - l) << "\n";
  }
}
