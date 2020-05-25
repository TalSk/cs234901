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

ull min_ink(vi canvasses) {
  // In a case of already-solved cases
  if (canvasses.size() == 1) {
    return 0;
  }
  if (canvasses.size() == 2) {
    return accumulate(canvasses.begin(), canvasses.end(), 0);
  }
  priority_queue<ull, vector<ull>, greater<ull> > min_heap(canvasses.begin(), canvasses.end());
  ull sum = 0;
  while(min_heap.size() > 1){
    ull first = min_heap.top();
//    cout << first << endl;
    min_heap.pop();
    ull second = min_heap.top();
//    cout << second << endl;
    min_heap.pop();
    sum += first + second;
//    cout << sum << endl;
    min_heap.push(first + second);
  }
  return sum;
}

int main() {
  ull T;
  while (cin >> T) {
    for (int i = 0; i < T; ++i) {
      ull N;
      cin >> N;
      vi canvasses(N);
      for (int j = 0; j < N; ++j) {
        cin >> canvasses[j];
      }

      cout << min_ink(canvasses) << endl;
    }
  }
}