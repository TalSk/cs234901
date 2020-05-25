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
typedef vector<vector<ull>> vvu;
typedef vector<ull> vu;
typedef vector<vector<pair<int, int>>> vvii;
typedef vector<pair<int, int>> vii;
typedef pair<int, int> ii;
typedef vector<pair<ull, ull>> vuu;
typedef pair<ull, ull> uu;

bool hasPath(vvu graph, ull src, ull dst){
  // Do BFS to find path from src to dst.
  queue<ull> q;
  q.push(src);
  vector<bool> seen(graph.size(), false);
  seen[src] = true;
  while (!q.empty()){
    ull u = q.front();
    q.pop();
    for (auto v : graph[u]){
      if (!seen[v]){
        if (v == dst){
          return true;
        }
        seen[v] = true;
        q.push(v);
      }
    }
  }
  return false;
}

int main(){
  ull m, n;
  while (cin >> m){
    cin >> n;
    if (n == 0 or m == 0){
      break;
    }
    vvu g(26, vu());
    ull a, b;
    char tmp;
    for (int i = 0; i < m; ++i) {
      cin >> tmp;
      a = tmp - 'a';
      cin >> tmp;
      b = tmp - 'a';
      g[a].push_back(b);
    }

    string word1, word2;
    for (int j = 0; j < n; ++j) {
      cin >> word1 >> word2;
      if (word1.size() != word2.size()){
        cout << "no" << endl;
        continue;
      }
      bool f = true;
      for (int i = 0; i < word1.size(); ++i) {
        if (word1[i] - 'a' == word2[i] - 'a'){
          continue;
        }
        if (not hasPath(g, word1[i] - 'a', word2[i] - 'a')){
          f = false;
          break;
        }
      }
      if (f){
        cout << "yes" << endl;
      }
      else {
        cout << "no" << endl;
      }
    }
  }
  return 0;
}