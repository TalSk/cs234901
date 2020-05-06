//
// Created by Tal Skverer on 06/05/2020.
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
typedef vector<ull> vu;
typedef pair<int, int> pii;
typedef vector<vector<pair<ull, ull>>> vvuu;
typedef vector<vector<pair<int, int>>> vvii;
typedef vector<pair<int, int>> vii;
typedef pair<int, int> ii;
typedef vector<pair<ull, ull>> vuu;
typedef pair<ull, ull> uu;

#define INF 1e12

vector<bool> seen;

// Calculate the distance of all cities from the city s up to max_dist distance.
// Assumes d is filled with already-calculated values of distances, and therefore
// can safely ignore any city that is already of distance less than k.
ll DijkstraCountUpToMax(const vvuu & g, ull s, vu& d, ull max_dist){
  ll count = 0;
  d[s] = 0;
  priority_queue<uu, vuu, greater<uu>> q;
  q.push({0, s});
  while (!q.empty()){
    uu front = q.top();
    q.pop();
    ull dist = front.first, u = front.second;
    // Check if found a distance to u that is already shorter
    if (d[u] < dist){
      continue;
    }
    if (seen[u] == false){
      // Seen first time, found a city that is less than distance k
      seen[u] = true;
      count++;
    }
    for (uu next : g[u]){
      ull v = next.first, w = next.second;
      if (d[u] + w < max_dist && d[u] + w < d[v]){
        d[v] = d[u] + w;
        q.push({d[v], v});
      }
    }
  }
  return count;
}

int main(){
  ull n, m, a, k;
  while (cin >> n){
    if (n == 0){
      break;
    }
    cin >> m >> a >> k;
    vvuu g(n);
    ull t1, t2, d;
    for (int i = 0; i < m; ++i) {
      cin >> t1 >> t2 >> d;
      t1--;
      t2--;
      g[t1].push_back({t2, d});
      g[t2].push_back({t1, d});
    }
    ull bi;
    // To count how many cities are true in seen (Shorter computation)
    ll less_than_k = 0;
    // Save cities that were already visited (and therefore are less than distance k)
    seen = vector<bool>(n, false);
    // We will save the shortest distances from any alien city to all other cities
    vu distances(n, INF);
    for (int j = 0; j < a; ++j) {
      cin >> bi;
      bi--;
      less_than_k += DijkstraCountUpToMax(g, bi, distances, k);
      cout << n - less_than_k << endl;
    }
    cout << endl;
  }
  return 0;
}