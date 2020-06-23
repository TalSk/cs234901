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

pair<ll, ll> try_move(pair<ll, ll> &pos, vector<vector<char>> &board,
                      char move) {
  auto next = pos;
  switch (move) {
  case 'v':
    if (board[pos.first + 1][pos.second] != '#') {
      next.first++;
      return next;
    }
    break;
  case '^':
    if (board[pos.first - 1][pos.second] != '#') {
      next.first--;
      return next;
    }
    break;

  case '>':
    if (board[pos.first][pos.second + 1] != '#') {
      next.second++;
      return next;
    }
    break;
  case '<':
    if (board[pos.first][pos.second - 1] != '#') {
      next.second--;
      return next;
    }
    break;
  default:
    assert(false);
  }
  return next;
}

pair<pair<pair<ll, ll>, ll>, bool> advance_by(pair<pair<ll, ll>, ll> &who,
                                              ll count, string &prog,
                                              vector<vector<char>> &board) {
  auto position = who.first;
  auto cur_prog_pos = who.second;
  for (int i = 0; i < count; ++i) {
    auto next_position =
        try_move(position, board, prog[cur_prog_pos % prog.size()]);
    if (next_position == position) {
      count++;
    }
    if (count > prog.size() + 1) {
      // Didn't manage to move after trying to make more than N moves.
      return {{position, cur_prog_pos}, false};
    }
    cur_prog_pos++;
    position = next_position;
  }
  return {{position, cur_prog_pos}, true};
}

string find_circle(vector<vector<char>> &board, string &prog,
                   pair<ll, ll> start) {
  pair<pair<ll, ll>, ll> turtle = {start, 0};
  pair<pair<ll, ll>, ll> hare = {start, 0};

  auto out = advance_by(turtle, 1, prog, board);
  turtle = out.first;
  if (!out.second) {
    return "";
  }
  out = advance_by(hare, 2, prog, board);
  hare = out.first;
  if (!out.second) {
    return "";
  }
  while (turtle.first != hare.first or
         turtle.second % prog.size() != hare.second % prog.size()) {
    out = advance_by(turtle, 1, prog, board);
    turtle = out.first;
    if (!out.second) {
      return "";
    }
    out = advance_by(hare, 2, prog, board);
    hare = out.first;
    if (!out.second) {
      return "";
    }
  }

  hare = {start, 0};
  while (turtle.first != hare.first or
         turtle.second % prog.size() != hare.second % prog.size()) {
    out = advance_by(turtle, 1, prog, board);
    turtle = out.first;
    if (!out.second) {
      return "";
    }
    out = advance_by(hare, 1, prog, board);
    hare = out.first;
    if (!out.second) {
      return "";
    }
  }
  // Right now, if we advance the turtle until we get to the same position,
  // we'll have the full required string. It is difficult to do with the
  // functions we created so for quickness sake, we'll just re-do the required
  // logic.
  turtle = hare;
  // Force advance by one so they're on different positions.
  turtle = advance_by(turtle, 1, prog, board).first;
  // Moves will contain a string of the loop.
  string moves(1, prog[(turtle.second - 1) % prog.size()]);
  auto current_position = turtle.first;
  auto t = turtle.second;
  // Run until we get to the hare's position.
  while (current_position != hare.first or t % prog.size() != hare.second % prog.size()) {
    // Here the move will always work, since we know for a fact there's a loop
    // and the movement is not finite.
    auto next_position = try_move(current_position, board, prog[t % prog.size()]);
    // If we actually moved, add this to the moves string.
    if (next_position != current_position) {
      moves += prog[t % prog.size()];
    }
    t++;
    current_position = next_position;
  }
  return moves;
}
bool mod_equal(string moves, ll count) {
  string sub = moves.substr(0, count);
  for (int i = 0; i < moves.size(); i++) {
    if (sub[i % count] != moves[i]) {
      return false;
    }
  }
  return true;
}

string remove_repeats(string moves) {
  // Go over all divisors of the length of the string (find the largest)
  // for which it is a whole integer multiplication of the original moves,
  // and return its subset.
  for (int i = moves.size(); i >= 1; i--) {
    if (moves.size() % i == 0) {
      auto divisor = moves.size() / i;
      if (mod_equal(moves, divisor)) {
        return moves.substr(0, divisor);
      }
    }
  }
  return moves;
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
    auto actual = find_circle(board, prog, start);
    if (actual.empty()) {
      cout << 1 << endl;
      continue;
    }
    // Try to delete repetitions of the loop.
    actual = remove_repeats(actual);
    if (actual.empty()) {
      cout << 1 << endl;
    } else {
      cout << actual.size() << endl;
    }
  }
  return 0;
}