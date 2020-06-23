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

enum Turn {
  MAX,
  MIN
};

#define INF 1e8

map<pair<string, Turn>, ll> mem;

string boardToString(vector<vector<ll>> board) {
  string out;
  for (int i = 0; i < board.size(); ++i) {
    for (int j = 0; j < board[i].size(); ++j) {
      out.append(to_string(board[i][j]));
      out.append(",");
    }
    out.append(("\n"));
  }
  return out;
}

ll minimax(vector<vector<ll>> & board, Turn turn) {
  if (mem.count({boardToString(board), turn}) > 0){
    return mem[{boardToString(board), turn}];
  }

  ll ans = turn == MAX ? -INF: INF;
  bool flag = false;

  for (int i = 0; i < board.size(); ++i) {
    for (int j = 0; j <= i; ++j) {
      // Test if position i,j can jump over the empty spot.
      if (board[i][j] == 0) {
        // This is the empty spot
        continue;
      }
      ull temp_i_f, temp_j_f;
      ull temp_i_m, temp_j_m;
      // Up right
      temp_i_f = i - 2;
      temp_j_f = j;
      temp_i_m = i - 1;
      temp_j_m = j;
      if (temp_i_f >= 0 and temp_i_f < board.size() and temp_j_f <= temp_i_f and temp_j_f >= 0){
        if (board[temp_i_f][temp_j_f] == 0 and board[temp_i_m][temp_j_m] != 0){
          // Can jump
          flag = true;
          auto temp_board = board;
          auto val1 = temp_board[i][j];
          auto val2 = temp_board[temp_i_m][temp_j_m];
          temp_board[i][j] = 0;
          temp_board[temp_i_m][temp_j_m] = 0;
          temp_board[temp_i_f][temp_j_f] = val1;
          if (turn == MAX){
            ans = max(ans, val1 * val2 + minimax(temp_board, MIN));
          }
          else {
            ans = min(ans, -val1 * val2 + minimax(temp_board, MAX));
          }
        }
      }

      // Up left
      temp_i_f = i - 2;
      temp_j_f = j - 2;
      temp_i_m = i - 1;
      temp_j_m = j - 1;
      if (temp_i_f >= 0 and temp_i_f < board.size() and temp_j_f <= temp_i_f and temp_j_f >= 0){
        if (board[temp_i_f][temp_j_f] == 0 and board[temp_i_m][temp_j_m] != 0){
          // Can jump
          flag = true;
          auto temp_board = board;
          auto val1 = temp_board[i][j];
          auto val2 = temp_board[temp_i_m][temp_j_m];
          temp_board[i][j] = 0;
          temp_board[temp_i_m][temp_j_m] = 0;
          temp_board[temp_i_f][temp_j_f] = val1;
          if (turn == MAX){
            ans = max(ans, val1 * val2 + minimax(temp_board, MIN));
          }
          else {
            ans = min(ans, -val1 * val2 + minimax(temp_board, MAX));
          }
        }
      }

      // Right
      temp_i_f = i;
      temp_j_f = j + 2;
      temp_i_m = i;
      temp_j_m = j + 1;
      if (temp_i_f >= 0 and temp_i_f < board.size() and temp_j_f <= temp_i_f and temp_j_f >= 0){
        if (board[temp_i_f][temp_j_f] == 0 and board[temp_i_m][temp_j_m] != 0){
          // Can jump
          flag = true;
          auto temp_board = board;
          auto val1 = temp_board[i][j];
          auto val2 = temp_board[temp_i_m][temp_j_m];
          temp_board[i][j] = 0;
          temp_board[temp_i_m][temp_j_m] = 0;
          temp_board[temp_i_f][temp_j_f] = val1;
          if (turn == MAX){
            ans = max(ans, val1 * val2 + minimax(temp_board, MIN));
          }
          else {
            ans = min(ans, -val1 * val2 + minimax(temp_board, MAX));
          }
        }
      }

      // Left
      temp_i_f = i;
      temp_j_f = j - 2;
      temp_i_m = i;
      temp_j_m = j - 1;
      if (temp_i_f >= 0 and temp_i_f < board.size() and temp_j_f <= temp_i_f and temp_j_f >= 0){
        if (board[temp_i_f][temp_j_f] == 0 and board[temp_i_m][temp_j_m] != 0){
          // Can jump
          flag = true;
          auto temp_board = board;
          auto val1 = temp_board[i][j];
          auto val2 = temp_board[temp_i_m][temp_j_m];
          temp_board[i][j] = 0;
          temp_board[temp_i_m][temp_j_m] = 0;
          temp_board[temp_i_f][temp_j_f] = val1;
          if (turn == MAX){
            ans = max(ans, val1 * val2 + minimax(temp_board, MIN));
          }
          else {
            ans = min(ans, -val1 * val2 + minimax(temp_board, MAX));
          }
        }
      }

      // Down right
      temp_i_f = i + 2;
      temp_j_f = j + 2;
      temp_i_m = i + 1;
      temp_j_m = j + 1;
      if (temp_i_f >= 0 and temp_i_f < board.size() and temp_j_f <= temp_i_f and temp_j_f >= 0){
        if (board[temp_i_f][temp_j_f] == 0 and board[temp_i_m][temp_j_m] != 0){
          // Can jump
          flag = true;
          auto temp_board = board;
          auto val1 = temp_board[i][j];
          auto val2 = temp_board[temp_i_m][temp_j_m];
          temp_board[i][j] = 0;
          temp_board[temp_i_m][temp_j_m] = 0;
          temp_board[temp_i_f][temp_j_f] = val1;
          if (turn == MAX){
            ans = max(ans, val1 * val2 + minimax(temp_board, MIN));
          }
          else {
            ans = min(ans, -val1 * val2 + minimax(temp_board, MAX));
          }
        }
      }

      // Down left
      temp_i_f = i + 2;
      temp_j_f = j;
      temp_i_m = i + 1;
      temp_j_m = j;
      if (temp_i_f >= 0 and temp_i_f < board.size() and temp_j_f <= temp_i_f and temp_j_f >= 0){
        if (board[temp_i_f][temp_j_f] == 0 and board[temp_i_m][temp_j_m] != 0){
          // Can jump
          flag = true;
          auto temp_board = board;
          auto val1 = temp_board[i][j];
          auto val2 = temp_board[temp_i_m][temp_j_m];
          temp_board[i][j] = 0;
          temp_board[temp_i_m][temp_j_m] = 0;
          temp_board[temp_i_f][temp_j_f] = val1;
          if (turn == MAX){
            ans = max(ans, val1 * val2 + minimax(temp_board, MIN));
          }
          else {
            ans = min(ans, -val1 * val2 + minimax(temp_board, MAX));
          }
        }
      }
    }
  }
  if (not flag){
    // Didn't jump
    mem[{boardToString(board), turn}] = 0;
    return 0;
  }
  mem[{boardToString(board), turn}] = ans;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  mem.clear();
  vector<vector<ll>> board(5);
  ll temp;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j <= i; ++j) {
      cin >> temp;
      board[i].push_back(temp);
    }
  }
  cout << minimax(board, MAX) << endl;

  return 0;
}