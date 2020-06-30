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

vector<vector<char>> bmp;
map<char, string> char_map;
ll H, W;

void bfs(pair<ll, ll> s, char what) {
  queue<pair<ll, ll>> q;
  q.push(s);
  vector<vector<bool>> visited(bmp.size(), vector<bool>(bmp[0].size(), false));
  visited[s.first][s.second] = true;
  bmp[s.first][s.second] = '2';
  while (!q.empty()) {
    auto u = q.front();
    q.pop();

    auto i = u.first;
    auto j = u.second;
    // Left
    if (j > 0 and bmp[i][j - 1] == what and not visited[i][j - 1]) {
      bmp[i][j - 1] = '2';
      visited[i][j - 1] = true;
      q.push({i, j - 1});
    }
    // Right
    if (j < 4 * W - 1 and bmp[i][j + 1] == what and not visited[i][j + 1]) {
      bmp[i][j + 1] = '2';
      visited[i][j + 1] = true;
      q.push({i, j + 1});
    }
    // Up
    if (i > 0 and bmp[i - 1][j] == what and not visited[i - 1][j]) {
      bmp[i - 1][j] = '2';
      visited[i - 1][j] = true;
      q.push({i - 1, j});
    }
    // Down
    if (i < H - 1 and bmp[i + 1][j] == what and not visited[i + 1][j]) {
      bmp[i + 1][j] = '2';
      visited[i + 1][j] = true;
      q.push({i + 1, j});
    }
  }
}

bool getNextOne() {
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W * 4; ++j) {
      if (bmp[i][j] == '1') {
        bfs({i, j}, '1');
        return true;
      }
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  char_map['0'] = "0000";
  char_map['1'] = "0001";
  char_map['2'] = "0010";
  char_map['3'] = "0011";
  char_map['4'] = "0100";
  char_map['5'] = "0101";
  char_map['6'] = "0110";
  char_map['7'] = "0111";
  char_map['8'] = "1000";
  char_map['9'] = "1001";
  char_map['a'] = "1010";
  char_map['b'] = "1011";
  char_map['c'] = "1100";
  char_map['d'] = "1101";
  char_map['e'] = "1110";
  char_map['f'] = "1111";

  ll aaa = 1;
  while (cin >> H) {
    cin >> W;
    if (H == 0 and W == 0) {
      break;
    }
    bmp.assign(H, vector<char>(W * 4));
    string temp;
    for (int i = 0; i < H; ++i) {
      cin >> temp;
      for (int j = 0; j < W; ++j) {
        auto c = temp[j];
        for (int k = 0; k < 4; ++k) {
          bmp[i][4 * j + k] = char_map[c][k];
        }
      }
    }

    for (int j = 0; j < W * 4; ++j) {
      if (bmp[0][j] == '0') {
        bfs({0, j}, '0');
      }
      if (bmp[H - 1][j] == '0') {
        bfs({H - 1, j}, '0');
      }
    }
    for (int i = 0; i < H; ++i) {
      if (bmp[i][0] == '0') {
        bfs({i, 0}, '0');
      }
      if (bmp[i][4 * W - 1] == '0') {
        bfs({i, 4 * W - 1}, '0');
      }
    }
    vector<char> out;
    while (getNextOne()) {
      ll num_circles = 0;
      for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W * 4; ++j) {
          if (bmp[i][j] == '0') {
            // Check that it's next to something that has already been
            // processed.
            if ((i > 0 and bmp[i - 1][j] == '2') or
                (j > 0 and bmp[i][j - 1] == '2') or
                (i < H - 1 and bmp[i + 1][j] == '2') or
                (j < 4 * W - 1 and bmp[i][j + 1] == '2')) {
              bfs({i, j}, '0');
              num_circles++;
            }
          }
        }
      }
      switch (num_circles) {
      case 0:
        out.push_back('W');
        break;
      case 1:
        out.push_back('A');
        break;
      case 2:
        out.push_back('K');
        break;
      case 3:
        out.push_back('J');
        break;
      case 4:
        out.push_back('S');
        break;
      case 5:
        out.push_back('D');
        break;
      default:
        assert(false);
      }
    }
    sort(out.begin(), out.end());
    cout << "Case " << aaa << ": ";
    for (const auto &x : out) {
      cout << x;
    }
    cout << endl;
    aaa++;
  }
  return 0;
}