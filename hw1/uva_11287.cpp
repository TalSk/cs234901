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

#define EPS 1e-7
typedef long long LL;
bool IsPrimeSlow (LL x)
{
  if(x<=1) return false;
  if(x<=3) return true;
  if (!(x%2) || !(x%3)) return false;
  LL s=(LL)(sqrt((double)(x))+EPS);
  for(LL i=5;i<=s;i+=6)
  {
    if (!(x%i) || !(x%(i+2))) return false;
  }
  return true;
}

ull fast_exp_mod(ull a, ull s, ull mod){
  bitset<64> s_bs(s);
  ull cur_a_s = a;
  ull cur_exp = 1;
  for (int i = 0; i < s_bs.size(); ++i) {
    if (s_bs[i] == 1){
      cur_exp *= cur_a_s;
      cur_exp = cur_exp % mod;
    }
    cur_a_s = (cur_a_s * cur_a_s) % mod;
  }
  return cur_exp;
}



int main() {
  ull p, a;
  while (cin >> p) {
    cin >> a;
    if (a == 0 && p == 0){
      break;
    }
    if (IsPrimeSlow(p)){
      cout << "no" << endl;
      continue;
    }
    if (fast_exp_mod(a, p, p) == a){
      cout << "yes" << endl;
    }
    else {
      cout << "no" << endl;
    }

  }
  return 0;

}