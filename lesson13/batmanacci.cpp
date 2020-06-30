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
typedef unsigned long long ll;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<pair<int, int>> vii;
typedef vector<vector<pair<int, int>>> vvii;

ll fib(ll N) {
  static long double phipl = (1+sqrt(5))/2;
  static long double phimin = (1-sqrt(5))/2;
  if (N <= 2) return 1;
  //return (fib(N - 1) + fib(N - 2));
  return round((1 / sqrt(5))*(pow(phipl, N) - pow(phimin, N)));
}

int main() {
  ll N, K, fib1, fib2;
  ll fibs[94];
  // use memo
  fibs[0] = 0;
  fibs[1] = 1;
  for (int i = 2; i < 94; i++) {
    fibs[i] = fibs[i - 2] + fibs[i - 1];
  }
  //while (true) {
  cin >> N >> K;
  //cout << "fib N: " << fib(N) << endl;
  if (N > 95) {
    //if (N % 2 == 1) {
    //	N = 94;
    //}
    //else {
    N = 95;
    //}
  }
  while (N > 2) {
    fib1 = fibs[N - 2];
    //fib2 = fib(N - 1);
    if (K <= fib1) {
      N = N - 2;
    }
    else {
      N = N - 1;
      K -= fib1;
    }
    //cout << "N: " << N << " K: " << K << " fib1: " << fib1  << endl;
  }
  if (N == 1) {
    cout << "N" << endl;

  }
  else {
    cout << "A" << endl;

  }
  //}
  return 0;
}