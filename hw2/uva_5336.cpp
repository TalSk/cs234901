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

int main(){
  string a, b;
  bool first = false;
  while (cin >> a){
    if (first){
      cout << endl;
    }
    cin >> b;
    string c = a + "@" + b + "$";
    SuffixArray S(c.c_str(), c.size() - 1);
    ull current_max = 0;
    vector<ull> indices;
    for (int i = 0; i < S.SA.size() - 1; ++i) {
      if (S.LCP[i + 1] < current_max){
        continue;
      }
      string x, y;
      x = c.substr(S.SA[i]);
      y = c.substr(S.SA[i + 1]);
      if ((x.find('@') != string::npos and y.find('@') == string::npos) or (x.find('@') == string::npos and y.find('@') != string::npos)){
        if (S.LCP[i + 1] > current_max){
          current_max = S.LCP[i + 1];
          indices.clear();
        }
        indices.push_back(S.SA[i + 1]);
      }
    }
    set<string> setset;
    if (current_max == 0){
      cout << "No common sequence." << endl;
    }
    else {
      for(auto &index: indices){
        setset.insert(c.substr(index, current_max));
      }
      for (auto& ababa : setset){
        cout << ababa << endl;
      }
    }
    first = true;
    cin >> ws;
  }
  return 0;
}