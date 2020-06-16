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
typedef long long ll;

ll count_pebbles(const string & board){
  ll pebbles = 0;
  for(auto & c : board){
    if (c == 'o'){
      pebbles++;
    }
  }
  return pebbles;
}

map<string, ll> mem;
ll f(string board) {
  if (mem.count(board)){
    return mem[board];
  }
  auto ans = count_pebbles(board);
  for (int i = 2; i < board.size(); ++i) {
    string updated = board;
    auto a = i;
    auto b = i - 1;
    auto c = i - 2;
    if (board[a] == 'o' and board[b] == 'o' and board[c] == '-'){
      // a eats b
      updated[a] = '-';
      updated[b] = '-';
      updated[c] = 'o';
      ans = min(f(updated), ans);
    }
    if (board[a] == '-' and board[b] == 'o' and board[c] == 'o'){
      // c eats b
      updated[a] = 'o';
      updated[b] = '-';
      updated[c] = '-';
      ans = min(f(updated), ans);
    }
  }
  mem[board] = ans;
  return ans;
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  while(cin >> n){
    for (int bla = 0; bla < n; ++bla) {
      mem.clear();
      string board;
      cin >> board;
      cout << f(board) << endl;
    }
  }
  return 0;
}