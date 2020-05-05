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

typedef vector<vector<ull>> vvu;             // unweighted
typedef vector<vector<int>> vvi;             // unweighted
typedef vector<vector<pair<int, int>>> vvii; // weighted

vu seen;

ull bfs(const vvu &g, ull s) {
  queue<int> q;
  q.push(s);
  vector<bool> visited(g.size(), false);
  if (seen[s]){
    return 0;
  }
  visited[s] = true;
  ull total = 1;
  seen[s] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : g[u]) {
      if (!visited[v]) {
        if (seen[v] == 1){
          continue;
        }
        visited[v] = true;
        seen[v] = 1;
        total++;
        q.push(v);
      }
    }
  }
  return total;
}

int main() {
  ull t;
  while (cin >> t) {
    for (ull bla = 0; bla < t; ++bla) {
      ull n, m, l;
      cin >> n >> m >> l;
      seen.assign(n, 0);
      vvu g(n, vu());
      ull x, y;
      for (ull i = 0; i < m; ++i) {
        cin >> x >> y;
        x--;
        y--;
        g[x].push_back(y);
      }
      ull total_fell = 0;
      for (ull j = 0; j < l; ++j) {
        cin >> x;
        total_fell += bfs(g, x-1);
      }
      cout << total_fell << endl;


    }
  }
  return 0;
}