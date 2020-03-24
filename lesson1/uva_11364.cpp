#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main(){
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
  return 0;
}
