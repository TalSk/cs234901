#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define eps 1e-9
vector<pii> ascent;
vector<pii> descent;
ull total_height;
ull total_time_a;
ull total_time_d;

double ascent_at_t(double t){
  if (t >= total_time_a){
    return total_height;
  }
  double cur_t = 0.0;
  double cur_h = 0.0;
  int seg = 0;
  for (int i = 0; i < ascent.size(); ++i) {
    if (ascent[i].second + cur_t > t){
      seg = i;
      break;
    }
    else{
      cur_t += ascent[i].second;
      cur_h += ascent[i].first;
    }
  }
  return cur_h + (t - cur_t) * (double)((double)ascent[seg].first / (double)ascent[seg].second);
}

double descent_at_t(double t){
  if (t >= total_time_d){
    return 0;
  }
  double cur_t = 0.0;
  double cur_h = total_height;
  int seg = 0;
  for (int i = 0; i < descent.size(); ++i) {
    if (descent[i].second + cur_t > t){
      seg = i;
      break;
    }
    else{
      cur_t += descent[i].second;
      cur_h -= descent[i].first;
    }
  }
  return cur_h - (t - cur_t) * (double)((double)descent[seg].first / (double)descent[seg].second);
}

int main() {
  ull a, d;
  while (cin >> a) {
    cin >> d;
    total_height = 0;
    ull h, t;
    for (int i = 0; i < a; ++i) {
      cin >> h;
      cin >> t;
      ascent.emplace_back(pii(h, t));
      total_height += h;
      total_time_a += t;
    }

    for (int k = 0; k < d; ++k) {
      cin >> h;
      cin >> t;
      descent.emplace_back(pii(h, t));
      total_time_d += t;
    }

    double lo = 0.0, hi = 5000 * 100, mid = 0.0, ans = 0.0;
    while (fabs(hi - lo) > eps) {
      mid = (lo + hi) / 2.0;
      if (ascent_at_t(mid) >= descent_at_t(mid)) {
        hi = mid;
        ans = hi;
      } else {
        lo = mid;
      }
    }

    cout << setprecision(7) << mid;
  }
  return 0;
}