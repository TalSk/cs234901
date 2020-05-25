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

namespace segmentTreeA {
const ull N = 5000000; // limit for array size
ull n = 2000000;       // array size
ull t[2 * N];

void reset(ull default_value=0){
  // Reset array
  for (ull i = 0; i < n; ++i) {
    t[n + i] = default_value; // init array
  }
}
void build() { // build the tree
  for (ull i = n - 1; i > 0; --i)
    t[i] = t[i << 1] + t[i << 1 | 1];
}

void modify(ull p, ull value) { // set value at position p
  for (t[p += n] = value; p > 1; p >>= 1)
    t[p >> 1] = t[p] + t[p ^ 1];
}

int query(ull l, ull r) { // sum on interval [l, r)
  ull res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      res += t[l++];
    if (r & 1)
      res += t[--r];
  }
  return res;
}
}

int A() {
  ull m, n;
  while(cin >> n){
    cin >> m;
    if (n == 0 && m == 0){
      break;
    }
    segmentTreeA::reset();
    segmentTreeA::build();

    ull start, end;
    bool flag = false;
    for (ull j = 0; j < n; ++j) {
      cin >> start;
      cin >> end;

      if (segmentTreeA::query(start, end) != 0){
        // Found a collision
        flag = true;
        break;
      }
      // "Occupy" every minute of the current times
      for (ull i = start; i < end; ++i) {
        segmentTreeA::modify(i, 1);
      }
    }

    ull repeat;
    // Not needed if flag is false, but do it anyway to flush the input.
    for (ull k = 0; k < m; ++k) {
      cin >> start;
      cin >> end;
      cin >> repeat;
      ull base = 0;
      // Iterate over repetitions until the start time exceeds the maximum possible.
      while (base + start <= 1000000){
        if (segmentTreeA::query(base + start, base + end) != 0){
          // Found a collision
          flag = true;
          break;
        }
        // "Occupy" every minute of the current times
        for (ull i = base + start; i < base + end; ++i) {
          segmentTreeA::modify(i, 1);
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