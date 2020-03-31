//
// Created by Tal Skverer on 31/03/2020.
//
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
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
typedef pair<int, int> pii;


int q2() {
  // Minimum queue to take each time 2 numbers and sum their values.
  ull N;
  priority_queue<ull, vector<ull>, greater<ull>> min_heap;
  while (true) {
    cin >> N;
    if (N == 0){
      break;
    }
    while (!min_heap.empty()) {
      min_heap.pop();
    }
    ull curr;
    for (int i = 0; i < N; ++i) {
      cin >> curr;
      min_heap.push(curr);
    }
    ull sum = 0;
    while (true){
      // Get two least numbers
      ull min1, min2;
      min1 = min_heap.top();
      min_heap.pop();
      min2 = min_heap.top();
      min_heap.pop();
      sum += min1 + min2;
      if (min_heap.empty()) {
        cout << sum << endl;
        break;
      }
      min_heap.push(min1 + min2);
    }
  }
  return 0;
}



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

int q3(){
  long n;
  while (true){
    cin >> n;
    if (n == 0){
      break;
    }
    bitset<32> bs(n);
    bitset<32> a;
    bitset<32> b;
    uint index = 1;
    for (int i = 0; i < 32; ++i) {
      if (bs.test(0)){
        if (index % 2 == 1){
          a.flip(i);
        }
        else {
          b.flip(i);
        }
        index++;
      }
      bs = bs >> 1;
    }
    cout << a.to_ulong() << " " << b.to_ulong() << endl;
  }
  return 0;
}

int q1(){
  ull n;
  while(cin >> n) {
    map<string, int> courses;
    for (int i = 0; i < n; ++i) {
      set<int> values;
      int cur;
      for (int j = 0; j < 5; ++j) {
        cin >> cur;
        values.insert(cur);
      }
      string a;
      for (auto x: values){
        a.append(to_string(x));
      }
      courses[a]++;
    }
    int max = 0;
    int countmax = 0;
    for (const auto & x: courses){
      if (x.second > max){
        max = x.second;
        countmax = x.second;
      }
      else if (x.second == max){
        countmax += x.second;
      }
    }
    cout << countmax << endl;
  }
  return 0;
}






int q4(){
  ull n, m;
  while (cin >> n){
    cin >> m;
    unionfind uf(n);
    map<ull, int> pep;
    for (int i = 0; i < n; ++i) {
      int amount;
      cin >> amount;
      pep[i] = amount;
    }

    int x,y;
    for (int j = 0; j < m; ++j) {
      cin >> x;
      cin >> y;
      uf.Union(x,y);
    }

    map<ull, int> groups;
    int g;
    for (int i = 0; i < n; ++i) {
      g = uf.find(i);
      groups[g] += pep[i];
    }

    for (int k = 0; k < groups.size(); ++k) {
      if (groups[k] != 0){
        cout << "IMPOSSIBLE" << endl;
        return 0;
      }
    }
    cout << "POSSIBLE" << endl;
  }
}