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

vector<vector<ll>> *table;
vector<ll> *costs;
ull N;
#define MAXV INT32_MAX
ll get_cheapest(ll cur, ll prev) {
  if (cur == N) {
    return 0;
  }

  if ((*table)[cur][prev] != -1) {
    return (*table)[cur][prev];
  }

  // Calculate minimum
  ll min1, min2;
  ll step = abs(cur - prev);
  if (cur - step < 1) {
    min1 = MAXV;
  } else {
    min1 = (*costs)[cur - step] + get_cheapest(cur - step, cur);
  }

  if (cur + step + 1 > N) {
    min2 = MAXV;
  } else {
    min2 = (*costs)[cur + step + 1] + get_cheapest(cur + step + 1, cur);
  }

  (*table)[cur][prev] = min(min1, min2);
  return min(min1, min2);
}

int main() {
  while (cin >> N) {
    table = new vector<vector<ll>>(N + 1, vector<ll>(N, -1));

    costs = new vector<ll>(N + 1, 0);
    ull cur;
    for (int i = 1; i < N + 1; ++i) {
      cin >> cur;
      (*costs)[i] = cur;
    }
    cout << get_cheapest(2,1) + (*costs)[2] << endl;
  }
  return 0;
}