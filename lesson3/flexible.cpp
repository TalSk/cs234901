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
  ull W, P;
  while (cin >> W){
    cin >> P;
    vector<ull> locations(P + 2);
    ull cur;
    locations[0] = 0;
    for (int i = 1; i < P + 1; ++i) {
      cin >> cur;
      locations[i] = cur;
    }
    locations[P + 1] = W;
    set<ull> sizes;
    for (int j = 0; j < locations.size(); ++j) {
      for (int i = 0; i < locations.size(); ++i) {
        if (locations[j] > locations[i]){
          sizes.insert(locations[j] - locations[i]);
        }
        else{
          sizes.insert(locations[i] - locations[j]);
        }
      }
    }

    ull i = 0;
    for (auto it = sizes.begin(); it != sizes.end(); ++it) {
      if (*it != 0){
        std::cout << *it;
        if (i != sizes.size() - 1){
          std::cout << " ";
        }
      }
      i++;
    }
    std::cout << endl;

  }
  return 0;
}