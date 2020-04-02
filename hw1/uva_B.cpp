//
// Created by Tal Skverer on 02/04/2020.
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

const int N = 5000000;  // limit for array size
int n = 200001;  // array size
int t[2 * N];

void build() {  // build the tree
  for (ull i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(ull p, ull value) {  // set value at position p
  for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = max(t[p], t[p^1]);
}

int query(int l, int r) {  // sum on interval [l, r)
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1){
      res = max(res, t[l++]);
    }
    if (r&1) {
      res = max(res, t[--r]);
    }
  }
  return res;
}

int main(){
  ull size, q;
  while (cin >> size){
    if (size == 0){
      break;
    }
    cin >> q;
    // Reset array
    for (ll i = 0; i < n; ++i) {
      t[n + i] = 0; // init array
    }
    build();

    // Create frequency segment tree
    ll list[size];
    ull frequencies[size];
    ull start = 0;
    ull count = 1;
    ll cur, prev;
    cin >> prev;
    list[0] = prev;
    for (ll i = 1; i < size; ++i) {
      cin >> cur;
      list[i] = cur;
      if (cur != prev){
        for (ll j = start; j < i; ++j) {
//          cout << "modify " << j << ", " <<  count << endl;
          modify(j, count);
          frequencies[j] = count;
        }
        count = 1;
        prev = cur;
        start = i;
      }
      else if (i == (size - 1)) {
        for (ll j = start; j <= i; ++j) {
//          cout << "modify " << j << ", " <<  count << endl;
          modify(j, count + 1);
          frequencies[j] = count + 1;
        }
      }
      else {
        count++;
      }
    }
//    for (int i = 0; i < size; ++i)
//      cout << list[i] << " ";
//    cout << endl;
//    for (int i = 0; i < size; ++i)
//      cout << frequencies[i] << " ";
//    cout << endl;
//    for (ll i = 0; i < size; ++i) {
//      cout << t[n + i] << " ";
//    }
//    cout << endl;

    ull x,y, xt, yt;
    int count_first, count_last;
    for (ll k = 0; k < q; ++k) {
      cin >> x;
      cin >> y;
      // Zero base...
      x--;
      y--;
      // Special case if x and y point to the same value
      if (list[x] == list[y]){
//        cout << "Spec case 1" << endl;
        cout << y - x + 1 << endl;
        continue;
      }
      // find the beginning of the next value
      count_first = 0;
      while (list[x] == list[x + count_first]){
        count_first++;
      }
      // find the end of the last value
      count_last = 0;
      while (list[y] == list[y - count_last]){
        count_last++;
      }

//      cout << count_first << ", " << count_last << endl;
      // Special case if dealing with just 2 numbers
      if (x + count_first > y - count_last){
//        cout << "Spec case 2" << endl;
        cout << max(count_first, count_last) << endl;
        continue;
      }

//      cout << "query " << x + count_first << ", " << y - count_last + 1<< endl;
//      cout << "case 3: "<< query(x + count_first, y - count_last + 1) << endl;
      cout << max(max(count_first, count_last), query(x + count_first, y - count_last + 1)) << endl;

    }
  }
}