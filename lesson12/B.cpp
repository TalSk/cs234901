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

bool check_bounds(ll i, ll j, ll N) {
  if (i < 0)
    return false;
  if (j < 0)
    return false;
  if (i >= N)
    return false;
  if (j >= N)
    return false;
  return true;
}
pair<pair<pair<ll, ll>, string>, bool> get_f(ll N, vector<vector<char>> &board,
                                             pair<pair<ll, ll>, string> &pos,
                                             ll count) {
  auto out = pos;
  auto c = 0;
  for (int i = 0; i < count; ++i) {
    switch (out.second[0]) {
    case 'v':
      if (check_bounds(out.first.first + 1, out.first.second, N) and
          board[out.first.first + 1][out.first.second] != '#') {
        out.first = {out.first.first + 1, out.first.second};
      }
      break;
    case '^':
      if (check_bounds(out.first.first - 1, out.first.second, N) and
          board[out.first.first - 1][out.first.second] != '#') {
        out.first = {out.first.first - 1, out.first.second};
      }
      break;

    case '>':
      if (check_bounds(out.first.first, out.first.second + 1, N) and
          board[out.first.first][out.first.second + 1] != '#') {
        out.first = {out.first.first, out.first.second + 1};
      }
      break;
    case '<':
      if (check_bounds(out.first.first, out.first.second - 1, N) and
          board[out.first.first][out.first.second - 1] != '#') {
        out.first = {out.first.first, out.first.second - 1};
      }
      break;
    }
    out.second = out.second.substr(1) + out.second[0];
    if (c > N) {
      return {out, false};
    }
    c++;
  }
  return {out, true};
}

pair<pair<pair<ll, ll>, string>, bool>
try_move(ll N, vector<vector<char>> &board, pair<pair<ll, ll>, string> &pos) {
  auto out = pos;
  bool flag = false;
  switch (out.second[0]) {
  case 'v':
    if (check_bounds(out.first.first + 1, out.first.second, N) and
        board[out.first.first + 1][out.first.second] != '#') {
      out.first = {out.first.first + 1, out.first.second};
      flag = true;
    }
    break;
  case '^':
    if (check_bounds(out.first.first - 1, out.first.second, N) and
        board[out.first.first - 1][out.first.second] != '#') {
      out.first = {out.first.first - 1, out.first.second};
      flag = true;
    }
    break;

  case '>':
    if (check_bounds(out.first.first, out.first.second + 1, N) and
        board[out.first.first][out.first.second + 1] != '#') {
      out.first = {out.first.first, out.first.second + 1};
      flag = true;
    }
    break;
  case '<':
    if (check_bounds(out.first.first, out.first.second - 1, N) and
        board[out.first.first][out.first.second - 1] != '#') {
      out.first = {out.first.first, out.first.second - 1};
      flag = true;
    }
    break;
  }
  out.second = out.second.substr(1) + out.second[0];
  if (flag) {
    return {out, true};
  }
  return {out, false};
}

ll find_circle(vector<vector<char>> &board, string &prog, pair<ll, ll> start,
               ll N) {
  pair<pair<ll, ll>, string> turtle = {start, prog};
  pair<pair<ll, ll>, string> hare = {start, prog};
  auto out = get_f(N, board, turtle, 1);
  turtle = out.first;
  if (!out.second) {
    return 1;
  }
  out = get_f(N, board, hare, 2);
  hare = out.first;
  if (!out.second) {
    return 1;
  }
  while (turtle != hare) {
    out = get_f(N, board, turtle, 1);
    turtle = out.first;
    if (!out.second) {
      return 1;
    }
    out = get_f(N, board, hare, 2);
    hare = out.first;
    if (!out.second) {
      return 1;
    }
  }
  hare = {start, prog};
  //  ll mu = 0;
  while (turtle != hare) {
    out = get_f(N, board, turtle, 1);
    turtle = out.first;
    if (!out.second) {
      return 1;
    }
    out = get_f(N, board, hare, 1);
    hare = out.first;
    if (!out.second) {
      return 1;
    }
    //    mu++;
  }
  turtle = hare;
  out = get_f(N, board, turtle, 1);
  turtle = out.first;
  if (!out.second) {
    return 1;
  }
  ull lambda = 1;
  while (turtle != hare) {
    out = try_move(N, board, turtle);
    turtle = out.first;
    if (out.second) {
      lambda++;
    }
  }
  return lambda;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll N;
  while (cin >> N) {
    string prog;
    cin >> prog;
    vector<vector<char>> board(N, vector<char>(N));
    pair<ll, ll> start;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        cin >> board[i][j];
        if (board[i][j] == 'R') {
          board[i][j] = '.';
          start = {i, j};
        }
      }
    }
    cout << find_circle(board, prog, start, N) << endl;
  }
  return 0;
}