#include <bits/stdc++.h>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    vector<int> a;

    for (int i = 0; i < n; i++) {
      int e;
      cin >> e;
      a.push_back(e);
    }

    sort(a.begin(), a.end(), greater<int>());

    int res = 0;
    for (int i = 0; i < n; i++) {
      res = a[i - 1] - a[i];
      if (a[i - 1] != a[i]) {
        res++;
      }
    }
    cout << res << "\n";
  }
}
