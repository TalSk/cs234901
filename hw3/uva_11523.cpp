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
vector<string> g_materials;

// f(i, j) = The number of moves required to clear the global materials vector
// from index i to index j (inclusive).
ll f(ll i, ll j) {
  if (mem[i][j] != -1) {
    return mem[i][j];
  }
  if (i == j){
    mem[i][j] = 1;
    return 1;
  }
  if (i > j) {
    mem[i][j] = 0;
    return 0;
  }

  ll ans = INF;
  // First, try to clear the first item.
  ans = min(ans, f(i + 1, j) + 1);
  // Second, iterate over all items on the material list.
  for (ll x = i + 1; x <= j; ++x) {
    // If we find a material in position x that is the same as the first item,
    // we can "commit" on throwing away everything between index i+1 and x-1
    // to throw position i and x together.
    if (g_materials[i] == g_materials[x]) {
      // The cost in this case is then throwing i+1 to x-1 plus throwing x to j.
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
    for (int case_num = 1; case_num <= T; ++case_num) {
      ll N;
      cin >> N;
      // A list of list, using the non-recyclable as separators.
      vector<vector<string>> materials_list;

      string temp;
      string last;
      ll current_materials_list = 0;
      materials_list.emplace_back();
      for (int i = 0; i < N; ++i) {
        cin >> temp;
        if (temp[0] >= 'a') {
          // It's a recyclable. Add to current material list.
          if (last != temp) {
            materials_list[current_materials_list].push_back(temp);
          }
          last = temp;
        } else {
          // It's something non-recyclable, create a new list.
          current_materials_list++;
          materials_list.emplace_back();
          last = "";
        }
      }

      ll ans = 0;
      // Go over all partial lists and calculate the minimum number of moves required to clear them.
      for (auto &current_materials : materials_list) {
        if (current_materials.empty()) {
          // Can happen if the last item is a non-recyclable or we have consecutive non-recyclables. Just skip.
          continue;
        }
        g_materials = current_materials;
        mem.assign(current_materials.size() + 1, vector<ll>(current_materials.size() + 1, -1));
        ans += f(0, current_materials.size() - 1);
      }
      cout << "Case " << case_num << ": " << ans << endl;
    }
  }
}