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

vector<ll> candies;
vector<vector<vector<ll>>> mem;

ll f(ll candy, ll diff_1, ll diff_2) {
  if (candy == -1) {
    return max(diff_1, diff_2);
  }
  if (mem[candy][diff_1][diff_2] != -1){
    return mem[candy][diff_1][diff_2];
  }
  ll ans = INT64_MAX;
  auto weight = candies[candy];
  // Give to max child
  ans = min(ans, f(candy - 1, diff_1 + weight, diff_2 + weight));
  // Give to first child
  auto new_diff_1 = diff_1 - weight;
  if (new_diff_1 < 0) {
    ans = min(ans, f(candy - 1, -new_diff_1, diff_2 - new_diff_1));
  }
  else {
    ans = min(ans, f(candy - 1, new_diff_1, diff_2));
  }
  // Give to second child
  auto new_diff_2 = diff_2 - weight;
  if (new_diff_2 < 0) {
    ans = min(ans, f(candy - 1, diff_1 - new_diff_2 , -new_diff_2));
  }
  else {
    ans = min(ans, f(candy - 1, diff_1, new_diff_2));
  }
  mem[candy][diff_1][diff_2] = ans;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ull T;
  while (cin >> T){
    ll i = 1;
    for (int bla = 0; bla < T; ++bla) {
      ull n;
      cin >> n;
      candies.assign(n, 0);
      mem.assign(n+1, vector<vector<ll>>((n+1) * 20, vector<ll>((n + 1) * 20, -1)));
      for (int i = 0; i < n; ++i) {
        cin >> candies[i];
      }
      cout << "Case " << i << ": " << f(n - 1, 0, 0) << endl;
      i++;
    }
  }
  return 0;
}