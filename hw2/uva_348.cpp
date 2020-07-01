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

using namespace std;

vector<vector<pair<ll, string>>> mem;
vector<pair<ll, ll>> arrays;

pair<ll, string> f(ll low, ll high) {
  if (mem[low][high].first != -1){
    return mem[low][high];
  }
  if (low == high) {
    return {0, "X"};
  }

  ll ans = INT64_MAX;
  string best_string;
  for (ll i = low; i < high; ++i) {
    auto ret1 = f(low, i);
    auto ret2 = f(i+1, high);
    auto val = ret1.first + (arrays[i].second * arrays[low].first * arrays[high].second) + ret2.first;
    if (val < ans){
      ans = val;
      best_string = "(" + ret1.second + " x " + ret2.second + ")";
    }
  }

  mem[low][high] = {ans, best_string};
  return {ans, best_string};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ull N;
  ull co = 1;
  while (cin >> N) {
    if (N == 0) {
      break;
    }
    mem.clear();
    arrays.clear();
    mem.assign(N, vector<pair<ll, string>>(N, {-1, ""}));
    ll a, b;
    for (int i = 0; i < N; ++i) {
      cin >> a >> b;
      arrays.emplace_back(a, b);
    }
    auto out = f(0, N-1);
//    cout << out.first << endl;
//    cout << out.second << endl;
    ll i = 1;
    cout << "Case " << co << ": ";
    for(auto & c : out.second) {
      if (c == 'X') {
        cout << "A" << i;
        i++;
      }
      else {
        cout << c;
      }
    }
    cout << endl;
    co++;
  }
  return 0;
}