#include <algorithm>
#include <bits/stdc++.h>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> ii;

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

char T[300001] = {'\0'};

void find_indices(string &text, string &pat, SuffixArray &S, ull n, ll index) {
  vector<ull> found_indices;
  ll orig = index;
  // Go forward
  while (index != S.SA.size()) {
    if (S.LCP[index] < pat.size()) {
      break;
    }
    if (S.SA[index] >= n) {
      index++;
      continue;
    }
    found_indices.push_back(S.SA[index]);
    index++;
  }
  // Go backward
  index = orig - 1;
  while (index >= 0) {
    if (S.LCP[index + 1] < pat.size()) {
      break;
    }
    if (S.SA[index] >= n) {
      index--;
      continue;
    }
    found_indices.push_back(S.SA[index]);
    index--;
  }

  sort(found_indices.begin(), found_indices.end());
  for (int j = 0; j < found_indices.size(); ++j) {
    cout << found_indices[j];
    if (j != found_indices.size() - 1){
      cout << " ";
    }
  }
  cout << endl;
}

int main() {
  int n;

  while (scanf("%i", &n) != EOF) {
    char temp_pattern[100001] = {'\0'};
    vector<string> v_patterns;
    string patterns;

    for (int i = 0; i < n; ++i) {
      scanf(" %[^\r\n]", temp_pattern);
      patterns += temp_pattern;
      v_patterns.emplace_back(temp_pattern);
    }

    char temp_text[200001] = {'\0'};
    scanf(" %[^\r\n]", temp_text);
    string text = temp_text;
    ull x = text.size();
    text += patterns;

    strcpy(T, text.c_str());
    T[text.size()] = '$';          // add terminating symbol
    T[text.size() + 1] = '\0';
    SuffixArray S(T, text.size()); // construct SA+LCP

//        printf("T = '%s'\n", T);
//        printf(" i SA[i] LCP[i]   Suffix SA[i]\n");
//        for (int i = 0; i < text.size(); ++i)
//          printf("%2d    %2d    %2d    %s\n", i, S.SA[i], S.LCP[i],
//          T+S.SA[i]);

    map<ull, ull> s_index_to_sa_index;
    for (int j = 0; j < text.size(); ++j) {
      s_index_to_sa_index[S.SA[j]] = j;
    }

    ull sum = 0;
    for (auto pattern : v_patterns) {
      find_indices(text, pattern, S, x, s_index_to_sa_index[x + sum] + 1);
      sum += pattern.size();
    }
    v_patterns.clear();
    memset(T, '\0', 300001);
    memset(temp_text, '\0', 200001);
    memset(temp_pattern, '\0', 100001);
  }
  return 0;
}