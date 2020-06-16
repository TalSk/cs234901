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

vector<vector<ll>> matmul(vector<vector<ll>> A, vector<vector<ll>> B, ll mod) {
  auto n = A.size();
  vector<vector<ll>> res(n, vector<ll>(n, 0));
  for(int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        {
          res[i][j] += (A[i][k] * B[k][j]) % mod;
        }
      }
    }
  }
  return res;
}

ll f(vector<ll> &coeffs, vector<ll> &initial, ll T, ll mod) {
  auto N = initial.size();
  if (T < N) {
    return initial[T] % mod;
  }
  vector<vector<ll>> mat(N + 1, vector<ll>(N + 1, 0));
  for (int i = 0; i + 1 < N + 1; ++i) {
    mat[i][i + 1] = 1;
  }
  for (int i = 0; i < N; ++i) {
    mat[N - 1][i] = coeffs[coeffs.size() - i - 1] % mod;
  }
  mat[N][N] = mat[N - 1][N] = 1;
  vector<vector<ll>> res = mat;
  // Take mat ^ T
  T = T >> 1;
  while(T != 0){
    if((T & 1) == 1){
      res = matmul(res, mat, mod);
    }
    mat = matmul(mat, mat, mod);
    T = T >> 1;
  }
  ll ans = 0;
  for (int k = 0; k < N; ++k) {
    ans += res[0][k] * initial[k] % mod;
  }
  ans += res[0][N] * coeffs[0] % mod;
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
    vector<ll> initial(N);
    for (int j = 0; j < N; ++j) {
      cin >> initial[j];
    }
    ll Q;
    cin >> Q;
    for (int bla = 0; bla < Q; ++bla) {
      ll T, M;
      cin >> T >> M;
      cout << f(coeffs, initial, T, M) << endl;
    }
  }

  return 0;
}