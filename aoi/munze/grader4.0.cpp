#include "munzen.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

int q = 0;
std::vector<int> muenzen;
std::vector<int> wiege(std::vector<std::vector<int>> paket) {
  q++;

  std::vector<int> gewichte(paket.size());
  for (int i = 0; i < paket.size(); i++) {
    for (int j = 0; j < paket[i].size(); j++) {
      gewichte[i] += muenzen[paket[i][j]];
    }
  }

  std::random_shuffle(gewichte.begin(), gewichte.end());
  return gewichte;
}

std::vector<int> bestimme_werte(int n) {
  // implementiere hier deine Lösung.
  // Mit wiege(std::vector<std::vector<int>> paket) kannst du Abfragen machen.
  vector<int> res;
  vector<vector<int>> ret;

  int sum = 0;
  while (res.size() < n) {
    vector<vector<int>> p;
    vector<int> vs;
    int l = res.size();

    bool ok = true;
    vector<bool> e(res.size(), false);
    int lv = 0;
    int z = sum;
    while (ok && l < n) {
      vector<int> t;
      t.push_back(l);

      int s = 1;
      int tz = z;
      int tr = 0;
      for (int i = 0; i < res.size() && s < lv; ++i) {
        if (!e[i]) {
          if (tz - res[i] < lv) {
            t.push_back(i);
            e[i] = true;
            tz -= res[i];
            tr += res[i];
            s += res[i];
          } else if (res[i] == 1) {
            if ((lv - s) % 2 == 1) {
              t.push_back(i);
              e[i] = true;
              tz -= res[i];
              tr += res[i];
              s += res[i];
            }
          } else {
            if (lv - s > 1) {
              t.push_back(i);
              e[i] = true;
              tz -= res[i];
              tr += res[i];
              s += res[i];
            }
          }
        }
        if (tz < lv - s) {
          ok = false;
          break;
        }
      }
      if (s < lv) {
        ok = false;
      }

      if (ok) {
        p.push_back(t);
        vs.push_back(tr);
        l++;
        lv = s + 1;
        z = tz;
      }
    }

    auto r = wiege(p);
    sort(r.begin(), r.end());
    for (int i = 0; i < r.size(); ++i) {
      res.push_back(r[i] - vs[i]);
      sum += r[i] - vs[i];
    }
  }

  return res;
}

int main() {
  int n;
  std::cin >> n;
  muenzen = std::vector<int>(n);
  for (int i = 0; i < n; i++)
    std::cin >> muenzen[i];
  for (int v : bestimme_werte(n))
    std::cout << v << " ";
  std::cout << "\n" << q << " Queries\n";
}
