#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
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
typedef long long ll;

constexpr long double eps = 1e-6;

long double dist(long double x1, long double y1, long double x2,
                 long double y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

struct unionfind {
  vector<ll> rank;
  vector<ll> parent;
  explicit unionfind(ll size) {
    rank = vector<ll>(size, 0);
    parent = vector<ll>(size);
    for (ll i = 0; i < size; i++)
      parent[i] = i;
  }

  ll find(ll x) {
    ll tmp = x;
    while (x != parent[x])
      x = parent[x];
    while (tmp != x) // for log*, not needed most of the time
    {
      ll remember = parent[tmp];
      parent[tmp] = x;
      tmp = remember;
    }
    return x;
  }
  void Union(ll p, ll q) {
    p = find(p);
    q = find(q);
    if (q == p) {
      // alredy in the same group
      return;
    }
    if (rank[p] < rank[q])
      parent[p] = q;
    else
      parent[q] = p;
    if (rank[p] == rank[q])
      rank[p]++;
  }
};

bool f(
    long double radius, ll w,
    const vector<pair<pair<long double, long double>, long double>> &sensors) {
  // Returns whether fitting a radius in the room is possible.
  // The algorithm is as follows - we first create N+2 groups in a UnionFind structure (N sesnors + 2 walls) 
  // Then, for every sensor point, we interate over all other sensor points. If their radii + the circle we try to fit in collide,
  // this means that we cannot pass it between them, and thus we group them together. We also do this for the current sensor and both walls.
  // After this process, if both walls are still in a different group, this means we can pass a circle with the given radius in the room.
  auto left_wall = sensors.size();
  auto right_wall = sensors.size() + 1;
  auto uf = unionfind(sensors.size() + 2);
  for (ll i = 0; i < sensors.size(); ++i) {
    auto x1 = sensors[i].first.first;
    auto y1 = sensors[i].first.second;
    auto r1 = sensors[i].second;
    for (ll j = i + 1; j < sensors.size(); ++j) {
      auto x2 = sensors[j].first.first;
      auto y2 = sensors[j].first.second;
      auto r2 = sensors[j].second;
      if (dist(x1, y1, x2, y2) < r1 + r2 + radius * 2 + eps) {
        uf.Union(i, j);
      }
    }
    if (x1 < r1 + radius * 2 + eps) {
      uf.Union(left_wall, i);
    }
    if (w - x1 < r1 + radius * 2 + eps) {
      uf.Union(right_wall, i);
    }
  }
  return uf.find(left_wall) != uf.find(right_wall);
}

int main() {
  ull T;
  while (cin >> T) {
    for (int bla = 1; bla <= T; ++bla) {
      long double w;
      cin >> w;
      ll n;
      cin >> n;
      vector<pair<pair<long double, long double>, long double>> sensors(n);
      long double x, y, r = 0;
      for (ll i = 0; i < n; ++i) {
        cin >> x >> y >> r;
        sensors[i] = {{x, y}, r};
      }

      // Binary search for the maximum radius using the defiend boolean function.
      long double low = 0, high = w / 2;
      while (fabs(low - high) > eps) {
        auto mid = (low + high) / 2.0;
        if (f(mid, w, sensors)) {
          // Can pass radius "mid" through the room.
          low = mid;
        } else {
          // Can not pass radius "mid" through the room.
          high = mid;
        }
      }
      auto ans = (low + high) / 2.0;
      printf("%.8Lf\n", ans);
    }
  }
  return 0;
}