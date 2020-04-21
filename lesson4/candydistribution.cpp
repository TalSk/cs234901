//
// Created by Tal Skverer on 21/04/2020.
//
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

// returns d = gcd(a,b); finds x,y such that d = ax + by
int extended_euclid(ll a, ll b, ll &x, ll &y) {
  ll xx = y = 0;
  ll yy = x = 1;
  while (b) {
    ll q = a/b;
    ll t = b; b = a%b; a = t;
    t = xx; xx = x-q*xx; x = t;
    t = yy; yy = y-q*yy; y = t;
  }
  return a;
}

int mod(int a, int b) {
  return ((a%b) + b) % b;
}

bool coprime(int a, int b) { return __gcd(a, b) == 1; }

int main(){
  ull t;
  while (cin >> t){
    for (int blabla = 0; blabla < t; ++blabla) {
      ll K, C;
      cin >> K;
      cin >> C;
      ll u, v;
      if (K == 1){
        if (C > 2){
          cout << "IMPOSSIBLE" << endl;
        } else {
          cout << "2" << endl;
        }
        continue;
      }
      else if (C == 1) {
        cout << K + 1 << endl;
        continue;
      }
      if (!coprime(K, C)){
        cout << "IMPOSSIBLE" << endl;
        continue;
      }
//      extended_euclid(K, C, u, v);
//      ll x = (u * -1) % C;
//      ll num_candy_bags = (K * (mod(x,  C)) + 1) / C;
      extended_euclid(C, K, u, v);
      ll num_candy_bags = (K + u) % K;
      if (num_candy_bags > pow(10, 9)){
        cout << "IMPOSSIBLE" << endl;
        continue;
      }
      cout << num_candy_bags << endl;
    }
  }
  return 0;
}