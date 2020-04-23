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
typedef pair<int, int> pii;

/*
 * Multiplies a circular matrix by another. Assumes A is already the column-view
 * of the actual matrix A.
 */
vector<ull> multiply(vector<ull> &A, vector<ull> &B, ull mod) {
  int n = A.size();
  assert(n == B.size());
  vector<ull> C(n);

  for (int i = 0; i < n; i++) {
    ull tmp = 0;
    for (int j = 0; j < n; ++j) {
      if (j <= i) {
        tmp += (A[j] * B[i - j]) % mod;
      } else {
        tmp += (A[j] * B[n + (i - j)]) % mod;
      }
      tmp = tmp % mod;
    }
    C[i] = tmp % mod;
  }

  return C;
}

/*
 * Calculates the first column of matrix A.
 */
vector<ull> circ_get_first_column(vector<ull> &A) {
  vector<ull> ret(A.size());
  ret[0] = A[0];
  for (int i = 1; i < A.size(); ++i) {
    ret[i] = A[A.size() - i];
  }
  return ret;
}

// Adapted from the Standford github linked in the presentations.
vector<ull> circ_pow(vector<ull> &A, ull k, ull mod) {
  // Calculates pow(A,k) of a circulant matrix using the fast exponential
  // method we've seen in the lecture, keeping values in the matrix under mod.

  vector<ull> ret(A.size(), 0);
  ret[0] = 1; // Identity circulant matrix.
  // For a circulant matrix multiplication we need to multiply the first column
  // while circulating the rest of the matrix, multiply assumes that and
  // therefore we prepare this here.
  vector<ull> B = circ_get_first_column(A);

  while (k) {
    if (k & 1)
      // If the bit is on, "add" the multiplication of the current circulant
      // matrix to the ret matrix.
      ret = multiply(ret, B, mod);
    B = multiply(B, B, mod);
    k >>= 1;
  }
  return ret;
}

int main() {
  ull T;
  while (cin >> T) {
    for (ull bla = 0; bla < T; ++bla) {
      ull N, S, L, R, X;
      cin >> N >> S >> L >> R >> X;
      vector<ull> nums(N);
      for (int i = 0; i < N; ++i) {
        cin >> nums[i];
      }

      // Create our matrix. Only the row for the first number is needed because
      // it is circulant.
      vector<ull> A(N, 0);
      A[0] = 1;
      A[1] = R;
      A[N - 1] = L;

      // We want to calculate A^k * nums. We will first calculate the power
      auto A_by_S = circ_pow(A, S, (ull)pow(10, X));
      // And then multiply by nums (With it being the first argument, so it is
      // being treated as a column.
      auto out = multiply(nums, A_by_S, (ull)pow(10, X));

      ull n = 0;
      for (auto &num : out) {
        cout << (num % (ull)pow(10, X));
        if (n != N - 1) {
          cout << " ";
        } else {
          cout << endl;
        }
        n++;
      }
    }
  }
  return 0;
}