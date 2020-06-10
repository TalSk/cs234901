#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;
#define EPS 1e-9

/********** Topological Sort **********/

// input: directed graph (g[u] contains the neighbors of u, nodes are named
// 0,1,...,|V|-1). output: is g a DAG (return value), a topological ordering of
// g (order). comment: order is valid only if g is a DAG. time: O(V+E).
bool topological_sort(const vvi &g, vi &order) {
  // compute indegree of all nodes
  vi indegree(g.size(), 0);
  for (int v = 0; v < g.size(); v++)
    for (int u : g[v])
      indegree[u]++;
  // order sources first
  order = vector<int>();
  for (int v = 0; v < g.size(); v++)
    if (indegree[v] == 0)
      order.push_back(v);
  // go over the ordered nodes and remove outgoing edges,
  // add new sources to the ordering
  for (int i = 0; i < order.size(); i++)
    for (int u : g[order[i]]) {
      indegree[u]--;
      if (indegree[u] == 0)
        order.push_back(u);
    }
  return order.size() == g.size();
}

/********** Strongly Connected Components **********/

const int UNSEEN = -1;
const int SEEN = 1;

void KosarajuDFS(const vvi &g, int u, vi &S, vi &colorMap, int color) {
  // DFS on digraph g from node u:
  // visit a node only if it is mapped to the color UNSEEN,
  // Mark all visited nodes in the color map using the given color.
  // input: digraph (g), node (v), mapping:node->color (colorMap), color
  // (color). output: DFS post-order (S), node coloring (colorMap).
  colorMap[u] = color;
  for (auto &v : g[u])
    if (colorMap[v] == UNSEEN)
      KosarajuDFS(g, v, S, colorMap, color);
  S.push_back(u);
}

// Compute the number of SCCs and maps nodes to their corresponding SCCs.
// input: directed graph (g[u] contains the neighbors of u, nodes are named
// 0,1,...,|V|-1). output: the number of SCCs (return value), a mapping from
// node to SCC color (components). time: O(V+E).
int findSCC(const vvi &g, vi &components) {
  // first pass: record the `post-order' of original graph
  vi postOrder, seen;
  seen.assign(g.size(), UNSEEN);
  for (int i = 0; i < g.size(); ++i)
    if (seen[i] == UNSEEN)
      KosarajuDFS(g, i, postOrder, seen, SEEN);
  // second pass: explore the SCCs based on first pass result
  vvi reverse_g(g.size(), vi());
  for (int u = 0; u < g.size(); u++)
    for (int v : g[u])
      reverse_g[v].push_back(u);
  vi dummy;
  components.assign(g.size(), UNSEEN);
  int numSCC = 0;
  for (int i = (int)g.size() - 1; i >= 0; --i)
    if (components[postOrder[i]] == UNSEEN)
      KosarajuDFS(reverse_g, postOrder[i], dummy, components, numSCC++);
  return numSCC;
}

// Computes the SCC graph of a given digraph.
// input: directed graph (g[u] contains the neighbors of u, nodes are named
// 0,1,...,|V|-1). output: strongly connected components graph of g (sccg).
// time: O(V+E).
void findSCCgraph(const vvi &g, vsi &sccg) {
  vi component;
  int n = findSCC(g, component);
  sccg.assign(n, si());
  for (int u = 0; u < g.size(); u++)
    for (int v : g[u]) // for every edge u->v
      if (component[u] != component[v])
        sccg[component[u]].insert(component[v]);
}

/********** Shortest Paths **********/

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

// input: weighted directed graph (g[u] contains pairs (v,w) such that u->v has
// weight w, nodes are named 0,1,...,|V|-1), source node (s). output: is there a
// negative cycle in g? (return value), the distances from s (d) comment: the
// values in d are valid only if there is no negative cycle. time: O(VE).
bool BellmanFord(const vvii &g, int s, vi &d) {
  d.assign(g.size(), INF);
  d[s] = 0;
  bool changed = false;
  // V times
  for (int i = 0; i < g.size(); ++i) {
    changed = false;
    // go over all edges u->v with weight w
    for (int u = 0; u < g.size(); ++u)
      for (ii e : g[u]) {
        int v = e.first;
        int w = e.second;
        // relax the edge
        if (d[u] < INF && d[u] + w < d[v]) {
          d[v] = d[u] + w;
          changed = true;
        }
      }
  }
  // there is a negative cycle if there were changes in the last iteration
  return changed;
}

