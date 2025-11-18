// #include "munzen.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <bitset>
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

struct domino {
  bool left;
  domino *left_d;
  bool right;
  domino *right_d;
  int w;
  bool w_u;
  domino(int wert) {
    w = wert;
    w_u = false;
    left = false;
    right = false;
    right_d = nullptr;
    left_d = nullptr;
    if (wert == 2) {
      w_u = true;
    } else if (wert == 4) {
      left = true;
      right = true;
      w_u = true;
    }
  }
};

vector<domino> d_map(vector<int> &w) {
  vector<domino> res;

  for (int i = 0; i < w.size(); ++i) {
    domino d(w[i]);
    res.push_back(d);
  }

  return res;
}

bool l_check_right(domino *start, domino *end) {
  cout << " start right d: " << start->right_d << "\n";
  if (start->right_d == nullptr) {
    return start == end;
  }
  return l_check_right(start->right_d, end);
}

bool l_check_left(domino *start, domino *end) {
  cout << " start left d: " << start->left_d << "\n";
  if (start->left_d == nullptr) {
    cout << " > start: " << start << "\n";
    cout << " > end: " << end << "\n";
    return start == end;
  }
  return l_check_left(start->left_d, end);
}

void find(vector<domino> &d, int w, bool u, int count) {
  domino *left_d = nullptr;
  domino *right_d = nullptr;
  bool left = false;
  bool right = false;

  domino *e_right = nullptr;
  domino *e_left = nullptr;

  if (w == 4) {
    left = true;
    right = true;
  }

  cout << "\n WERT: " << w << "\n";

  for (int i = 0; i < d.size(); ++i) {
    if (d[i].w_u) {
      cout << "de wert: " << d[i].w << "\n";
      //        cout << "left d: " << left_d << " de left: " << de.left << "
      //        de left d "
      //             << de.left_d << " c left: " << left << " \n";
      if (left_d == nullptr && (d[i].right == left || !u) &&
          d[i].right_d == nullptr) {

        cout << "check for loop:\n";
        cout << " left d: " << right_d << "\n";
        if (right_d != nullptr && count < d.size() &&
            l_check_left(&d[i], right_d)) {
          cout << "loop detected!! \n";
          continue;
        }

        cout << "found left d \n";
        left_d = &d[i];
        if (!u) {
          u = !u;
          left = d[i].right;
          right = !left;
        }
        if (e_left != nullptr && e_right == nullptr) {
          e_right = e_left;
        }
      } else if (right_d == nullptr && (d[i].left == right || !u) &&
                 d[i].left_d == nullptr) {

        cout << "check for loop:\n";
        cout << " left d: " << left_d << "\n";
        if (left_d != nullptr && count < d.size() &&
            l_check_right(&d[i], left_d)) {
          cout << "loop detected!! \n";
          continue;
        }

        cout << "found right d\n";
        right_d = &d[i];
        if (!u) {
          u = !u;
          right = d[i].left;
          left = !right;
        }
      }
    } else {
      cout << "de has no final positioning: " << d[i].w << "\n";
      if (left_d == nullptr && e_left == nullptr) {
        e_left = &d[i];
        cout << "set e left \n";
      } else if (right_d == nullptr && e_right == nullptr) {
        e_right = &d[i];
        cout << "set e right: " << e_right << " w: " << e_right->w << "\n";
      }
    }
  }

  if (!u) {
    left = true;
    right = false;
    u = true;
  }

  if (left_d == nullptr) {
    if (e_left == nullptr) {
      throw "something went wrong in sort no possible next domino left";
    }
    cout << "left d is null\n";
    left_d = e_left;

    e_left->left = !left;
    e_left->right = left;
    e_left->w_u = true;
  }
  if (right_d == nullptr) {
    if (e_right == nullptr) {
      throw "something went wrong in sort no possible next domino right";
    }
    cout << "right d is null e right: " << e_right << " w " << e_right->w
         << "\n";
    right_d = e_right;

    e_right->right = !right;
    e_right->left = right;
    e_right->w_u = true;
  }

  left_d->right_d = right_d;
  right_d->left_d = left_d;

  cout << " |||: " << left_d->left << " " << left_d->right << " "
       << left_d->right_d->left << " " << left_d->right_d->right << " \n";
}

vector<int> sort(vector<int> &ew, vector<int> &ow) {
  vector<domino> d = d_map(ew);

  int dk = 0;

  int count = 0;

  for (int e : ow) {
    if (e == 3) {
      dk++;
      continue;
    }
    count++;
    find(d, e, true, count);
  }
  for (int i = 0; i < dk; ++i) {
    count++;
    find(d, 3, false, count);
  }

  domino *next = &d[0];

  cout << " ||| >> : " << next->left_d->left << next->left_d->right
       << next->left << next->right << next->right_d->left
       << next->right_d->right << next->right_d->right_d->left
       << next->right_d->right_d->right << " \n";

  cout << "\n";

  vector<int> res;

  int i = 0;
  do {
    cout << i << ": \n"
         << " left: " << next->left << "\n right: " << next->right
         << "\n wert: " << next->w << "\n";

    cout << " >right: " << next->right_d << "\n >left: " << next->left_d
         << " \n";

    cout << next->left << next->right << "\n";

    if (next->left) {
      res.push_back(2);
    } else {
      res.push_back(1);
    }

    if (next->right) {
      res.push_back(2);
    } else {
      res.push_back(1);
    }

    i += 2;
    next = next->right_d;
  } while (next != &d[0]);

  cout << "\n";

  return res;
}

int find_start(bitset<10001> b) {
  vector<int> w = wiege({{0}});
  bitset<10001> ps;
  ps = b;
  if (w[0] == 1) {
    ps.flip();
  }
  return 0;
}

std::vector<int> bestimme_werte(int n) {
  bool odd = false;
  int last = 0;
  if (n % 2 == 1) {
    odd = true;
    last = wiege({{n}})[0];
  }

  // implementiere hier deine Lösung.
  // Mit wiege(std::vector<std::vector<int>> paket) kannst du Abfragen machen.

  vector<vector<int>> e_pairs;
  vector<vector<int>> o_pairs;

  for (int p = 1; p < n; p += 2) {
    e_pairs.push_back({p - 1, p});
    if (p != n - 1) {
      o_pairs.push_back({p, p + 1});
    } else {
      o_pairs.push_back({0, p});
    }
  }

  vector<int> e_pairs_res = wiege(e_pairs);
  vector<int> o_pairs_res = wiege(o_pairs);

  auto c = sort(e_pairs_res, o_pairs_res);
  if (odd) {
    c.push_back(last);
  }

  return c;
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
