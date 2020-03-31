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
  // Minimum queue to take each time 2 numbers and sum their values.
  ull N;
  priority_queue<ull, vector<ull>, greater<ull>> min_heap;
  while (cin >> N) {
    while (!min_heap.empty()) {
      min_heap.pop();
    }
    ull curr;
    for (int i = 0; i < N; ++i) {
      cin >> curr;
      min_heap.push(curr);
    }
    ull sum = 0;
    while (true){
      // Get two least numbers
      ull min1, min2;
      min1 = min_heap.top();
      min_heap.pop();
      min2 = min_heap.top();
      min_heap.pop();
      sum += min1 + min2;
      if (min_heap.empty()) {
        cout << sum << endl;
        break;
      }
      min_heap.push(min1 + min2);
    }
  }
  return 0;
}