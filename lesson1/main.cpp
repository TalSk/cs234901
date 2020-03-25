//
// Created by Tal Skverer on 24/03/2020.
//
#include <algorithm>
#include <vector>
#include <iostream>

typedef long long ll;
typedef long double ld;
using namespace std;

int main1(){
  ll H, U, D;
  ld F;
  while(cin >> H){
    if (H == 0){
      break;
    }
    cin >> U;
    cin >> D;
    cin >> F;

    ld current_height = 0;
    ld factor = (U * (F / 100));
    int day = 0;
    while (current_height >= 0 && current_height <= H){
      if (U - (day * factor) >= 0){
        current_height += U - (day * factor);
      }

      day++;
      if (current_height > H){
        cout << "success on day " << day << endl;
        break;
      }
      current_height -= D;
      if (current_height < 0){
        cout << "failure on day " << day << endl;
      }
    }
  }
}


namespace lesson1 {
  int q1(){
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


  int q2(){
    int num_t;
    cin >> num_t;
    while (num_t){
      int stores;
      cin >> stores;
      vector<int> places;
      int cur;
      for (int i = 0; i < stores; ++i) {
        cin >> cur;
        places.push_back(cur);
      }

      int mi = *min_element(places.begin(), places.end());
      int ma = *max_element(places.begin(), places.end());
      num_t--;
      int mid = (mi + ma) / 2;
      cout << abs(ma - mid) + abs(ma - mi) + abs(mid - mi) << endl;
    }
  }

  void q3(){
    vector<string> words;
    vector<int> times;
    string cur;
    while (true) {

      cin >> cur;
      if (cur == "#") {
        break;
      }
      string cur1 = cur;
      std::transform(cur.begin(), cur.end(), cur.begin(),
                     [](unsigned char c) { return std::tolower(c); });
      sort(cur.begin(), cur.end());
      int i = 0;

      bool f = false;
      for (auto &item : words) {
        string item1 = item;
        std::transform(item1.begin(), item1.end(), item1.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        sort(item1.begin(), item1.end());

        if (item1 == cur) {
          times[i]++;
          f = true;
          break;
        }
        i++;

      }
      if (!f){
        words.push_back(cur1);
        times.push_back(1);
      }


    }

    vector<string> words2;
    for (int j = 0; j < words.size(); ++j) {
      if (times[j] == 1){
        words2.push_back(words[j]);
      }
    }
    sort(words2.begin(), words2.end());

    for (std::vector<string>::const_iterator i = words2.begin(); i != words2.end(); ++i) {
      std::cout << *i << endl;
    }
  }

  void q4(){
    ll H, U, D;
    ld F;
    while(cin >> H){
      if (H == 0){
        break;
      }
      cin >> U;
      cin >> D;
      cin >> F;

      ld current_height = 0;
      ld factor = (U * (F / 100));
      int day = 0;
      while (current_height >= 0 && current_height <= H){
        if (U - (day * factor) >= 0){
          current_height += U - (day * factor);
        }

        day++;
        if (current_height > H){
          cout << "success on day " << day << endl;
          break;
        }
        current_height -= D;
        if (current_height < 0){
          cout << "failure on day " << day << endl;
        }
      }
    }
  }
}


