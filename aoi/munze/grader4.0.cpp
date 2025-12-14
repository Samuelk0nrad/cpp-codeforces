#include "munzen.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <queue>
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

  set<int> ones;
  set<int> twos;

  int last = -1;
  int lz = 0;
  int lzs = 0;
  while (last + 1 < n) {
    vector<vector<int>> p;
    vector<int> vs;
    int l = last;

    bool ok = true;
    int lv = 0;
    bool za = false;

    queue<int> lones;
    for (int e : ones) {
      lones.push(e);
    }
    queue<int> ltwos;
    for (int e : twos) {
      ltwos.push(e);
    }

    int vz = lz;
    int vzs = lzs;
    while (ok && l + 1 < n) {
      vector<int> t;

      if (lz) {
        if (p.size() + 1 == lzs && !za) {
          l++;
          za = true;
          continue;
        }
      }

      t.push_back(l + 1);

      int s = 2;

      while (s <= lv) {
        int e = 0;
        if ((lv - s) - 2 >= 0 && !ltwos.empty()) {
          e = ltwos.front();
          ltwos.pop();
        } else if (!lones.empty()) {
          e = lones.front();
          lones.pop();
        } else if (!ltwos.empty()) {
          e = ltwos.front();
          ltwos.pop();
        } else {
          ok = false;
          break;
        }

        t.push_back(e);

        s += res[e];
        e++;
      }

      if (ok) {
        p.push_back(t);
        vs.push_back(s - 2);
        l++;
        lv = s;
      }
    }

    bool z = false;
    if (n - l > lv) {
      vector<int> t;
      for (int i = 1; i <= lv; ++i) {
        t.push_back(i + l);
      }
      p.push_back(t);
      z = true;
      lzs = lv;
    }

    last = l;
    auto r = wiege(p);
    sort(r.begin(), r.end());
    for (int i = 0; (!z && i < r.size()) || (z && i < r.size() - 1); ++i) {
      int e = r[i] - vs[i];
      res.push_back(e);
      if (e == 1) {
        ones.insert(res.size() - 1);
      } else {
        twos.insert(res.size() - 1);
      }
      if (vzs) {
        vzs--;
        vz -= e;
        if (vzs == 1) {
          res.push_back(vz);
        }
      }
    }
    if (z) {
      lz = r[r.size() - 1];
    } else {
      lz = 0;
      lzs = 0;
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
