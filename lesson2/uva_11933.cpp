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
  long n;
  while (true){
    cin >> n;
    if (n == 0){
      break;
    }
    bitset<32> bs(n);
    bitset<32> a;
    bitset<32> b;
    uint index = 1;
    for (int i = 0; i < 32; ++i) {
      if (bs.test(0)){
        if (index % 2 == 1){
          a.flip(i);
        }
        else {
          b.flip(i);
        }
        index++;
      }
      bs = bs >> 1;
    }
    cout << a.to_ulong() << " " << b.to_ulong() << endl;
  }
  return 0;
}