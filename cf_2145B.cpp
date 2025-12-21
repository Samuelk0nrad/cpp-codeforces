#include <bits/stdc++.h>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    string res;

    int top = 0;
    int bottom = 0;
    int idk = 0;
    for (char e : s) {
      if (e == '0') {
        top++;
      } else if (e == '1') {

        bottom++;
      } else if (e == '2') {
        idk++;
      }
    }

    int lidk = idk;
    int count = n - top - bottom - (idk * 2);
    for (int i = 0; i < n; i++) {
      if (i < top) {
        res += '-';
      } else if (n - i - 1 < bottom) {
        res += '-';
      } else if (k >= n) {
        res += '-';
      } else if (lidk) {
        res += '?';
        lidk--;
      } else if (count > 0) {
        res += '+';
        count--;
      } else {
        res += '?';
      }
    }

    cout << res << "\n";
  }
}
