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
#include <sstream>
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

#define INF 1000000000
vector<vector<ll>> mem;
vector<string> materials;

ll f(ll i, ll j) {
  if (i > j) {
    return 0;
  }
  if (mem[i][j] != -1) {
    return mem[i][j];
  }
  ll ans = INF;
  ans = min(ans, f(i + 1, j) + 1);

  for (ll x = i + 1; x <= j; ++x) {
    if (materials[i] == materials[x]) {
      ans = min(ans, f(i + 1, x - 1) + f(x, j));
    }
  }
  mem[i][j] = ans;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll T;
  while (cin >> T) {
    for (int aaa = 1; aaa <= T; ++aaa) {
      ll N;
      cin >> N;
      vector<vector<string>> all_mats(N, vector<string>());
      string temp;
      ll c = 0;
      for (int i = 0; i < N; ++i) {
        cin >> temp;
        if (temp[0] >= 'a') {
          all_mats[c].push_back(temp);
        } else {
          c++;
        }
      }
      ll ans = 0;
      for (auto &mat : all_mats) {
        if (mat.empty()) {
          continue;
        }
        int num = 0;
        for (int i = 1; i < mat.size(); i++) {
          if (mat[num] != mat[i])
            ++num;
        }
        materials = mat;
        mem.assign(mat.size() + 1, vector<ll>(mat.size() + 1, -1));
        ans += f(0, num);
      }
      cout << "Case " << aaa << ": " << ans << endl;
    }
  }
}