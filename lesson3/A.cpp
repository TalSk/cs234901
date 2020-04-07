#include <algorithm>
#include <bitset>
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
typedef vector<int> vi;
typedef pair<int, int> pii;

int main() {
  ull N,T;
  while(cin >> N){
    cin >> T;
    map<ull, vector<ull>> time_to_money;
    ull ci, ti;
    for (int i = 0; i < N; ++i) {
      cin >> ci;
      cin >> ti;
      time_to_money[ti].push_back(ci);
    }


    for (int j = 0; j < T; ++j) {
      sort(time_to_money[j].begin(), time_to_money[j].end());
      reverse(time_to_money[j].begin(), time_to_money[j].end());
    }

    ull total_money = 0;


    for (int k = T - 1; k >= 0; --k) {
      // Find the person with the most money
      ull m = 0;
      int x = -1;
      for (int j = k; j < T; ++j) {
        if (!time_to_money[j].empty()){
          if (time_to_money[j][0] > m) {
            m = time_to_money[j][0];
            x = j;
          }
        }
      }
      if (x == -1){
        continue;
      }
      else{
        total_money += time_to_money[x][0];
        time_to_money[x].erase(time_to_money[x].begin());
      }
    }
    std::cout << total_money << std::endl;
  }
  return 0;
}