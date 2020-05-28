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
#include <sstream>
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

long double dist(long double x1, long double y1, long double x2,
                 long double y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

ull n;
vector<vector<long double>> distances;

map<string, pair<long double, long double>> cities;
map<string, ull> city_name_to_orig_index;
map<ull, string> orig_index_to_city_name;
vector<string> cities_to_visit;

map<ull, ull> orig_index_to_new_index;
map<ull, ull> new_index_to_orig_index;

vector<vector<long double>> mem;
vector<vector<long double>> parents;

void print_path(ll visited) {
  vector<ull> path;
  auto cur_place = orig_index_to_new_index[city_name_to_orig_index["work"]];
  auto home_index = orig_index_to_new_index[city_name_to_orig_index["home"]];
  auto cur_visited = visited;
  while (cur_place != home_index) {
    cur_place = parents[cur_place][cur_visited];
    cur_visited = cur_visited | (1 << cur_place);
    path.push_back(cur_place);
  }
  ull c = 0;
  for (auto &i : path) {
    if (i == home_index) {
      break;
    }
    cout << orig_index_to_city_name[new_index_to_orig_index[i]];
    if (c != path.size() - 1) {
      cout << " ";
    }
    c++;
  }
}


long double g(ull curr, ll visited){
  if (mem[curr][visited] != -1){
    return mem[curr][visited];
  }

  auto home_orig = city_name_to_orig_index["home"];
  auto curr_orig = new_index_to_orig_index[curr];
  if (visited == (1 << cities_to_visit.size()) - 1){
    // Visited everything, go home
    mem[curr][visited] = distances[home_orig][curr_orig];
    parents[curr][visited] = orig_index_to_new_index[city_name_to_orig_index["home"]];
    return distances[home_orig][curr_orig];
  }
  if (home_orig == curr_orig){
    // We are home without passing through all required places
    return MAXFLOAT;
  }
  ll picked = -1;
  long double ans = MAXFLOAT;
  for (int i = 0; i < cities_to_visit.size(); ++i) {
    if (!(visited & (1 << i))){
      auto i_orig = new_index_to_orig_index[i];
      auto new_ans = distances[curr_orig][i_orig] + g(i, visited | (1 << i));
      if (new_ans < ans){
        ans = new_ans;
        picked = i;
      }
    }
  }
  if (picked != -1){
    parents[curr][visited] = picked;
  }
  mem[curr][visited] = ans;
  return ans;
}

int main() {
  while (cin >> n) {
    cities.clear();
    city_name_to_orig_index.clear();
    orig_index_to_city_name.clear();

    string temp;
    long double x, y;
    for (int i = 0; i < n; ++i) {
      cin >> temp;
      cin >> x >> y;
      cities[temp] = {x, y};
      city_name_to_orig_index[temp] = i;
      orig_index_to_city_name[i] = temp;
    }

    distances.assign(n + 1, vector<long double>(n + 1, 0));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        distances[i][j] = dist(cities[orig_index_to_city_name[i]].first,
                               cities[orig_index_to_city_name[i]].second,
                               cities[orig_index_to_city_name[j]].first,
                               cities[orig_index_to_city_name[j]].second);
      }
    }

    string query;
    cin >> ws;
    while (getline(cin, query)) {
      istringstream iss(query);
      cities_to_visit.clear();
      for (string s; iss >> s;) {
        cities_to_visit.push_back(s);
      }

      orig_index_to_new_index.clear();
      new_index_to_orig_index.clear();


      for (int i = 0; i < cities_to_visit.size(); ++i) {
        orig_index_to_new_index[city_name_to_orig_index[cities_to_visit[i]]] = i;
        new_index_to_orig_index[i] = city_name_to_orig_index[cities_to_visit[i]];
      }


      auto home_orig = city_name_to_orig_index["home"];
      auto work_orig = city_name_to_orig_index["work"];
      orig_index_to_new_index[home_orig] = cities_to_visit.size();
      orig_index_to_new_index[work_orig] = cities_to_visit.size() + 1;
      new_index_to_orig_index[cities_to_visit.size()] = home_orig;
      new_index_to_orig_index[cities_to_visit.size() + 1] = work_orig;

      mem.assign(cities_to_visit.size() + 3, vector<long double>(pow(2, 16), -1));
      parents.assign(cities_to_visit.size() + 3, vector<long double>(pow(2, 16), -1));

      g(orig_index_to_new_index[work_orig], 0);


      print_path(0);
      cout << endl;
      mem.clear();
      parents.clear();
    }
  }
  return 0;
}