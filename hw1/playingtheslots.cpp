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

using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI                                                                     \
  acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

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
};

struct vec {
  double x, y; // name: `vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {}

  double mag() const { return sqrt(x * x + y * y); }

  vec &operator/(const double scale) {
    x /= scale;
    y /= scale;
    return *this;
  }

  void normalize() {
    auto m = mag();
    if (m != 0) {
      *this = *this / m;
    }
  }

  friend vec operator-(const vec &a, const vec &b);
  friend vec operator/(const vec &a, const double &b);
};

vec operator/(const vec &a, const double &b) { return {a.x / b, a.y / b}; }

double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }


// Converts a point structure to vector structure. Pretty simple.
vec pointToVec(const point &p) { return {p.x, p.y}; }

// Some vector operators implementation
vec operator-(const vec&a){
  return {-a.x, -a.y};
}
vec operator-(const vec &a, const vec &b) { return {a.x - b.x, a.y - b.y}; }
vec operator+(const vec &a, const vec &b) { return {a.x + b.x, a.y + b.y}; }

// Get a vector perpendicular to a
vec perp(const vec& a){
  return {a.y, -a.x};
}

// Finds all rectangles that enclose a convex polygon cp (ccw ordered).
// Returns the smallest edge of all rectangles.
double minimum_rectangle_edge(vector<point> cp) {
  double minimum_edge_length = MAXFLOAT;
  for (ull i = 0, j = 1; i < cp.size(); ++i, j = (i + 1) % cp.size()) {
    auto p0 = pointToVec(cp[i]);
    auto p1 = pointToVec(cp[j]);
    // Create a normalized vector of the chosen base edge.
    auto base = p1 - p0;
    base.normalize();
    // Perp base to create a correct axis to project unto.
    auto perp_base = -perp(base);
    double min_base = 0, max_base = 0;
    double max_base_perp = 0; // min_base_perp is always 0.
    for (auto & p : cp) {
      auto d = pointToVec(p) - p0;
      auto projection_on_base = dot(base, d);
      if (projection_on_base < min_base) {
        min_base = projection_on_base;
      } else if (projection_on_base > max_base) {
        max_base = projection_on_base;
      }
      auto projection_on_perp_base = dot(perp_base, d);
      if (projection_on_perp_base > max_base_perp) {
        max_base_perp = projection_on_perp_base;
      }
    }
    // Finished finding enclosing rectangle using this base edge.
    // Calculate the edges' length.
    double edge0_length = max_base - min_base;
    double edge1_length = max_base_perp;

    // Save minimum value.
    double min_edge = min(edge0_length, edge1_length);
    if (min_edge < minimum_edge_length){
      minimum_edge_length = min_edge;
    }
  }

  return minimum_edge_length;
}

int main() {
  ull n;
  while (cin >> n) {
    vector<point> poly;
    double x, y;
    for (int i = 0; i < n; ++i) {
      cin >> x >> y;
      poly.emplace_back(x, y);
    }
    // Algorithm requires a ccw ordered polygon, so reverse it.
    vector<point> poly_ccw;
    for (auto j = poly.rbegin(); j < poly.rend(); ++j) {
      poly_ccw.push_back(*j);
    }
    printf("%.8f\n", minimum_rectangle_edge(poly_ccw));
  }
  return 0;
}