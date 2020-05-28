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

vector<vector<vector<ll>>> mem;

ull f(ull k, ull i, ull j){
  if (i >= j){
    return 0;
  }
  if (k == 1){
    return (j * (j + 1) / 2) - (i * (i + 1) / 2);
  }
  if (mem[k][i][j] != -1){
    return mem[k][i][j];
  }
  ull ans = INT64_MAX;
  for (int l = i + 1; l <= j; ++l) {
    ans = min(ans, l + max(f(k - 1, i, l - 1), f(k, l, j)));
  }
  mem[k][i][j] = ans;
  return ans;
}

int main(){
  ull N;
  while(cin >> N){
    for (int i = 0; i < N; ++i) {
      ull k, m;
      cin >> k >> m;
      mem.assign(11, vector<vector<ll>>(101, vector<ll>(101, -1)));
      cout << f(k, 0, m) << endl;

    }
  }
  return 0;
}