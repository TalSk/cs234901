#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
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
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

vector<ull> costs;
enum sol {
  IMP = -2,
  AMB = -1,
};
vector<ll> mem;

#define MAX_COST 30000
void prepare_cost(ull item){
  for (int i = 0; i <= MAX_COST; ++i) {
    if (mem[i] == AMB){
      // If ambiguous, then adding this item will still be ambiguous.
      mem[i + costs[item]] = AMB;
    }
    if (mem[i] >= 0){
      if (mem[i + costs[item]] == IMP){
        // Change to possible using this item.
        mem[i + costs[item]] = item;
      }
      else {
        // It already has an item or AMB. We have ambiguity nevertheless.
        mem[i + costs[item]] = AMB;
      }
    }
  }
}


int main(){
    ull n;
    while(cin >> n){
      costs.assign(n, 0);
      ull temp;
      for (int i = 0; i < n; ++i) {
        cin >> temp;
        costs[i] = temp;
      }

      mem.assign(MAX_COST + 10000, IMP);
      mem[0] = 0;
      for (int item = 0; item < n; ++item) {
        prepare_cost(item);
      }

      ull m;
      cin >> m;
      ll cost;
      for (int j = 0; j < m; ++j) {
        cin >> cost;
        auto ans = mem[cost];
        if (ans == AMB){
          cout << "Ambiguous" << endl;
        }
        else if (ans == IMP){
          cout << "Impossible" << endl;
        }
        else {
          // Iterate backwards on the items
          vector<ull> menu_items;
          menu_items.push_back(ans + 1);
          auto curr_cost = cost - costs[ans];
          while (curr_cost != 0){
            menu_items.push_back(mem[curr_cost] + 1);
            curr_cost -= costs[mem[curr_cost]];
          }
          assert(curr_cost == 0);
          sort(menu_items.begin(), menu_items.end());
          auto i = 0;
          for (auto & x : menu_items){
            cout << x;
            if (i != menu_items.size() - 1){
              cout << " ";
            }
            i++;

          }
          cout << endl;
        }
      }
    }
    return 0;
}