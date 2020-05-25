#include <algorithm>
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

#define TEXT_MAX_SIZE 200001
#define PATTERN_MAX_SIZE 100001
char KMP_str[TEXT_MAX_SIZE]; // The string to search in
char KMP_pat[PATTERN_MAX_SIZE]; // The pattern to search
vi lps;

// KMP Init
void KMP_init(){
  int m = strlen(KMP_pat);
  lps.resize(m+1,0);
  lps[0]=-1;
  int i = 0, j = -1;
  while (i < m) {
    while (j >= 0 && KMP_pat[i] != KMP_pat[j]) j = lps[j];
    i++; j++;
    lps[i] = j;
  }
}

// Search a pattern in a string
// Assuming lps is allready initialized with KMP_init
void KMP_search() {
  int n = strlen(KMP_str);
  int m = strlen(KMP_pat);
  int i = 0, j = 0;
  while (i < n) {
    while (j >= 0 && KMP_str[i] != KMP_pat[j]) j = lps[j];
    i++; j++;
    if (j == m) { // Pattern found
      printf("%d ", i-j);
      j = lps[j];
    }
  }
  printf("\n");
}


int main() {
  int n;

  while (scanf("%i", &n) != EOF){
    char temp_pattern[100001];
    vector<string> patterns;

    for (int i = 0; i < n; ++i) {
      scanf(" %[^\r\n]", temp_pattern);
      patterns.emplace_back(temp_pattern);
    }

    scanf(" %[^\r\n]", KMP_str);
    for (auto& pattern : patterns){
      strcpy(KMP_pat, pattern.c_str());
      KMP_init();
      KMP_search();
    }
  }
  return 0;
}