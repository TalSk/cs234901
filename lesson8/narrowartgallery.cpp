#include <algorithm>
#include <bitset>
#include <cassert>
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
typedef long long ll;

vector<pair<ull, ull>> values;

enum state { LEFT = 0, RIGHT = 1, OPEN = 2 };

#define INF INT64_MAX;
vector<vector<vector<ll>>> mem;

ull f(ull i, ull k, enum state s) {
  if (mem[i][k][s] != -1){
    return mem[i][k][s];
  }
  ull ans = INF;
  if (k == 0){
    mem[i][k][s] = 0;
    return 0;
  }
  if (i == 0) {
    if (k >= 2) {
      mem[i][k][s] = INF;
      return INF;
    }
    if (k == 1) {
      switch (s) {
      case LEFT:
        mem[i][k][s] = values[i].first;
        return values[i].first;
      case RIGHT:
        mem[i][k][s] = values[i].second;
        return values[i].second;
      case OPEN:
        ans = min(values[i].first, values[i].second);
        mem[i][k][s] = ans;
        return ans;
      }
    }
  }
  if (k > i + 1){
    mem[i][k][s] = INF;
    return INF;
  }
  auto a = f(i - 1, k, OPEN);
  ull b, c;
  switch (s) {
  case LEFT:
    b = f(i - 1, k - 1, LEFT) + values[i].first;
    ans = min(a, b);
    mem[i][k][s] = ans;
    return ans;
  case RIGHT:
    b = f(i - 1, k - 1, RIGHT) + values[i].second;
    ans = min(a, b);
    mem[i][k][s] = ans;
    return ans;
  case OPEN:
    b = f(i - 1, k - 1, LEFT) + values[i].first;
    ans = min(a, b);
    c = f(i - 1, k - 1, RIGHT) + values[i].second;
    ans = min(ans, c);
    mem[i][k][s] = ans;
    return ans;
  }
  assert(false);
}

int main() {
  ull N, k;

  while (cin >> N) {
    cin >> k;
    values.clear();
    ull t1, t2;
    ull sum = 0;
    for (int i = 0; i < N; ++i) {
      cin >> t1 >> t2;
      values.emplace_back(t1, t2);
      sum += t1 + t2;
    }
    cin >> t1 >> t2;
    assert(t1 == 0);
    assert(t2 == 0);

    mem.clear();
    mem.assign(N, vector<vector<ll>>(k + 1, vector<ll>(4, -1)));
    cout << sum - f(N - 1, k, OPEN) << endl;
  }
  return 0;
}