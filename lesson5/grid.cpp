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
typedef vector<vector<int> > vvi; // unweighted
typedef vector<vector<pair<int, int>>> vvii; // weighted

void bfs(const vvu &g, int s, vector<int> & d) {
  queue<int> q;
  q.push(s);
  vector<bool> visited(g.size(), false);
  visited[s] = true;
  d.assign(g.size(), -1);
  d[s] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : g[u]) {
      if (!visited[v]) {
        visited[v] = true;
        d[v] = d[u] + 1;
        q.push(v);
      }
    }
  }
}


int main(){
  ull n, m;
  while(cin >> n){
    cin >> m;
    string in;
    vi vec(n * m);
    for (int i = 0; i < n; ++i) {
      cin >> in;
      for (int j = 0; j < m; ++j) {
        vec[(i * m) + j] = (char)in[j] - '0';
      }
    }
    vvu g(m * n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        int dist = vec[(i * m) + j];
        // Right
        if (j + dist < m) {
          g[(i * m) + j].push_back((i * m) + (j + dist));
        }
        // Left
        if (j - dist >= 0) {
          g[(i * m) + j].push_back((i * m) + (j - dist));
        }
        // Up
        if (i + dist < n) {
          g[(i * m) + j].push_back(((i + dist) * m) + j);
        }
        // Down
        if (i - dist >= 0) {
          g[(i * m) + j].push_back(((i - dist) * m) + j);
        }

      }
    }
    vi d;
    bfs(g, 0, d);
    cout << d[m * n - 1] << endl;
  }
  return 0;
}