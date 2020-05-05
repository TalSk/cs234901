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

bool bfs(const vvi &g, int L, vi &sizes, vi &curr_sizes, int X) {
  queue<int> q;
  q.push(L);
  vector<bool> left(g.size(), false);
  left[L] = true;

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : g[u])
      if (!left[v]) {
        curr_sizes[v]--;
        if (curr_sizes[v] <= (float)sizes[v] / 2) {
          left[v] = true;
          q.push(v);
        }
      }
  }
  return left[X];
}

int main() {
  int C, P, X, L, Ai, Bi;
  cin >> C >> P >> X >> L;
  vvi graph(C + 1, vi(0, 0));
  vi sizes(C + 1, 0);
  vi curr_sizes(C + 1, 0);

  for (size_t i = 0; i < P; i++) {
    cin >> Ai >> Bi;
    graph[Ai].push_back(Bi);
    graph[Bi].push_back(Ai);
    sizes[Ai]++;
    curr_sizes[Ai]++;
    sizes[Bi]++;
    curr_sizes[Bi]++;
  }

  cout << (bfs(graph, L, sizes, curr_sizes, X) ? "leave" : "stay") << endl;
  return 0;
}