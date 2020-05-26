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

#define MAX_N 200010

class SuffixArray {
private:
  vi RA; // rank array

  void countingSort(int k) {          // O(n)
    int maxi = max(300, n);           // up to 255 ASCII chars
    vi c(maxi, 0);                    // clear frequency table
    for (int i = 0; i < n; ++i)       // count the frequency
      ++c[i + k < n ? RA[i + k] : 0]; // of each integer rank
    for (int i = 0, sum = 0; i < maxi; ++i) {
      int t = c[i];
      c[i] = sum;
      sum += t;
    }
    vi tempSA(n);
    for (int i = 0; i < n; ++i) // sort SA
      tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    swap(SA, tempSA); // update SA
  }

  void constructSA() { // can go up to 400K chars
    SA.resize(n);
    iota(SA.begin(), SA.end(), 0); // the initial SA
    RA.resize(n);
    for (int i = 0; i < n; ++i)
      RA[i] = T[i];                   // initial rankings
    for (int k = 1; k < n; k <<= 1) { // repeat log_2 n times
      // this is actually radix sort
      countingSort(k); // sort by 2nd item
      countingSort(0); // stable-sort by 1st item
      vi tempRA(n);
      int r = 0;
      tempRA[SA[0]] = r;          // re-ranking process
      for (int i = 1; i < n; ++i) // compare adj suffixes
        tempRA[SA[i]] = // same pair => same rank r; otherwise, increase r
            ((RA[SA[i]] == RA[SA[i - 1]]) &&
             (RA[SA[i] + k] == RA[SA[i - 1] + k]))
                ? r
                : ++r;
      swap(RA, tempRA); // update RA
      if (RA[SA[n - 1]] == n - 1)
        break; // nice optimization
    }
  }

  void computeLCP() {
    vi Phi(n);
    vi PLCP(n);
    PLCP.resize(n);
    Phi[SA[0]] = -1;                     // default value
    for (int i = 1; i < n; ++i)          // compute Phi in O(n)
      Phi[SA[i]] = SA[i - 1];            // remember prev suffix
    for (int i = 0, L = 0; i < n; ++i) { // compute PLCP in O(n)
      if (Phi[i] == -1) {
        PLCP[i] = 0;
        continue;
      } // special case
      while ((i + L < n) && (Phi[i] + L < n) && (T[i + L] == T[Phi[i] + L]))
        L++; // L incr max n times
      PLCP[i] = L;
      L = max(L - 1, 0); // L dec max n times
    }
    LCP.resize(n);
    for (int i = 0; i < n; ++i) // compute LCP in O(n)
      LCP[i] = PLCP[SA[i]];     // restore PLCP
  }

public:
  const char *T; // the input string
  const int n;   // the length of T
  vi SA;         // Suffix Array
  vi LCP;        // of adj sorted suffixes

  SuffixArray(const char *_t, const int _n) : T(_t), n(_n) {
    constructSA(); // O(n log n)
    computeLCP();  // O(n)
  }
};

bool has_more_than_m(const vi &SA, ll p, ll m) {
  ll s = 0;
  for (int i = 0; i < SA.size(); ++i) {
    if (SA[i] >= p) {
      s++;
    } else {
      s = 0;
    }
    if (s >= m - 1) {
      return true;
    }
  }
  return false;
}

ll get_rightmost(const vi &SA, const vi &LCP, ll p, ll m){
  ll s = 0;
  int max_index = -1;
  bool f = false;
  for (int i = 0; i < LCP.size(); ++i) {
    if (LCP[i] >= p) {
      s++;
    } else {
      f = false;
      s = 0;
    }
    if (s >= m - 1){
      if (not f){
        for (int j = i - m + 1; j < i; ++j) {
          max_index = max(SA[j], max_index);
        }
      }
      f = true;
      max_index = max(SA[i], max_index);
    }
  }
  return max_index;
}

char T[MAX_N];
char P[MAX_N];
char LRS_ans[MAX_N];
char LCS_ans[MAX_N];

int main() {
  ull m;
  string str;
  ll n;
  while (cin >> m) {
    memset(T, 0, MAX_N);
    if (m == 0) {
      break;
    }

    cin >> str;
    if (m == 1){
      cout << str.size() << " " << 0 << endl;
      continue;
    }
    strncpy(T, str.c_str(), str.size());
    n = (ll)strlen(T);
    T[n++] = '$';

    SuffixArray s(T, n);

    ll low = 0, hi = str.size() - 1, mid;
    while (low < hi - 1) {
      mid = (hi + low) / 2;
      if (has_more_than_m(s.LCP, mid, m)) {
        low = mid;
      } else {
        hi = mid;
      }
    }
    ll ans;
    if (has_more_than_m(s.LCP, mid + 1, m)){
      ans = mid + 1;
    }
    else if (has_more_than_m(s.LCP, mid, m)) {
      ans = mid;
    }
    else if (mid - 1 > 0 and has_more_than_m(s.LCP, mid - 1, m)) {
      ans = mid - 1;
    }
    else {
      cout << "none" << endl;
      continue;
    }
    cout << ans << " " << get_rightmost(s.SA, s.LCP, ans, m) << endl;
  }
  return 0;
}