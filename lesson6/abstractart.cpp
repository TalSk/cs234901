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
typedef long long ll;

using namespace std;

#define INF 1e9
#define EPS 1e-9

struct point {
  double x, y;             // only used if more precision is needed
  point() { x = y = 0.0; } // default constructor
  point(double _x, double _y) : x(_x), y(_y) {} // user-defined
  bool operator<(point other) const {           // override less than operator
    if (fabs(x - other.x) > EPS)                // useful for sorting
      return x < other.x; // first criteria , by x-coordinate
    return y < other.y;
  } // second criteria, by y-coordinate
  // use EPS (1e-9) when testing equality of two floating points
  bool operator==(point other) const {
    return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
  }

  point operator-(point other) const { return {x - other.x, y - other.y}; }

  point operator*(double other) const { return {x * other, y * other}; }
  long double operator*(point other) const { return x * other.x + y * other.y; }
  point operator+(point other) const { return {x + other.x, y + other.y}; }
};

struct vec {
  double x, y; // name: `vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(point a, point b) { // convert 2 points to vector a->b
  return vec(b.x - a.x, b.y - a.y);
}

vec scale(vec v, double s) { // nonnegative s = [<1 .. 1 .. >1]
  return vec(v.x * s, v.y * s);
} // shorter.same.longer

double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

double cross(point a, point b) { return a.x * b.y - a.y * b.x; }

ll sgn(long double num) { return abs(num) < EPS ? 0 : num < 0 ? -1 : 1; }

ll ccw(point a, point b, point c) {
  return sgn((c.y - a.y) * (b.x - a.x) - (b.y - a.y) * (c.x - a.x));
}

long double area(vector<point> poly) {
  long double shoelace_sum = 0;
  for (ull i = 0, j = 1; i < poly.size(); i++, j = (i + 1) % (poly.size())) {
    shoelace_sum += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
  }
  return abs(0.5 * shoelace_sum);
}

enum IntersectionType { LTR = -1, MOCK = 0, RTL = 1 };

long double polys_union_area(const vector<vector<point>> &polys) {
  long double total_area = 0;
  for (int poly_pos = 0; poly_pos < polys.size(); ++poly_pos) {
    auto poly_size = polys[poly_pos].size();
    for (ull i = 0, j = 1; i < poly_size; ++i, j = (i + 1) % poly_size) {
      // For every "original segment" of 2 points in a polygon, check
      // intersections with every "other segment" of every other polygon
      auto poly1_point1 = polys[poly_pos][i];
      auto poly1_point2 = polys[poly_pos][j];

      // Hold a vector of intersections. Each intersection is a pair of its
      // position on the segment, and the direction of the intersection (in case
      // of multiple intersections)
      vector<pair<long double, IntersectionType>> intersections;
      for (int poly_pos2 = 0; poly_pos2 < polys.size(); ++poly_pos2) {
        if (poly_pos == poly_pos2)
          // Skip same polygon
          continue;
        auto poly_size2 = polys[poly_pos2].size();
        for (ull k = 0, h = 1; k < poly_size2; ++k, h = (k + 1) % poly_size2) {
          auto poly2_point1 = polys[poly_pos2][k];
          auto poly2_point2 = polys[poly_pos2][h];
          // Check if there's an intersection by calculating whether the two
          // points of the other segment are ccw
          auto is_point1_ccw = ccw(poly1_point1, poly1_point2, poly2_point1);
          auto is_point2_ccw = ccw(poly1_point1, poly1_point2, poly2_point2);
          if ((is_point1_ccw < 0 and is_point2_ccw >= 0) or
              (is_point1_ccw >= 0 and is_point2_ccw < 0)) {
            // We might have an intersection! The position of intersection the
            // segment is calculated by diving the areas of the parallelogram
            // created by the other segment and each of the original points
            auto first_area = cross(toVec(poly2_point1, poly2_point2),
                                    toVec(poly2_point1, poly1_point1));
            auto second_area = cross(toVec(poly2_point1, poly2_point2),
                                     toVec(poly2_point1, poly1_point2));
            auto percent = second_area / (second_area - first_area);
            // The position can be lower than 0 or bigger than 1 (in case the
            // other segment points are on different sides but the segment
            // itself does not intersect. In this case we just save the
            // direction used in future calculation to get the correct area.
            if (percent < 0) percent = 0;
            else if (percent > 1) percent = 1;
            
            if (is_point1_ccw < 0 and is_point2_ccw >= 0) {
              // First case, point1 is cw and point2 is ccw (or on the segment).
              intersections.emplace_back(percent, LTR);
            } else if (is_point1_ccw >= 0 and is_point2_ccw < 0) {
              // Second case, point1 is ccw (or on) and point2 is cw.
              intersections.emplace_back(percent, RTL);
            }
          }
        }
      }
      // Now, we want to find the parts of the original segment that
      // should be added to the shoelace area calculation. We do this by
      // iterating over all percents found and adding their respective
      // parts, taking in mind to only add areas that were intersected an
      // even number of times

      // We need to add a "mock" positions 0 and 1.
      intersections.emplace_back(0, MOCK);
      intersections.emplace_back(1, MOCK);
      // Sort intersections so we can iterate them with the correct order
      sort(intersections.begin(), intersections.end());
      long double previous, current, total_areas = 0.0;
      ll intersections_counter = intersections[0].second;
      // We trim negative values and values over 1.0 (Will effectively be
      // ignored but are important for intersection counter.
      previous = intersections[0].first;
      for (int l = 1; l < intersections.size(); ++l) {
        current = intersections[l].first;
        if (!intersections_counter) {
          total_areas += current - previous;
        }
        previous = current;
        intersections_counter += intersections[l].second;
      }
      // Add the appropriate shoelace formula part to the total area.
      total_area += 0.5 * cross(poly1_point1, poly1_point2) * total_areas;
    }
  }
  return abs(total_area);
}

int main() {
  ull n;
  while (cin >> n) {
    vector<vector<point>> polys(n);
    for (int j = 0; j < n; ++j) {
      ull m;
      cin >> m;
      long double x, y;
      for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        polys[j].emplace_back(x, y);
      }
    }

    long double total_area = 0;
    for (auto &poly : polys) {
      total_area += area(poly);
    }
    printf("%.8Lf ", total_area);

    /* 
    Note: I found this algorithm online, but it was interesting enough I had to find a solution after failing myself.
    This is my own implmentation of it, after understanding most of it (still having a problem understanding why the direction 
    of the "outside" intersections are relevant).
    If this does not qualify as solving the problem, I don't mind it not being counted towards my number of probelms solved.
    */

    auto total_union_area = polys_union_area(polys);
    printf("%.8Lf\n", total_union_area);
  }
  return 0;
}