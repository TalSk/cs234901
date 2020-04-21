

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
#include  <tgmath.h>

# define M_PIl          (3.141592653589793238462643383279502884L) /* pi */

using namespace std;
typedef long long ll;

ll kam(ll i) {
  return (log10(2* M_PIl *i)/2 + i*(log10(i)-log10(exp(1)))/(log10(10)))+1;
  // [(log(2πn)/2+n(logn−loge))/log10]+1
}

int main() {
  ll digs = 0;
  int res = 0;
  char c;

  while (true)
  {
    c = getchar();
    if (c == EOF) {
      if (digs <= 3) {
        // calc it direct
        if (digs == 2) {
          cout << 4 << endl;

        }
        else {
          switch (res)
          {
          case 1:
            cout << 1 << endl;
            break;
          case 2:
            cout << 2 << endl;
            break;
          case 6:
            cout << 3 << endl;
            break;
          case 120:
            cout << 5 << endl;
            break;
          case 720:
            cout << 6 << endl;
            break;
          default:
            break;
          }
        }

        return 0;
      }
      break;
    }

    if (c < '0' || c > '9') {
      continue;
    }

    digs++;

    if (digs <= 3) {
      res *= 10;
      res += c - '0';
    }
  }

  ll i=1;
  while (i < INT32_MAX) {
    if (kam(i) == digs) {
      break;
    }
    i++;

  }
  cout << i << endl;

  return 0;
}
