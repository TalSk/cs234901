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

#define INF 1e14

vector<vector<ll>> mem;
vector<ll> pixels_loc_to_density;
vector<vector<ll>> dist_both_sides;

ll f(ll i, ll k) {
  if (mem[i][k] != -1) {
    return mem[i][k];
  }
  if (k == 0) {
    mem[i][k] = dist_both_sides[i][0];
    return dist_both_sides[i][0];
  }

  ll ans = INF;
  for (ll j = i - 1; j > -1; --j) {
    auto dist = dist_both_sides[j][(i + j) / 2] + dist_both_sides[i][(i + j) / 2 + 1];
    ans = min(ans, f(j, k - 1) + dist);
  }
  mem[i][k] = ans;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll d,k ;
  while (cin >> d) {
    mem.clear();
    pixels_loc_to_density.clear();
    dist_both_sides.clear();
    cin >> k;
    ll r, p;
    pixels_loc_to_density.assign(256, 0);
    for (int i = 0; i < d; ++i) {
      cin >> r >> p;
      pixels_loc_to_density[r] = p;
    }

    dist_both_sides.assign(256, vector<ll>(256, 0));
    for (int i = 0; i < dist_both_sides.size(); ++i) {
      for (int l = i - 1; l > -1; --l) {
        dist_both_sides[i][l] = pow((i - l), 2) * pixels_loc_to_density[l] + dist_both_sides[i][l + 1];
      }
      for (int j = i + 1; j < 256; ++j) {
        dist_both_sides[i][j] = pow((j - i), 2) * pixels_loc_to_density[j] + dist_both_sides[i][j - 1];
      }
    }

    ll ans = INF;
    for (int m = 255; m > -1; --m) {
      mem.assign(256, vector<ll>(k + 1, -1));
      auto cur = f(m, k - 1) + dist_both_sides[m][255];
      if (cur >= 0) {
        ans = min(ans, cur);
      }
    }
    cout << ans << endl;
  }

  return 0;
}