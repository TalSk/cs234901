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

namespace segmentTreeB1 {
const ull N = 5000000; // limit for array size
ull n = 200001;        // array size
ull t[2 * N];

void reset(ull default_value=0){
  // Reset array
  for (ull i = 0; i < n; ++i) {
    t[n + i] = default_value; // init array
  }
}

void build() { // build the tree
  for (ull i = n - 1; i > 0; --i)
    t[i] = t[i << 1] + t[i << 1 | 1];
}

void modify(ull p, ull value) { // set value at position p
  for (t[p += n] = value; p > 1; p >>= 1)
    t[p >> 1] = max(t[p], t[p ^ 1]);
}

int query(ull l, ull r) { // max on interval [l, r)
  ull res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      res = max(res, t[l++]);
    if (r & 1)
      res = max(res, t[--r]);
  }
  return res;
}
}

int B1(){
  ull size, q;
  while (cin >> size){
    if (size == 0){
      break;
    }
    cin >> q;

    // Reset the segment tree to values of 0.

    segmentTreeB1::reset();
    segmentTreeB1::build();

    // Get the input values. arr will hold the values.
    // For each number, same_left will hold the count of equal values to the left,
    // and same_right the count of equal values to the right.
    int arr[size];
    int same_left[size];
    int same_right[size];
    int cur;

    // Initialize values
    cin >> cur;
    arr[0] = cur;
    same_left[0] = 0;
    int prev = cur;
    int count = 0;
    // First iteration to receive the data and update same_left.
    for (ull i = 1; i < size; ++i) {
      cin >> cur;
      arr[i] = cur;
      // Store current frequency of the current input in the segment tree
      segmentTreeB1::modify(cur + 100000, segmentTreeB1::query(cur + 100000, cur + 100001) + 1);
      if (prev == cur){
        count++;
      }
      else{
        count = 0;
      }
      prev = cur;
      same_left[i] = count;
    }

    // Reverse iteration to update same_right.
    same_right[size - 1] = 0;
    prev = arr[size - 1];
    count = 0;
    for (int j = size - 2; j >= 0; --j) {
      cur = arr[j];
      if (prev == cur){
        count++;
      }
      else{
        count = 0;
      }
      prev = cur;
      same_right[j] = count;
    }

    ull start,end, start_tag, end_tag;
    // The frequencies segment tree return correct value only if queried on
    // two indices that are a beginning and end of equal values.
    // Therefore, we need to "skip" from the start and end indices, we will use
    // same_right and same_left respectively to do so.
    ull count_start_ai, count_end_ai, max_full;
    for (int k = 0; k < q; ++k) {
      cin >> start;
      cin >> end;
      // Zero base the indices...
      start--;
      end--;

      // In a special case where the indices point to the same value, a simple
      // calculation will yield the correct result.
      if (arr[start] == arr[end]){
        cout << end - start + 1 << endl;
        continue;
      }

      // Skip necessary indices.
      count_start_ai = same_right[start] + 1;
      start_tag = start + count_start_ai;

      count_end_ai = same_left[end] + 1;
      end_tag = end - count_end_ai;

      // Query if dealing with more than 2 different values.
      if (start_tag <= end_tag) {
        max_full = segmentTreeB1::query(arr[start_tag] + 100000, arr[end_tag] + 100001);
      }
      else{
        max_full = 0;
      }

      // Max between 3 of the values we acquired.
      cout << max(max(count_start_ai, count_end_ai), max_full) << endl;
    }
  }
}