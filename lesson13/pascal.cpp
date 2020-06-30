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
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<pair<int, int>> vii;
typedef vector<vector<pair<int, int>>> vvii;

bool isPrime(ll n) {
  if (n < 2)
    return false;
  ll sqrtn = sqrt(n);
  for (ll i = 2; i <= sqrtn; ++i) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}


ll biggestDiv(ll n) {
  ll res = 1;
  if (n < 2)
    return n;
  ll sqrtn = sqrt(n);
  for (ll i = 2; i <= sqrtn; ++i) {
    if (n % i == 0) {
      return i;
    }
  }
  return n;
}

int main() {
  ll N, res;
  cin >> N;

  res = N/biggestDiv(N);

  cout << (N-res) << endl;
  return 0;
  //
}