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
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
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

ll n, k;
vector<ll> elevators_times;
map<ll, vector<ll>> floor_to_elevators;

const int INF = 1e9;
// input: non-negatively weighted directed graph (g[u] contains pairs (v,w) such
// that u->v has weight w, nodes are named 0,1,...,|V|-1), source (s). output:
// distances from s (dist). time: O(ElogV).
void Dijkstra(const vvii &g, int s, vi &dist) {
  dist = vi(g.size(), INF);
  dist[s] = 0;
  priority_queue<ii, vii, greater<ii>> q;
  q.push({0, s});
  while (!q.empty()) {
    ii front = q.top();
    q.pop();
    int d = front.first, u = front.second;
    if (d > dist[u])
      continue; // We may have found a shorter way to get to u after inserting
                // it to q.
    // In that case, we want to ignore the previous insertion to q.
    for (ii next : g[u]) {
      int v = next.first, w = next.second;
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        q.push({dist[v], v});
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  while (cin >> n) {
    cin >> k;
    elevators_times.assign(n, 0);
    for (int i = 0; i < n; ++i) {
      cin >> elevators_times[i];
    }
    string temp;
    vvii graph(6000, vii());
    for (int i = 0; i < n; ++i) {
      cin >> ws;
      getline(cin, temp);
      std::stringstream iss(temp);
      ll last = -1;
      for (ll curr; iss >> curr;) {
        if (last != -1) {
          ll last_node, curr_node;
          last_node = 1000 * i + last;
          curr_node = 1000 * i + curr;
          // Connect last node to current node
          graph[last_node].push_back(
              {curr_node, elevators_times[i] * (curr - last)});
          graph[curr_node].push_back(
              {last_node, elevators_times[i] * (curr - last)});
        }
        last = curr;
        if (floor_to_elevators.count(curr) == 0) {
          floor_to_elevators[curr].assign(1, i);
        } else {
          floor_to_elevators[curr].push_back(i);
        }
      }
    }
    for (int i = 0; i < 100; ++i) {
      if (floor_to_elevators.count(i) > 0) {
        // Connect all elevator nodes on this floor with weight 60.
        for (auto &x : floor_to_elevators[i]) {
          for (auto &y : floor_to_elevators[i]) {
            if (x != y) {
              auto x_prime = 1000 * x + i;
              auto y_prime = 1000 * y + i;
              graph[x_prime].push_back({y_prime, 60});
            }
          }
        }
      }
    }

    if (floor_to_elevators.count(0) == 0 or floor_to_elevators.count(k) == 0) {
      cout << "IMPOSSIBLE" << endl;
    }
    int ans = INF;
    for (auto &x : floor_to_elevators[0]) {
      vi dist;
      Dijkstra(graph, 1000 * x + 0, dist);
      for (auto &y : floor_to_elevators[k]) {
        ans = min(ans, dist[1000 * y + k]);
      }
    }

    if (ans == INF) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      cout << ans << endl;
    }
  }
}