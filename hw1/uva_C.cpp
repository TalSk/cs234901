#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
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

double eps = 1e-9;

vector<pair<double, double>> *competitors;
pair<double, double> *cheater;
ll t;

double f(double r) {
  // Find best competitor
  vector<double> times(competitors->size());
  for (int i = 0; i < competitors->size(); ++i) {
    times[i] =
        (r / competitors->at(i).first) + ((t - r) / competitors->at(i).second);
  }
  // Calculate cheater's time
  double cheater_time = (r / cheater->first) + ((t - r) / cheater->second);

  // Subtract to get function's value (minimum between 1e50 to get rid of inf values)
  return min(1e50, *min_element(times.begin(), times.end())) - cheater_time;
}

int main() {
  while (cin >> t) {
    ull n;
    cin >> n;
    double r_speed, c_speed;
    competitors = new vector<pair<double, double>>();
    for (int i = 0; i < n - 1; ++i) {
      cin >> r_speed;
      cin >> c_speed;
      competitors->push_back({r_speed, c_speed});
    }
    cin >> r_speed;
    cin >> c_speed;
    cheater = new pair<double, double>(r_speed, c_speed);

    // Ternary search to find the maximum of the function.
    double l = 0, r = t;

    while (fabs(r - l) > eps) {
      double left_third = l + (r - l) / 3;
      double right_third = r - (r - l) / 3;

      if (f(left_third) < f(right_third)) {
        l = left_third;
      } else {
        r = right_third;
      }
    }

    // Get average end value of r.
    double ans_r = (l + r) / 2;
    // Get the function value at this r.
    double ans_time_hr = f(ans_r);
    // For rounding errors.
    if (fabs(ans_time_hr) < eps){
      ans_time_hr = 0;
    }

    if (ans_time_hr < 0.0) {
      printf("The cheater cannot win.\n");
    } else {
      // I had a lot of problems trying to present it with cout and gave up :(
      printf("The cheater can win by %.0lf seconds with r = %.2lfkm and k = "
             "%.2lfkm.\n",
             ans_time_hr * 3600, ans_r, t - ans_r);
    }
  }
  return 0;
}