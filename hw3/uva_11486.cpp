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

using namespace std;
ll N;

// Naive matrix multiplication with modulo.
vector<vector<ll>> matmul(vector<vector<ll>> &A, vector<vector<ll>> &B,
                          ull modulo) {
  vector<vector<ll>> res(A.size(), vector<ll>(A.size(), 0));

  for (int i = 0; i < A.size(); ++i) {
    for (int j = 0; j < A.size(); ++j) {
      for (int k = 0; k < A.size(); ++k) {
        {
          res[i][j] += (A[i][k] * B[k][j]) % modulo;
          res[i][j] = res[i][j] % modulo;
        }
      }
    }
  }
  return res;
}

// Checks whether a move between state i to state j is valid, according to the
// question's rules.
bool valid(pair<pair<pair<ll, ll>, ll>, ll> i,
           pair<pair<pair<ll, ll>, ll>, ll> j) {
  vector<ll> i_players(7, 0);
  vector<ll> j_players(7, 0);
  i_players[i.first.first.first] = 1;
  i_players[i.first.first.second] = 1;
  i_players[i.first.second] = 1;
  i_players[i.second] = 1;
  j_players[j.first.first.first] = 1;
  j_players[j.first.first.second] = 1;
  j_players[j.first.second] = 1;
  j_players[j.second] = 1;

  ll i_index = 0;
  // Iterate forward. This way, whenever we encounter a player we rather it move
  // 'backwards' to check validity.
  while (i_index < 7) {
    if (i_players[i_index]) {
      if (i_index > 0 and j_players[i_index - 1]) {
        i_players[i_index] = 0;
        j_players[i_index - 1] = 0;
      } else if (i_index < 6 and j_players[i_index + 1]) {
        i_players[i_index] = 0;
        j_players[i_index + 1] = 0;
      } else {
        return false;
      }
    }
    i_index++;
  }
  // Sanity checks, after the while loop both player array should be empty.
  for (auto &y : i_players) {
    assert(y == 0);
  }
  for (auto &y : j_players) {
    assert(y == 0);
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull T;
  while (cin >> T) {
    for (int bla = 0; bla < T; ++bla) {
      // Pre-processing: go over all possible states.
      map<pair<pair<pair<ll, ll>, ll>, ll>, ll> state_to_num;
      map<ll, pair<pair<pair<ll, ll>, ll>, ll>> num_to_state;
      ll num = 0;
      for (int p1 = 0; p1 < 7; ++p1) {
        for (int p2 = p1 + 1; p2 < 7; ++p2) {
          for (int p3 = p2 + 1; p3 < 7; ++p3) {
            for (int p4 = p3 + 1; p4 < 7; ++p4) {
              state_to_num[{{{p1, p2}, p3}, p4}] = num;
              num_to_state[num] = {{{p1, p2}, p3}, p4};
              num++;
            }
          }
        }
      }
      // Create the main matrix. This matrix begins as all the valid paths between
      // state i to state j. Then, raising it to the k-th power gives in the cell
      // [i][j] the number of possible paths from state i to state j of length k.
      size_t size = num;
      vector<vector<ll>> matrix(size, vector<ll>(size, 0));
      for (ll i = 0; i < size; ++i) {
        for (ll j = 0; j < size; ++j) {
          auto state_i = num_to_state[i];
          auto state_j = num_to_state[j];
          // 'valid' checks if we can get from state i to state j with one move, by
          // the question's rules.
          if (valid(state_i, state_j)) {
            matrix[i][j] = 1;
          }
        }
      }

      // Get the required N.
      cin >> N;

      // Start with the identity matrix.
      vector<vector<ll>> res(size, vector<ll>(size, 0));
      for (int i = 0; i < size; ++i) {
        res[i][i] = 1;
      }
      // Raise matrix to the power of (N - 1).
      auto mat = matrix;
      auto s = N - 1;
      while (s != 0) {
        int b = s % 2;
        s /= 2;
        if (b) {
          res = matmul(res, mat, 1000000007);
        }
        mat = matmul(mat, mat, 1000000007);
      }

      // Get the starting state from stdin.
      ll tmp;
      pair<pair<pair<ll, ll>, ll>, ll> start;
      vector<ll> non_zeros;
      for (int i = 0; i < 7; ++i) {
        cin >> tmp;
        if (tmp != 0) {
          non_zeros.push_back(i);
        }
      }
      assert(non_zeros.size() == 4);
      start.first.first.first = non_zeros[0];
      start.first.first.second = non_zeros[1];
      start.first.second = non_zeros[2];
      start.second = non_zeros[3];

      // Aggregate the sum of all paths of length N from the starting state
      // to any other state i.
      ll ans = 0;
      for (int i = 0; i < size; ++i) {
        ans = (ans + res[state_to_num[start]][i] % 1000000007) % 1000000007;
      }

      cout << ans << endl;
    }
  }
  return 0;
}