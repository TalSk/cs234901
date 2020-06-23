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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ull n;
  while(cin >> n) {
    ull m;
    cin >> m;
    vector<ll> nums(m);
    for (ll i = 0; i < m; ++i) {
      cin >> nums[i];
    }
    vector<bool> mem(n + 1);
    mem[0] = false;
    for (ll stones = 1; stones <= n; ++stones) {
      mem[stones] = false;
      for (int i = 0; i < m; ++i) {
        auto take_possibility = nums[i];
        if (stones >= take_possibility and mem[stones - nums[i]] == false) {
          mem[stones] = true;
          break;
        }
      }
    }
    if (mem[n]){
      cout << "Stan wins" << endl;
    }
    else {
      cout << "Ollie wins" << endl;
    }
  }
  return 0;
}