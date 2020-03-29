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

int main() {
  ull W, N, w, l;
  while(cin >> W){
      cin >> N;
      ll total_size = 0;
      // Calculate the cumulative sum of each piece's area.
      while (N) {
        cin >> w;
        cin >> l;
        total_size += w * l;
        N--;
      }
      // We now have the area of the whole cake. Divide by the width to get the
      // length. Should return int.
      cout << total_size / W << endl;
  }
  return 0;
}