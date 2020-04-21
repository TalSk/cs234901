

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>

using namespace std;
typedef long long ll;

int main() {
  int N, num, first, res_gcd;
  cin >> N;
  cin >> first;

  for (int i = 0; i < N-1; i++)
  {
    cin >> num;
    res_gcd = __gcd(first, num);

    cout << (first/res_gcd) << "/" << (num/res_gcd) << endl;
  }
  return false;
}
