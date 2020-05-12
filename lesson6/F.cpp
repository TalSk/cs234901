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
#define EPS 1e-9
#define MAX_SIZE 100

using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI                                                                     \
  acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

struct point {
  long double x, y;             // only used if more precision is needed
  point() { x = y = 0.0; } // default constructor
  point(long double _x, long double _y) : x(_x), y(_y) {} // user-defined
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

long double dist(point p1, point p2) { // Euclidean distance
  // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
  return hypot(p1.x - p2.x, p1.y - p2.y);
} // return double

struct line {
  long double a, b, c;
}; // a way to represent a line

// not needed since we will use the more robust form: ax + by + c = 0 (see
// above)
struct line2 {
  long double m, c;
}; // another way to represent a line

bool areParallel(line l1, line l2) { // check coefficients a & b
  return (fabs(l1.a - l2.a) < EPS) && (fabs(l1.b - l2.b) < EPS);
}

// returns true (+ intersection point) if two lines are intersect
bool areIntersect(line l1, line l2, point &p) {
  if (areParallel(l1, l2))
    return false; // no intersection
  // solve system of 2 linear algebraic equations with 2 unknowns
  p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
  // special case: test for vertical line to avoid division by zero
  if (fabs(l1.b) > EPS)
    p.y = -(l1.a * p.x + l1.c);
  else
    p.y = -(l2.a * p.x + l2.c);
  return true;
}

struct vec {
  long double x, y; // name: `vec' is different from STL vector
  vec(long double _x, long double _y) : x(_x), y(_y) {}
};

vec toVec(point a, point b) { // convert 2 points to vector a->b
  return {b.x - a.x, b.y - a.y};
}

vec scale(vec v, long double s) { // nonnegative s = [<1 .. 1 .. >1]
  return {v.x * s, v.y * s};
} // shorter.same.longer

point translate(point p, vec v) { // translate p according to v
  return {p.x + v.x, p.y + v.y};
}

// convert point and gradient/slope to line
void pointSlopeToLine(point p, long double m, line &l) {
  l.a = -m; // always -m
  l.b = 1;  // always 1
  l.c = -((l.a * p.x) + (l.b * p.y));
} // compute this

void closestPoint(line l, point p, point &ans) {
  line perpendicular{};    // perpendicular to l and pass through p
  if (fabs(l.b) < EPS) { // special case 1: vertical line
    ans.x = -(l.c);
    ans.y = p.y;
    return;
  }

  if (fabs(l.a) < EPS) { // special case 2: horizontal line
    ans.x = p.x;
    ans.y = -(l.c);
    return;
  }

  pointSlopeToLine(p, 1 / l.a, perpendicular); // normal line
  // intersect line l with this perpendicular line
  // the intersection point is the closest point
  areIntersect(l, perpendicular, ans);
}

long double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

long double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
long double distToLine(point p, point a, point b, point &c) {
  // formula: c = a + u * ab
  vec ap = toVec(a, p), ab = toVec(a, b);
  long double u = dot(ap, ab) / norm_sq(ab);
  c = translate(a, scale(ab, u)); // translate a to c
  return dist(p, c);
} // Euclidean distance between p and c

long double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0;
}

// Returns -1 if point p to the left of the line a,b, 0 if it's on the line and 1 if it's to the right.
int left(point a, point b, point c){
  long double det = (a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y);
  if (det < 0){
    return -1;
  }
  if (det > 0){
    return 1;
  }
  return 0;
}

// Returns true if point p is inside the triangle defined by points a,b,c.
bool IsInTriangle(point p, point a, point b, point c){
  // This function assumes the triangle a, b, c is ordered clockwise.
  int left_a_b = left(p, a, b);
  int left_b_c = left(p, b, c);
  int left_c_a = left(p, c, a);

  // The point is in if it has no points on the left side or no points of the right side of all edges.
  bool has_left = left_a_b == -1 or left_b_c == -1 or left_c_a == -1;
  bool has_right = left_a_b == 1 or left_b_c == 1 or left_c_a == 1;
  return not(has_left and has_right);
}

bool IsInConvexPolygon(point p, vector<point> convex_poly) {
  ull l = convex_poly.size();
  assert(l >= 3);

  // Binary search to find between which segments v0 - vi and v0 - vi+1 does p reside
  ull low = 1, high = l - 1;
  while(low < high - 1){
    ull mid = (low + high) / 2;
    if (ccw(convex_poly[0], convex_poly[mid], p)){
      high = mid;
    }
    else {
      low = mid;
    }
  }
  // Point is between segment [0, low] to [0, low + 1]
  assert(low < l);
  return IsInTriangle(p, convex_poly[0], convex_poly[low], convex_poly[low + 1]);
}

vector<point> convex_hull(vector<point> Points) {

  //-------------- incremental alg. ---------
  // upper hull
  sort(Points.begin(), Points.end());
  stack<point> stk_up;
  stk_up.push(Points[0]);
  stk_up.push(Points[1]);
  for (int i = 2; i < Points.size(); i++) {
    while ((stk_up.size() >= 2)) {
      point p2, p3;
      p2 = stk_up.top();
      stk_up.pop();
      p3 = stk_up.top();
      if (ccw(Points[i], p2, p3)) {
        stk_up.push(p2);
        break;
      }
    }
    stk_up.push(Points[i]);
  }
  // lower hull
  for (int i = 0; i < Points.size(); i++) {
    Points[i].x = -Points[i].x;
    Points[i].y = -Points[i].y;
  }
  sort(Points.begin(), Points.end());
  stack<point> stk_low;
  stk_low.push(Points[0]);
  stk_low.push(Points[1]);
  for (int i = 2; i < Points.size(); i++) {
    while ((stk_low.size() >= 2)) {
      point p2, p3;
      p2 = stk_low.top();
      stk_low.pop();
      p3 = stk_low.top();
      if (ccw(Points[i], p2, p3)) {
        stk_low.push(p2);
        break;
      }
    }
    stk_low.push(Points[i]);
  }

  // print convex hull - cw order from leftmost point
  vector<point> CH;
  stk_low.pop();
  point p;
  while (!stk_low.empty()) {
    p = stk_low.top();
    p.x = -p.x;
    p.y = -p.y;
    CH.push_back(p);
    stk_low.pop();
  }
  stk_up.pop();
  while (!stk_up.empty()) {
    CH.push_back(stk_up.top());
    stk_up.pop();
  }
  reverse(CH.begin(), CH.end()); // ccw -> cw
  return CH;
}
int main() {
  ull L, S;
  while (cin >> L) {
    vector<point> points(L);
    long double x, y;
    for (int i = 0; i < L; ++i) {
      cin >> x >> y;
      points[i] = point(x, y);
    }

    auto CH = convex_hull(points);

    cin >> S;
    ull count = 0;
    for (int j = 0; j < S; ++j) {
      cin >> x >> y;
      if (IsInConvexPolygon(point(x, y), CH)) {
        count++;
      }
    }

    cout << count << endl;
  }
  return 0;
}