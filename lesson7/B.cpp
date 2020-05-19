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

#define MAX_LEN 60
char key[5][5];
vector<pair<int, int>> char_to_index(26, {0, 0});

void generate_key(const char *keyword) {
  // keyword is uppercase without spaces.
  vector<bool> seen(26, false);
  vector<char> t_key;
  for (int i = 0; i < strlen(keyword); ++i) {
    char cur = keyword[i];
    if (cur == 'J') {
      cur = 'I';
    }
    if (not seen[cur - 'A']) {
      t_key.push_back(cur);
      seen[cur - 'A'] = true;
    }
  }
  for (int j = 0; j < seen.size(); ++j) {
    if (seen[j] == false and (char)('A' + j) != 'J') {
      t_key.push_back((char)('A' + j));
    }
  }
  assert(t_key.size() == 25);
  for (int k = 0; k < 5; ++k) {
    for (int i = 0; i < 5; ++i) {
      key[k][i] = t_key[5 * k + i];
      char_to_index[t_key[5 * k + i]] = {k, i};
    }
  }
}

char out[MAX_LEN];

const char *decrypt(const char *cipher) {
  memset(out, 0, MAX_LEN);
  int pos = 0;
  for (int i = 0; i < strlen(cipher);) {
    char first = cipher[i] == 'J' ? 'I' : cipher[i];
    char second;
    if (i + 1 == strlen(cipher)) {
      second = 'X';
    } else {
      second = cipher[i + 1] == 'J' ? 'I' : cipher[i + 1];
      if (second == first) {
        second = 'X';
      } else {
        i++;
      }
    }
    i++;
    if (first == 'X' and second == 'X') {
      out[pos] = 'Y';
      pos++;
      out[pos] = 'Y';
      pos++;
    } else {
      auto first_index = char_to_index[first];
      auto second_index = char_to_index[second];
      if (first_index.first == second_index.first) {
        // Same row.
        out[pos] = key[first_index.first][(first_index.second + 1) % 5];
        pos++;
        out[pos] = key[second_index.first][(second_index.second + 1) % 5];
        pos++;
      } else if (first_index.second == second_index.second) {
        // Same column.
        out[pos] = key[(first_index.first + 1) % 5][second_index.second];
        pos++;
        out[pos] = key[(second_index.first + 1) % 5][second_index.second];
        pos++;
      } else {
        out[pos] = key[first_index.first][second_index.second];
        pos++;
        out[pos] = key[second_index.first][first_index.second];
        pos++;
      }
    }
  }
  return out;
}

int main() {
  ll n;
  while (cin >> n) {
    if (n == 0) {
      break;
    }
    vector<string> plains;
    string curr;
    cin >> ws;
    getline(cin, curr);
    curr.erase(remove_if(curr.begin(), curr.end(), ::isspace), curr.end());
    transform(curr.begin(), curr.end(), curr.begin(), ::toupper);
    generate_key(curr.c_str());

    for (int i = 0; i < n; ++i) {
      getline(cin, curr);
      curr.erase(remove_if(curr.begin(), curr.end(), ::isspace), curr.end());
      transform(curr.begin(), curr.end(), curr.begin(), ::toupper);
      plains.push_back(curr);
    }

    for (int j = 0; j < n; ++j) {
      cout << decrypt(plains[j].c_str()) << endl;
    }
  }
  return 0;
}