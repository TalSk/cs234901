#include <iostream>

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<unsigned long long> vll;
typedef vector<string> vs;
typedef pair<int, int> pii;

typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;


// input: non-negatively weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named 0,1,...,|V|-1), source (s).
// output: distances from s (dist).
// time: O(ElogV).
vector<int> parents;
// input: non-negatively weighted directed graph (g[u] contains pairs (v,w) such
// that u->v has weight w, nodes are named 0,1,...,|V|-1), source (s). output:
// distances from s (dist). time: O(ElogV).
void Dijkstra(const vvii &g, int s, vi &dist) {
  dist = vi(g.size(), INF);
  parents.assign(g.size(), -1);
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
        parents[v] = u;
      }
    }
  }
}

//void getPathInSquares(vvi& rect, vii path){
//    for(auto index = )
//}

int main() {

  int h, w;
  while(true){
    cin >> h >> w;
    if (h == 0) return 0;

    // square (i,j) gets vertices w*i+j*2, w*i+j*2+1. Makor, Bor get h*w, h*w+1
    vvii graph(2 * h * w + 2);

    vvi rect(h, vi(w, 0));
    // get rectangle
    for (int i = 0; i < h; ++i) {
      string line;
      cin >> line;
      for (int j = 0; j < w; ++j) {
        rect[i][j] = line[j] - '0';
      }
    }


    // first line
    for (int j = 0; j < w; ++j) {
      //connect makor
      graph[2*h*w].push_back({j*2, 0});
    }

    // last line
    for (int j = 0; j < w; ++j) {
      // connect bor
      graph[2*w * (h-1) + j*2 + 1].push_back({2*h*w + 1, 0});
    }

    // between quares
    for (int i = 0; i < h; ++i) { // h
      for (int j = 0; j < w; ++j) { // w

        // connect to grid line below
        if (i < h-1){
          graph[2*w*i + j*2 + 1].push_back({2*w*(i+1) + j*2, 0});
          if(j > 0){
            graph[2*w*i + j*2 + 1].push_back({2*w*(i+1) + (j-1)*2, 0});
            graph[2*w*i + j*2 + 1].push_back({2*w*(i) + (j-1)*2, 0});
          }
          if(j < w-1){
            graph[2*w*i + j*2 + 1].push_back({2*w*(i+1) + (j+1)*2, 0});
            graph[2*w*i + j*2 + 1].push_back({2*w*(i) + (j+1)*2, 0});
          }
        }

        // connect to grid line above
        if (i > 0){
          graph[2*w*i + j*2 + 1].push_back({2*w*(i-1) + j*2, 0});
          if(j > 0){
            graph[2*w*i + j*2 + 1].push_back({2*w*(i-1) + (j-1)*2, 0});
          }
          if(j < w-1){
            graph[2*w*i + j*2 + 1].push_back({2*w*(i-1) + (j+1)*2, 0});
          }
        }

        // each square with himself: in -> out
        graph[2*w*i + j*2].push_back({2*w*i + j*2 + 1, rect[i][j]});
      }
    }

    vi dist;
    Dijkstra(graph, 2*h*w, dist);
//        cout << dist[2*h*w+1] << endl;

    int curr = 2*h*w+1;
    vi path;
    while(curr != 2*w*h){
      path.push_back(curr);
      curr = parents[curr];
    }

    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        if(find(path.begin(), path.end(), 2*w*i + j*2) != path.end()){
          cout << " ";
        }
        else{
          cout << rect[i][j];
        }
      }
      cout << endl;
    }

  }

  return 0;
}