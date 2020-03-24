#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main(){
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
  return 1;
}