// input: weighted directed graph (g[u] contains pairs (v,w) such that u->v has
// weight w, nodes are named 0,1,...,|V|-1). output: the pairwise distances (d).
// time: O(V^3).
void FloydWarshall(const vvii &g, vvi &d) {
  // initialize distances according to the graph edges
  d.assign(g.size(), vi(g.size(), INF));
  for (int u = 0; u < g.size(); ++u)
    d[u][u] = 0;
  for (int u = 0; u < g.size(); ++u)
    for (ii e : g[u]) {
      int v = e.first;
      int w = e.second;
      d[u][v] = min(d[u][v], w);
    }
  // relax distances using the Floyd-Warshall algorithm
  for (int k = 0; k < g.size(); ++k)
    for (int u = 0; u < g.size(); ++u)
      for (int v = 0; v < g.size(); ++v)
        d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
}

/********** Min Spanning Tree **********/

struct unionfind {
  vector<int> rank;
  vector<int> parent;

  unionfind(int size) {
    rank = vector<int>(size, 0);
    parent = vector<int>(size);
    for (int i = 0; i < size; i++)
      parent[i] = i;
  }

  int find(int x) {
    int tmp = x;
    while (x != parent[x])
      x = parent[x];
    while (tmp != x) {
      int remember = parent[tmp];
      parent[tmp] = x;
      tmp = remember;
    }
    return x;
  }

  void unite(int p, int q) {
    p = find(p);
    q = find(q);
    if (q == p)
      return;
    if (rank[p] < rank[q])
      parent[p] = q;
    else
      parent[q] = p;
    if (rank[p] == rank[q])
      rank[p]++;
  }
};

// input: edges v1->v2 of the form (weight,(v1,v2)),
//        number of nodes (n), all nodes are between 0 and n-1.
// output: weight of a minimum spanning tree.
// time: O(ElogV).
int Kruskal(vector<iii> &edges, int n) {
  sort(edges.begin(), edges.end());
  int mst_cost = 0;
  unionfind components(n);
  for (iii e : edges) {
    if (components.find(e.second.first) != components.find(e.second.second)) {
      mst_cost += e.first;
      components.unite(e.second.first, e.second.second);
    }
  }
  return mst_cost;
}

/********** Max Flow **********/

typedef unsigned long long ull;
typedef long long ll;
int augment(vvi &res, int s, int t, const vi &p, int minEdge) {
  // traverse the path from s to t according to p.
  // change the residuals on this path according to the min edge weight along
  // this path. return the amount of flow that was added.
  if (t == s) {
    return minEdge;
  } else if (p[t] != -1) {
    int f = augment(res, s, p[t], p, min(minEdge, res[p[t]][t]));
    res[p[t]][t] -= f;
    res[t][p[t]] += f;
    return f;
  }
  return 0;
}

// input: number of nodes (n), all nodes are between 0 and n-1,
//        edges v1->v2 of the form (weight,(v1,v2)), source (s) and target (t).
// output: max flow from s to t over the edges.
// time: O(VE^2) and O(EF).
ll EdmondsKarp(ll n, vector<iii> &edges, ll s, ll t) {
  // initialise adjacenty list and residuals adjacency matrix
  vvi res(n, vi(n, 0));
  vvi adj(n);
  for (iii e : edges) {
    res[e.second.first][e.second.second] += e.first;
    adj[e.second.first].push_back(e.second.second);
    adj[e.second.second].push_back(e.second.first);
  }
  // while we can add flow
  int addedFlow, maxFlow = 0;
  do {
    // save to p the BFS tree from s to t using only edges with residuals
    vi dist(res.size(), INF);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    vi p(res.size(), -1);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (u == t)
        break;
      for (int v : adj[u])
        if (res[u][v] > 0 && dist[v] == INF) {
          dist[v] = dist[u] + 1;
          q.push(v);
          p[v] = u;
        }
    }
    // add flow on the path between s to t according to p
    addedFlow = augment(res, s, t, p, INF);
    maxFlow += addedFlow;
  } while (addedFlow > 0);
  return maxFlow;
}


