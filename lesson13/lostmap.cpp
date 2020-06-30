#include <algorithm>
#include <bitset>
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

struct unionfind
{
  vector<int> rank;
  vector<int> parent;
  unionfind(int size)
  {
    rank=vector<int>(size,0);
    parent=vector<int>(size);
    for(int i=0;i<size;i++)
      parent[i]=i;
  }

  int find(int x){
    int tmp=x;
    while(x!=parent[x]) x=parent[x];
    while(tmp!=x)//for log*, not needed most of the time
    {
      int remember=parent[tmp];
      parent[tmp]=x;
      tmp=remember;
    }
    return x;
  }
  void Union(int p, int q){
    p = find(p);
    q = find(q);
    if(q==p)
    {
      //alredy in the same group
      return;
    }
    if(rank[p] < rank[q]) parent[p] = q;
    else parent[q] = p;
    if(rank[p] == rank[q]) rank[p]++;
  }
};

bool compare(const pair<pair<ll,ll>, ll> & a, const pair<pair<ll,ll>, ll> & b){
  if (a.second != b.second){
    return a.second < b.second;
  }
  return a.first < b.first;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll N;
  while (cin >> N) {
    vector<pair<pair<ll, ll>, ll>> dists;
    ll temp;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        cin >> temp;
        dists.push_back({{i + 1, j + 1}, temp});
      }
    }
    sort(dists.begin(), dists.end(), compare);
    unionfind uf(N + 1);
    for(auto const & p : dists) {
      auto first_city = p.first.first;
      auto second_city = p.first.second;
      if (uf.find(first_city) != uf.find(second_city)){
        cout << first_city << " " << second_city << endl;
      }
      uf.Union(first_city, second_city);
    }

  }
  return 0;
}