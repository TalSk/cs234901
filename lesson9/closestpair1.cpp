#include <algorithm>
#include <bits/stdc++.h>
#include <bitset>
#include <climits>
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
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
typedef vector<vector<double>> vvd;

class Point {
public:
  double x, y;
};

// Needed to sort array of points according to X coordinate
int compareX(const void *a, const void *b) {
  auto *p1 = (Point *)a, *p2 = (Point *)b;
  return (p1->x - p2->x);
}

// Needed to sort array of points according to Y coordinate
int compareY(const void *a, const void *b) {
  auto *p1 = (Point *)a, *p2 = (Point *)b;
  return (p1->y - p2->y);
}

double dist(Point p1, Point p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Returns the smallest distance between two points. Work in O(N^2) and
// therefore only valid when working on a small sized array.
double bruteForce(Point P[], int n, pair<Point, Point> &closest_pair) {
  auto min = DBL_MAX;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      auto curr_distance = dist(P[i], P[j]);
      if (curr_distance < min) {
        min = curr_distance;
        closest_pair.first = P[i];
        closest_pair.second = P[j];
      }
    }
  }
  return min;
}

// Finds the distance between the closest points of strip of given size.
// All points in strip[] are sorted according to their y coordinate.
// They all within distance d.
// Works in O(n) as the number of points in the strip is O(1).
double stripClosest(Point strip[], int size, double d,
                    pair<Point, Point> &closest_pair) {
  double min = d; // Initialize the minimum distance as d

  qsort(strip, size, sizeof(Point), compareY);

  for (int i = 0; i < size; ++i) {
    for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
      auto current_distance = dist(strip[i], strip[j]);
      if (current_distance < min) {
        min = current_distance;
        closest_pair.first = strip[i];
        closest_pair.second = strip[j];
      }
    }
  }

  return min;
}

// Find the smallest distance in a point array.
// The array should contain the points sorted according to their x coordinate.
double closestUtil(Point P[], int n, pair<Point, Point> &closest_pair) {
  // For a small amount of points, use brute force.
  if (n <= 3) {
    return bruteForce(P, n, closest_pair);
  }

  // Get the middle point
  int mid = n / 2;
  Point midPoint = P[mid];

  // Find the smallest distance dl on left of middle point and dr on right side
  pair<Point, Point> closest_pair_1;
  pair<Point, Point> closest_pair_2;
  double dl = closestUtil(P, mid, closest_pair_1);
  double dr = closestUtil(P + mid, n - mid, closest_pair_2);

  double d;
  if (dl <= dr) {
    closest_pair.first = closest_pair_1.first;
    closest_pair.second = closest_pair_1.second;
    d = dl;
  } else {
    closest_pair.first = closest_pair_2.first;
    closest_pair.second = closest_pair_2.second;
    d = dr;
  }

  // strip will contain all points closer than distance d to the middle point.
  Point strip[n];
  int j = 0;
  for (int i = 0; i < n; i++)
    if (abs(P[i].x - midPoint.x) < d)
      strip[j] = P[i], j++;

  // Find the closest points in strip and return it.
  pair<Point, Point> closest_pair_3;
  double res = stripClosest(strip, j, d, closest_pair_3);
  if (d <= res) {
    return d;
  } else {
    closest_pair.first = closest_pair_3.first;
    closest_pair.second = closest_pair_3.second;
    return res;
  }
}

double closest(Point P[], int n, pair<Point, Point> &closest_pair) {
  // Sort points by X.
  qsort(P, n, sizeof(Point), compareX);
  return closestUtil(P, n, closest_pair);
}

int main() {
  int n;
  cin >> n;
  while (n != 0) {
    auto *arr = static_cast<Point *>(malloc(sizeof(Point) * n));
    for (int i = 0; i < n; ++i) {
      double a, b;
      cin >> a >> b;
      arr[i].x = a;
      arr[i].y = b;
    }

    pair<Point, Point> closest_pair;
    double min_dist = closest(arr, n, closest_pair);
    printf("%.2f %.2f %.2f %.2f\n", closest_pair.first.x, closest_pair.first.y,
           closest_pair.second.x, closest_pair.second.y);

    free(arr);
    cin >> n;
  }

  return 0;
}