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

vector<vector<ll>> matmul(vector<vector<ll>> &a, vector<vector<ll>> &b,
                          ll mod) {
  auto n = a.size();
  vector<vector<ll>> c(n, vector<ll>(n, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        c[i][j] += (a[i][k] * b[k][j]) % mod;
        c[i][j] = c[i][j] % mod;
      }
    }
  }
  return c;
}

ll solveRecurrence(vector<ll> &coeffs_mod, vector<ll> &init_mod, ll T, ll mod) {
  auto N = init_mod.size();
  if (T < N) {
    return init_mod[T] % mod;
  }

  vector<vector<ll>> mat(N + 1, vector<ll>(N + 1, 0));
  for (int i = 2; i < N + 1; ++i) {
    mat[i][i - 1] = 1;
  }
  for (int i = 0; i < N + 1; ++i) {
    mat[1][i] = coeffs_mod[i];
  }
  mat[0][0] = 1;

  vector<vector<ll>> res;
  // Take mat ^ T
  bool flag = true;
  while (T != 0) {
    int b = T % 2;
    T /= 2;
    if (b) {
      if (flag) {
        flag = false;
        res = mat;
      } else {
        res = matmul(res, mat, mod);
      }
    }
    mat = matmul(mat, mat, mod);
  }

  ll ans = 0;
  for (int j = 1; j < N + 1; ++j) {
    ans += (res[N][j] * init_mod[init_mod.size() - j]) % mod;
    ans = ans % mod;
  }
  ans += (res[N][0] * 1) % mod;
  ans = ans % mod;
  return ((ans % mod) + mod) % mod;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll N;
  while (cin >> N) {
    vector<ll> coeffs(N + 1);
    for (int i = 0; i < N + 1; ++i) {
      cin >> coeffs[i];
    }
    vector<ll> init(N);
    for (int j = 0; j < N; ++j) {
      cin >> init[j];
    }
    ll Q;
    cin >> Q;
    for (int bla = 0; bla < Q; ++bla) {
      ll T, M;
      cin >> T >> M;

      vector<ll> coeffs_mod(N + 1);
      for (int i = 0; i < N + 1; ++i) {
        coeffs_mod[i] = ((coeffs[i] % M) + M) % M;
        assert(coeffs_mod[i] >= 0);
      }
      vector<ll> init_mod(N);
      for (int i = 0; i < N; ++i) {
        init_mod[i] = ((init[i] % M) + M) % M;
        assert(init_mod[i] >= 0);
      }

      cout << solveRecurrence(coeffs_mod, init_mod, T, M) << endl;
    }
  }

  return 0;
}