#include <iostream>

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<unsigned long long> vll;
typedef vector<string> vs;
typedef pair<int, int> pii;

char findSmallestchar(string str){
  if (str.find('A') != std::string::npos) return 'A';
  if (str.find('C') != std::string::npos) return 'C';
  if (str.find('G') != std::string::npos) return 'G';
  if (str.find('T') != std::string::npos) return 'T';
}

vi findAllIndexesOf(string str, char c){
  vi indices;
  int idx = 0;
  while(true){
    idx = str.find(c, idx);
    if (idx == std::string::npos){
      return indices;
    }
    indices.push_back(idx);
    idx++;
  }
}

string findString(vector<string> vec){
  string solution = vec[0];
  for (const string& str : vec){
    if (str < solution){
      solution = str;
    }
  }

  return solution;
}

int main() {
  int T;

  cin >> T;

  for(int i = 0; i < T; i++){
    string str;
    cin >> str;

    char c = findSmallestchar(str);
    vi indices = findAllIndexesOf(str, c);

    vector<string> vec;
    for (auto idx : indices){
      vec.push_back(str.substr(idx) + str.substr(0, idx));
    }

    string sol = findString(vec);
    cout << sol << endl;
  }
}