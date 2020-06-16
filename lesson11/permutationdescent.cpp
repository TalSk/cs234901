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

vector<vector<ll>> mem;
ll f(ll N, ll v){
  if (mem[N][v] != -1){
    return mem[N][v];
  }
  if (v == 0 or v == N - 1){
    mem[N][v] = 1;
    return 1;
  }
  auto ans = ((v + 1) * f(N - 1, v) % 1001113 + (N - v) * f(N -1 , v - 1) % 1001113) % 1001113;
  mem[N][v] = ans;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ll P;
  while (cin >> P) {
    for (int bla = 0; bla < P; ++bla) {
      ull K, N, v;
      cin >> K >> N >> v;
      mem.assign(N + 1, vector<ll>(v + 1, -1));
      cout << K << " " << f(N, v) << endl;
    }
  }
  return 0;
}