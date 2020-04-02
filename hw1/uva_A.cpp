//
// Created by Tal Skverer on 02/04/2020.
//
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

const ull N = 5000000;  // limit for array size
ull n = 2000000;  // array size
ull t[2 * N];

void build() {  // build the tree
  for (ull i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(ull p, ull value) {  // set value at position p
  for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(ull l, ull r) {  // sum on interval [l, r)
  ull res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}

int A() {
  ull m, nn;
  while(cin >> nn){
    // cout << "START" << endl;
    cin >> m;
    if (nn == 0 && m == 0){
      break;
    }
    // Reset array
    for (ull i = 0; i < n; ++i) {
      t[n + i] = 0; // init array
    }
    build();

    ull start, end;
    bool flag = false;
    for (ull j = 0; j < nn; ++j) {
      cin >> start;
      cin >> end;

      // cout << "querying " << start << ", " << end << endl;
      if (query(start, end) != 0){
        // cout << "true " << query(start, end) << endl;
        flag = true;
        break;
      }
      for (ull i = start; i < end; ++i) {
        // cout << "modify " << i << endl;
        modify(i, 1);
      }
    }
    ull repeat;
    for (ull k = 0; k < m; ++k) {
      cin >> start;
      cin >> end;
      cin >> repeat;
      ull base = 0;
      while (base + start <= 1000000){
        // cout << "querying " << base + start << ", " << base + end << endl;
        if (query(base + start, base + end) != 0){
          // cout << "true " << query(base + start, base + end) << endl;
          flag = true;
          break;
        }
        for (ull i = base + start; i < base + end; ++i) {
          modify(i, 1);
        }
        base += repeat;
      }
    }

    if (flag) {
      cout << "CONFLICT" << endl;
    }
    else {
      cout << "NO CONFLICT" << endl;
    }
  }
}