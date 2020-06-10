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

  SuffixArray(const char *_T, const int _n) : T(_T), n(_n) {
    constructSA(); // O(n log n)
    computeLCP();  // O(n)
  }
};

char T[MAX_N];
char P[MAX_N];
char LRS_ans[MAX_N];
char LCS_ans[MAX_N];

//ull binary_find(string &s, SuffixArray &sa, ull index) {
//  string to_find = s.substr(index);
//  ull low = 0, hi = sa.SA.size(), mid;
//  while (low < hi - 1) {
//    mid = (hi + low) / 2;
//    auto s_prime = s.substr(sa.SA[mid]);
//    if (s_prime < to_find) {
//      low = mid;
//    } else {
//      hi = mid;
//    }
//  }
//  mid = (hi + low) / 2;
//  if (s.substr(sa.SA[mid]) == to_find) {
//    return mid;
//  }
//  if (mid != s.size() and s.substr(sa.SA[mid + 1]) == to_find) {
//    return mid + 1;
//  }
//  if (mid != 0 and s.substr(sa.SA[mid - 1]) == to_find) {
//    return mid - 1;
//  }
//  assert(false);
//}

int minVal(int x, int y) { return (x < y)? x: y; }

int getMid(int s, int e) { return s + (e -s)/2; }

int RMQUtil(int *st, int ss, int se, int qs, int qe, int index)
{
  if (qs <= ss && qe >= se)
    return st[index];

  if (se < qs || ss > qe)
    return INT32_MAX;

  int mid = getMid(ss, se);
  return minVal(RMQUtil(st, ss, mid, qs, qe, 2*index+1),
                RMQUtil(st, mid+1, se, qs, qe, 2*index+2));
}

int RMQ(int *st, int n, int qs, int qe)
{
  if (qs < 0 || qe > n-1 || qs > qe)
  {
    cout<<"Invalid Input";
    return -1;
  }

  return RMQUtil(st, 0, n-1, qs, qe, 0);
}

int constructSTUtil(int arr[], int ss, int se,
                    int *st, int si)
{
  if (ss == se)
  {
    st[si] = arr[ss];
    return arr[ss];
  }

  int mid = getMid(ss, se);
  st[si] = minVal(constructSTUtil(arr, ss, mid, st, si*2+1),
                  constructSTUtil(arr, mid+1, se, st, si*2+2));
  return st[si];
}

int *constructST(int arr[], int n)
{
  int x = (int)(ceil(log2(n)));
  int max_size = 2*(int)pow(2, x) - 1;
  int *st = new int[max_size];

  constructSTUtil(arr, 0, n-1, st, 0);

  return st;
}



int main() {
  string s;
  while (cin >> s) {

    strcpy(T, s.c_str());
    T[s.size()] = '$';
    SuffixArray S(T, s.size() + 1);

    map<ull, ull> index_to_sa;
    for (int l = 0; l < s.size() + 1; ++l) {
      index_to_sa[S.SA[l]] = l;
    }

    auto lcp_array = new int[s.size() + 1];

    for (int m = 0; m < s.size() + 1; ++m) {
      lcp_array[m] = S.LCP[m];
    }

    auto st = constructST(lcp_array, s.size() + 1);

    ull q;
    cin >> q;
    ull i, j;
    for (int k = 0; k < q; ++k) {
      cin >> i >> j;
      auto i_prime = index_to_sa[i];
      auto j_prime = index_to_sa[j];
      auto smaller = min(i_prime, j_prime);
      auto bigger = max(i_prime, j_prime);
      cout << RMQ(st, s.size() + 1, smaller + 1, bigger) << endl;
    }
  }
}