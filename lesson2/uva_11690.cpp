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

int main(){
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