#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
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

long double dist(pair<ll, ll> a, pair<ll, ll> b) {
  auto y = b.second - a.second;
  auto x = b.first - a.first;
  return sqrt(y * y + x * x);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  map<ll, pair<ll, ll>> real_map;
  ll temp;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      cin >> temp;
      real_map[temp] = {i, j};
    }
  }

  long double s = 0;
  for (int k = 1; k < 9; ++k) {
    auto cur = real_map[k];
    auto next = real_map[k + 1];
    s += dist(cur, next);
  }
  cout << setprecision(15) << s << endl;



  return 0;
}