/*
NOTICE:
============
Our team (Noa, Hadas and I) worked on this exercise together while the competition took place
and only small fixes were done afterwards, therefore the code might be similar.
============
*/
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

bool BellmanFord(const vvii& g, int s, vi& d) {
  d.assign(g.size(), INT32_MAX); d[s] = 0;
  bool changed = false;
  // V times
  for (int i = 0; i < g.size(); ++i) {
    changed = false;
    // go over all edges u->v with weight w
    for (int u = 0; u < g.size(); ++u) for (ii e : g[u]) {
        int v = e.first;
        int w = e.second;
        // relax the edge
        if (d[u] < INT32_MAX && d[u] + w < d[v]) {
          d[v] = d[u] + w;
          changed = true;
        }
      }
  }
  // a negative cycle iff changes in the last iteration
  return changed;
}

int main() {
  int W, H, G, X, Y, E, X1, Y1, X2, Y2, T;

  while (cin >> W >> H) {
    if (W == 0) {
      break;
    }
    vvii graph(W*H, vector<pair<int, int>>());
    vi d;
    // fill graph
    for (size_t i = 0; i < W; i++)
    {
      for (size_t j = 0; j < H; j++)
      {
        if (i == W - 1 and j == H - 1){
          continue;
        }
        if (i != W-1)
          graph[i + j * W].emplace_back((i + j * W + 1), 1);

        if (i != 0)
          graph[i + j * W].emplace_back((i + j * W - 1), 1);

        if (j != 0)
          graph[i + j * W].emplace_back((i + (j-1) * W), 1);

        if (j != H-1)
          graph[i + j * W].emplace_back((i + (j+1) * W), 1);
      }

    }

    cin >> G;
    for (size_t k = 0; k < G; k++)
    {
      cin >> X >> Y;
      for (size_t i = 0; i < W; i++) {
        for (size_t j = 0; j < H; j++) {
          for (auto it = graph[i + j * W].begin(); it != graph[i + j * W].end(); ++it) {
            if ((*it).first == (X + Y * W)){
              graph[i + j * W].erase(it);
              break;
            }
          }
        }
      }
    }

    cin >> E;
    for (size_t i = 0; i < E; i++)
    {
      cin >> X1 >> Y1 >> X2 >> Y2 >> T;
      // make portal
      graph[X1 + Y1 * W].clear();
      graph[X1 + Y1 * W].push_back({X2 + Y2 * W, T});
    }

    bool neg_cycle = BellmanFord(graph, 0, d);
    if (neg_cycle) {
      cout << "Never" << endl;
    }
    else if (d[W * H - 1] == INT32_MAX) {
      cout << "Impossible" << endl;
    }
    else {
      cout << d[W * H - 1] << endl;
    }


  }

  return 0;
}