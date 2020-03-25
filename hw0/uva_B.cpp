//
// Created by Tal Skverer on 25/03/2020.
//
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

namespace uva_B {
int main() {
  ll num;
  cin >> num;
  string word;
  vector<string> perms;
  while (num) {
    cin >> word;
    sort(word.begin(),
         word.end()); // Sort string to get the permutations alphabetically
    do {
      cout << word << endl;
    } while (next_permutation(word.begin(), word.end()));
    num--;
  }
  return 0;
}
} // namespace uva_B