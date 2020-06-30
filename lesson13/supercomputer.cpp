#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
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
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<pair<int, int>> vii;
typedef vector<vector<pair<int, int>>> vvii;

int n;  // array size
int t[2 * 1000000];

void build() {  // build the tree
  for (int i = n - 1; i > 0; --i) t[i] = t[i << 1] + t[i << 1 | 1];
}

void modify(int p, int value) {  // set value at position p
  for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
}

int query(int l, int r) {  // sum on interval [l, r)
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) res += t[l++];
    if (r & 1) res += t[--r];
  }
  return res;
}

int main() {
  int K, i, l, r, q_res;
  string op;
  cin >> n >> K;
  build();
  for (size_t j = 0; j < K; j++)
  {
    cin >> op;
    if (op == "F") {
      cin >> i;
      i--;
      q_res = query(i, i + 1);
      modify(i, (q_res == 0 ) ? 1 : 0);
    }
    else { // op == C
      cin >> l >> r;
      l--;
      r--;
      cout << query(l, r+1) << endl;
    }
  }

  return 0;
}