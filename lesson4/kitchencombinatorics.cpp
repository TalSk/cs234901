/*
NOTICE:
============
Our team (Noa, Hadas and I) worked on this exercise together while the competition took place
and only small fixes were done afterwards, therefore the code might be similar.
============
*/
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
typedef pair<int, int> pii;

int main() {
  ull r, s, m, d, n;
  while (cin >> r) {
    // Get input
    cin >> s >> m >> d >> n;
    vector<ull> ingredient_brands(r);
    vector<vector<ull>> starters(s);
    vector<vector<ull>> mains(m);
    vector<vector<ull>> desserts(d);
    set<pair<ull, ull>> intersecting_pairs;
    for (int i = 0; i < r; ++i) {
      cin >> ingredient_brands[i];
    }
    ull num_ingr;
    ull tmp;
    for (int j = 0; j < s; ++j) {
      cin >> num_ingr;
      for (int i = 0; i < num_ingr; ++i) {
        cin >> tmp;
        starters[j].push_back(tmp - 1);
      }
    }
    for (int j = 0; j < m; ++j) {
      cin >> num_ingr;
      for (int i = 0; i < num_ingr; ++i) {
        cin >> tmp;
        mains[j].push_back(tmp - 1);
      }
    }
    for (int j = 0; j < d; ++j) {
      cin >> num_ingr;
      for (int i = 0; i < num_ingr; ++i) {
        cin >> tmp;
        desserts[j].push_back(tmp - 1);
      }
    }
    ull first, second;
    for (int l = 0; l < n; ++l) {
      cin >> first >> second;
      intersecting_pairs.insert({first - 1, second - 1});
      intersecting_pairs.insert({second - 1, first - 1});
    }
    // === After input ===

    ull answer = 0;
    ull c;
    set<ull> chosen_ingr;

    for (int k = 0; k < s; ++k) {
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < d; ++j) {
          // Check conflicts
          if ((intersecting_pairs.find({k, s + i}) != intersecting_pairs.end()) ||
              (intersecting_pairs.find({k, s + m + j}) != intersecting_pairs.end()) ||
              (intersecting_pairs.find({s + i, s + m + j}) != intersecting_pairs.end())){
            continue;
          }
          chosen_ingr.clear();
          for (auto& ingredient : starters[k]){
            chosen_ingr.insert(ingredient);
          }
          for (auto& ingredient : mains[i]){
            chosen_ingr.insert(ingredient);
          }
          for (auto& ingredient : desserts[j]){
            chosen_ingr.insert(ingredient);
          }
          c = 1;
          for (auto & ingredient : chosen_ingr){
            if (c > (long double)(pow(10, 18) / ingredient_brands[ingredient])){
              cout << "too many" << endl;
              return 0;
            }
            c *= ingredient_brands[ingredient];
          }
          answer += c;
          if (answer > (long double)pow(10, 18)){
            cout << "too many" << endl;
            return 0;
          }
        }
      }
    }

    cout << answer << endl;
  }
  return 0;
}