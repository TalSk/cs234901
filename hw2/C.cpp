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

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ull n;
  while (cin >> n){
    vector<int> weights(n + 1);
    for (int i = 0; i < n; ++i) {
      cin >> weights[i + 1];
    }

    vvi f(n + 1, vi(2000 + 1, 0));
    for (int i = 1; i <= n; ++i) {
      for (int c = 1; c <= 2000; ++c) {
        if (weights[i] <= c){
          f[i][c] = max(f[i-1][c], weights[i] + f[i-1][c - weights[i]]);
        }
        else {
          f[i][c] = f[i-1][c];
        }
      }
    }
    if (f[n][1000]== 1000) {
      cout << 1000 << endl;
      continue;
    }
    auto lower_dist = 1000 - f[n][1000];

    bool flag = false;
    for (int j = 1001; j <= 1000 + lower_dist; ++j) {
      if (f[n][j] > f[n][1000]){
        cout << f[n][j] << endl;
        flag = true;
        break;
      }
    }
    if (not flag){
      cout << f[n][1000] << endl;
    }
  }
}