long double getDist(ll i, ll j, ll i_tag, ll j_tag,
                    ll height) { // First is floor, last pair is ceiling.
  long double x1 = i + 0.5;
  long double y1 = j + 0.5;
  long double z1 = 0;
  long double x2 = i_tag + 0.5;
  long double y2 = j_tag + 0.5;
  long double z2 = height;
  auto x = x2 - x1;
  auto y = y2 - y1;
  auto z = z2 - z1;
  return x * x + y * y + z * z;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll B, H, R, C;
  while (cin >> B) {
    cin >> H >> R >> C;
    vector<vector<ll>> strengths(R, vector<ll>(C));
    string tmp;
    for (int i = 0; i < R; ++i) {
      cin >> tmp;
      for (int j = 0; j < C; ++j) {
        strengths[i][j] = (int)tmp[j] - 48;
      }
    }
    if (R <= 2 or C <= 2) {
      cout << 0 << endl;
      continue;
    }

    vector<vector<long double>> light(R, vector<long double>(C, 0));
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        for (int i_tag = 0; i_tag < R; ++i_tag) {
          for (int j_tag = 0; j_tag < C; ++j_tag) {
            auto distance = getDist(i, j, i_tag, j_tag, H);
            if (distance == 0){
              light[i][j] += strengths[i][j];
            }
            else {
              light[i][j] += strengths[i_tag][j_tag] / distance;
            }
          }
        }
      }
    }

    // Print light grid. L means that the room is sufficiently lit.
//    for (int k = 0; k < R; ++k) {
//      for (int i = 0; i < C; ++i) {
//
//        cout << light[k][i] << "\t";
//
//      }
//      cout << endl;
//    }
//    for (int k = 0; k < R; ++k) {
//      for (int i = 0; i < C; ++i) {
//        if (light[k][i] >= B){
//          cout << "L ";
//        }
//        else{
//          cout << "D ";
//        }
//
//      }
//      cout << endl;
//    }

    auto source_num = R * C;
    auto target_num = source_num + 1;
    vector<iii> edges;
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        auto cur = i * C + j;
        // Special case - make sure it doesn't happen by generating a time limit error.
        if (fabs(light[i][j] - B) < EPS){
          while (true) {}
        }
        if (i == 0 or j == 0 or i == R - 1 or j == C - 1){
          // Room is on the edge, connect to target.
          edges.push_back({INF, {cur, target_num}});
        }
        else if (light[i][j] < B) {
          // Room is dark, connect from source. It must not be on the edge (guaranteed).
          edges.push_back({INF, {source_num, cur}});
        }
        ll cost;
        if (i > 0) { // Down
          auto other = (i - 1) * C + j;
          cost = 11;
          if (light[i][j] >= B and light[i - 1][j] >= B){
            cost = 43;
          }
          edges.push_back({cost, {cur, other}});
        }
        if (i < R - 1) { // Up
          auto other = (i + 1) * C + j;
          cost = 11;
          if (light[i][j] >= B and light[i + 1][j] >= B){
            cost = 43;
          }
          edges.push_back({cost, {cur, other}});
        }
        if (j > 0) { // Left
          auto other = i * C + (j - 1);
          cost = 11;
          if (light[i][j] >= B and light[i][j - 1] >= B){
            cost = 43;
          }
          edges.push_back({cost, {cur, other}});
        }
        if (j < C - 1) { // Right
          auto other = i * C + (j + 1);
          cost = 11;
          if (light[i][j] >= B and light[i][j + 1] >= B){
            cost = 43;
          }
          edges.push_back({cost, {cur, other}});
        }
      }
    }
    // Print all edges
//    for(auto & x : edges){
//      cout << x.second.first << "->" << x.second.second << ": " << x.first << endl;
//    }
    cout << EdmondsKarp(target_num + 1, edges, source_num, target_num) << endl;

  }

  return 0;
}