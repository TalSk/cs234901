#include <algorithm>
#include <vector>
#include <iostream>

typedef long long ll;
typedef long double ld;
using namespace std;

int main(){
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
  return 0;
}
