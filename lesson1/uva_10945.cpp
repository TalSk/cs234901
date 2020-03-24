#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main(){
  string S;
  while (getline(cin, S)){
    if (S == "DONE"){
      break;
    }
    for_each(S.begin(), S.end(), [](char & c){
      c = ::tolower(c);
    });
    for (int i = 0; i < S.size(); i++) {

      if (S[i] < 'A' || S[i] > 'Z' && S[i] < 'a' || S[i] > 'z')
      {
        S.erase(i, 1);
        i--;
      }
    }

    int i = 0;
    int s = S.size();
    bool f = false;
    if (s % 2 == 1) {
      while (i < s / 2 - 1) {
        if (S[i] != S[S.size() - 1 - i]) {
          f = true;
        }
        i++;
      }
    }

    else {
      while (i < s / 2){
        if (S[i] != S[S.size() - 1 - i]){
          f = true;
        }
        i++;
      }
    }

    if (f){
      cout << "Uh oh.." << endl;
    }
    else {
      cout << "You won't be eaten!" << endl;
    }
  }
  return 0;
}
