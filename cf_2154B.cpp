#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    int max = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      int e;
      cin >> e;
      a[i] = e;
      if (e > max)
        max = e;
      if ((i % 2) == 1) {
        a[i] = max;
      }
    }

    int res = 0;

    for (int i = 0; i < n; i += 2) {
      int min = a[i] + 1;
      if (i != 0 && a[i - 1] < min)
        min = a[i - 1];
      if (i != n - 1 && a[i + 1] < min)
        min = a[i + 1];

      if (a[i] >= min) {
        res += a[i] - min;
        res++;
      }
    }

    cout << res << "\n";
  }
}
