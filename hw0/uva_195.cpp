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
bool compare(char a, char b) {
  char first = tolower(a);
  char second = tolower(b);
  if (first != second) {
    // Different characters, return who goes first alphabetically to order caps
    // and lower correctly
    return first < second;
  } else {
    // Same letters, capitals comes before lowercase in their ASCII encoding so
    // comparison between the original values should work.
    return a < b;
  }
}

int main() {
  ll num;
  cin >> num;
  string word;
  vector<string> perms;
  while (num) {
    if (!(cin >> word)) {
      break;
    }
    sort(word.begin(), word.end(),
         compare); // Sort string to get the permutations alphabetically
    cout << word << endl;
    while (next_permutation(word.begin(), word.end(), compare)) {
      cout << word << endl;
    }
    num--;
  }
  return 0;
}
}