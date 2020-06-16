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

#define UNDEF -1

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<pair<int, int>> vii;
typedef vector<vector<pair<int, int>>> vvii;

int total;
vector<vector<vector<int>>> mem;
int tests, C, in_n1, in_n5, in_n10;

int calc(int have, int n5, int n10) {
  if (mem[have][n5][n10] != UNDEF) {
    return mem[have][n5][n10];
  }
  if (have == C) {
    mem[have][n5][n10] = 0;
    return 0;
  }
  int n1 = total - (8 * have + 10 * n10 + 5 * n5);

  int res = INT16_MAX;
  if (n10 >= 1) {
    res = min(res, calc(have + 1, n5, n10 - 1) + 1);
  }
  if (n10 >= 1 && n1 >= 3) {
    res = min(res, calc(have + 1, n5 + 1, n10 - 1) + 4);
  }
  if (n5 >= 2) {
    res = min(res, calc(have + 1, n5 - 2, n10) + 2);
  }
  if (n5 >= 1 && n1 >= 3) {
    res = min(res, calc(have + 1, n5 - 1, n10) + 4);
  }
  if (n1 >= 8) {
    res = min(res, calc(have + 1, n5, n10) + 8);
  }

  mem[have][n5][n10] = res;
  return res;
}

int main() {
  cin >> tests;
  for (size_t i = 0; i < tests; i++) {
    mem.clear();
    cin >> C >> in_n1 >> in_n5 >> in_n10;
    mem.assign(150 + 1, vector<vi>(150 + 1, vi(50 + 1, UNDEF)));
    total = in_n1 + 5 * in_n5 + 10 * in_n10;
    cout << calc(0, in_n5, in_n10) << endl;
  }

  return 0;
}