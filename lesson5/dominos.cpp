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

typedef vector<vector<ull> > vvu; // unweighted
typedef vector<vector<pair<int, int>>> vvii; // weighted
typedef set<int> si;
typedef vector<si> vsi;
vu fallen;

void dfs(const vvu &g, int s) {
  stack<int> q;
  q.push(s);
  vector<bool> visited(g.size(), false);
  visited[s] = true;
  fallen[s] = 1;
  while (!q.empty()) {
    int u = q.top();
    q.pop();
    for (int v : g[u]) {
      if (!visited[v]) {
        visited[v] = true;
        fallen[v] = 1;
        q.push(v);
      }
    }
  }
}

const int UNSEEN = -1;
const int SEEN = 1;

void KosarajuDFS(const vvu& g, ull u, vi& S, vi& colorMap, int color) {
  // DFS on digraph g from node u:
  // visit a node only if it is mapped to the color UNSEEN,
  // Mark all visited nodes in the color map using the given color.
  // input: digraph (g), node (v), mapping:node->color (colorMap), color (color).
  // output: DFS post-order (S), node coloring (colorMap).
  colorMap[u] = color;
  for (auto& v : g[u])
    if (colorMap[v] == UNSEEN)
      KosarajuDFS(g, v, S, colorMap, color);
  S.push_back(u);
}

// Compute the number of SCCs and maps nodes to their corresponding SCCs.
// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|V|-1).
// output: the number of SCCs (return value), a mapping from node to SCC color (components).
// time: O(V+E).
int findSCC(const vvu& g, vi& components) {
  // first pass: record the `post-order' of original graph
  vi postOrder, seen;
  seen.assign(g.size(), UNSEEN);
  for (ull i = 0; i < g.size(); ++i)
    if (seen[i] == UNSEEN)
      KosarajuDFS(g, i, postOrder, seen, SEEN);
  // second pass: explore the SCCs based on first pass result
  vvu reverse_g(g.size(),vu());
  for (ull u=0; u<g.size(); u++) for (auto v : g[u]) reverse_g[v].push_back(u);
  vi dummy;
  components.assign(g.size(), UNSEEN);
  int numSCC = 0;
  for (ll i = g.size()-1; i >= 0; --i)
    if (components[postOrder[i]] == UNSEEN)
      KosarajuDFS(reverse_g, postOrder[i], dummy, components, numSCC++);
  return numSCC;
}

void findSCCgraph(const vvu& g, vsi& sccg) {
  vi component;
  int n = findSCC(g, component);
  sccg.assign(n, si());
  for (int u=0; u<g.size(); u++) for (int v: g[u]) // for every edge u->v
      if (component[u] != component[v])
        sccg[component[u]].insert(component[v]);
}

int main(){
  ull t;
  while(cin >> t){
    for (ull bla = 0; bla < t; ++bla) {
      ull n, m;
      cin >> n >> m;
      vvu g(n, vu());
      ull x, y;
      for (ull i = 0; i < m; ++i) {
        cin >> x >> y;
        x--;
        y--;
        g[x].push_back(y);
      }

      vsi sccg;
      findSCCgraph(g, sccg);

      vu indegree(sccg.size(), 0);
      for (auto & j : sccg) {
        for (auto v : j){
          indegree[v]++;
        }
      }

      ull s = 0;
      for (int k = 0; k < sccg.size(); ++k) {
        if (indegree[k] == 0){
          s++;
        }
      }

      cout << s << endl;
    }
  }
  return 0;
}