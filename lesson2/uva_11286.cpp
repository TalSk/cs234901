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

int main(){
  ull n;
  while(cin >> n) {
    map<string, int> courses;
    for (int i = 0; i < n; ++i) {
      set<int> values;
      int cur;
      for (int j = 0; j < 5; ++j) {
        cin >> cur;
        values.insert(cur);
      }
      string a;
      for (auto x: values){
        a.append(to_string(x));
      }
      courses[a]++;
    }
    int max = 0;
    int countmax = 0;
    for (const auto & x: courses){
      if (x.second > max){
        max = x.second;
        countmax = x.second;
      }
      else if (x.second == max){
        countmax += x.second;
      }
    }
    cout << countmax << endl;
  }
  return 0;
}