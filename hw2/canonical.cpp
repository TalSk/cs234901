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

ull greedy(ull count, vector<ull> & denominations, vector<ull> & mem) {
  for (int i = denominations.size() - 1; i >= 0; --i) {
    if (denominations[i] <= count){
      return mem[count - denominations[i]] + 1;
    }
  }
}

ull dp(ull count, vector<ull> & denominations, vector<ull> & mem){
  ull min_coins = UINT64_MAX;
  for (int i = 0; i < denominations.size(); ++i) {
    if (denominations[i] <= count){
      min_coins = min(min_coins, mem[count - denominations[i]] + 1);
    }
  }
  return min_coins;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ull n;
  while(cin >> n){
    vector<ull> denominations(n);
    for (int i = 0; i < n; ++i) {
      cin >> denominations[i];
    }

    auto sum = denominations[n - 1] + denominations[n - 2];
    vector<ull> mem(sum + 1, 0);
    vector<ull> greedy_mem(sum + 1, 0);

    // Compare greedy vs dp
    bool flag = false;
    for (int j = 1; j <= sum; ++j) {
      auto greedy_res = greedy(j, denominations, greedy_mem);
      greedy_mem[j] = greedy_res;
      auto dp_res = dp(j, denominations, mem);
      mem[j] = dp_res;
      if (greedy_res != dp_res){
        cout << "non-canonical" << endl;
        flag = true;
        break;
      }
    }
    if (not flag){
      cout << "canonical" << endl;
    }
  }

  return 0;
}