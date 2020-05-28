#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
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
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<pair<int, int>> vii;
typedef vector<vector<pair<int, int>>> vvii;
typedef long long ll;

long double dist(pair<long double, long double> first,
                 pair<long double, long double> second) {
  auto dist =
      sqrt((first.first - second.first) * (first.first - second.first) +
           (first.second - second.second) * (first.second - second.second));
  return dist;
}

bool sortByy(pair<long double, long double> a,
             pair<long double, long double> b) {
  return a.second < b.second;
}

vector<vector<long double>> mem;
vector<pair<long double, long double>> trees;
vector<pair<long double, long double>> left_possible_points;
vector<pair<long double, long double>> right_possible_points;
ull num_trees_per_side;
long double f(ll left_left, ll left_right) {
  if (left_left < 0 or left_right < 0){
    return MAXFLOAT;
  }
  if (left_left == 0 and left_right == 0){
    return 0;
  }
  if (mem[left_left][left_right] != -1){
    return mem[left_left][left_right];
  }
  auto num_trees_put = num_trees_per_side * 2 - (left_left + left_right);
  auto cur_tree = trees[num_trees_put];
  long double put_left = MAXFLOAT, put_right = MAXFLOAT;
  if (left_left > 0){
    auto dist_left = dist(cur_tree, left_possible_points[num_trees_per_side - left_left]);
    put_left = f(left_left - 1, left_right) + dist_left;
  }
  if (left_right > 0){
    auto dist_right = dist(cur_tree, right_possible_points[num_trees_per_side - left_right]);
    put_right = f(left_left, left_right - 1) + dist_right;
  }

  long double ans = min(put_left, put_right);
  mem[left_left][left_right] = ans;
  return ans;
}

int main() {
  ll N;
  while (cin >> N) {
    long double L, W;
    cin >> L >> W;
    trees.assign(N, {});
    long double y;
    for (int i = 0; i < N; ++i) {
      cin >> y;
      trees[i] = {0, y};
    }
    sort(trees.begin(), trees.end(), sortByy);
    num_trees_per_side = N / 2;
    left_possible_points.assign(num_trees_per_side, {});
    right_possible_points.assign(num_trees_per_side, {});
    for (int j = 0; j < num_trees_per_side; ++j) {
      left_possible_points[j] = {0, j * L / (num_trees_per_side - 1)};
      right_possible_points[j] = {W, j * L / (num_trees_per_side - 1)};
    }

    mem.assign(num_trees_per_side + 1,
               vector<long double>(num_trees_per_side + 1, -1));
    printf("%.10Lf\n", f(num_trees_per_side, num_trees_per_side));

  }
  return 0;
}