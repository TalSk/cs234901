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
#include <iomanip>
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

#define INF 1e9
#define EPS 1e-9
#define PI                                                                     \
  acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

// struct point_i { int x, y; };    // basic raw form, minimalist mode
struct point_i {
  int x, y;                // whenever possible, work with point_i
  point_i() { x = y = 0; } // default constructor
  point_i(int _x, int _y) : x(_x), y(_y) {}
}; // user-defined

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
};

long double dist(point p1, point p2) { // Euclidean distance
  // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
  return hypot(p1.x - p2.x, p1.y - p2.y);
} // return double

// rotate p by theta degrees CCW w.r.t origin (0, 0)
point rotate(point p, double theta) {
  double rad = DEG_to_RAD(theta); // multiply theta with PI / 180.0
  return point(p.x * cos(rad) - p.y * sin(rad),
               p.x * sin(rad) + p.y * cos(rad));
}

struct line {
  double a, b, c;
}; // a way to represent a line

// the answer is stored in the third parameter (pass by reference)
void pointsToLine(point p1, point p2, line &l) {
  if (fabs(p1.x - p2.x) < EPS) { // vertical line is fine
    l.a = 1.0;
    l.b = 0.0;
    l.c = -p1.x; // default values
  } else {
    l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
    l.b = 1.0; // IMPORTANT: we fix the value of b to 1.0
    l.c = -(double)(l.a * p1.x) - p1.y;
  }
}

// not needed since we will use the more robust form: ax + by + c = 0 (see
// above)
struct line2 {
  double m, c;
}; // another way to represent a line

int pointsToLine2(point p1, point p2, line2 &l) {
  if (abs(p1.x - p2.x) < EPS) { // special case: vertical line
    l.m = INF;                  // l contains m = INF and c = x_value
    l.c = p1.x;                 // to denote vertical line x = x_value
    return 0; // we need this return variable to differentiate result
  } else {
    l.m = (double)(p1.y - p2.y) / (p1.x - p2.x);
    l.c = p1.y - l.m * p1.x;
    return 1; // l contains m and c of the line equation y = mx + c
  }
}

bool areParallel(line l1, line l2) { // check coefficients a & b
  return (fabs(l1.a - l2.a) < EPS) && (fabs(l1.b - l2.b) < EPS);
}

bool areSame(line l1, line l2) { // also check coefficient c
  return areParallel(l1, l2) && (fabs(l1.c - l2.c) < EPS);
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
  double x, y; // name: `vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(point a, point b) { // convert 2 points to vector a->b
  return vec(b.x - a.x, b.y - a.y);
}

vec scale(vec v, double s) { // nonnegative s = [<1 .. 1 .. >1]
  return vec(v.x * s, v.y * s);
} // shorter.same.longer

point translate(point p, vec v) { // translate p according to v
  return point(p.x + v.x, p.y + v.y);
}

// convert point and gradient/slope to line
void pointSlopeToLine(point p, double m, line &l) {
  l.a = -m; // always -m
  l.b = 1;  // always 1
  l.c = -((l.a * p.x) + (l.b * p.y));
} // compute this

void closestPoint(line l, point p, point &ans) {
  line perpendicular;    // perpendicular to l and pass through p
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

// returns the reflection of point on a line
void reflectionPoint(line l, point p, point &ans) {
  point b;
  closestPoint(l, p, b); // similar to distToLine
  vec v = toVec(p, b);   // create a vector
  ans = translate(translate(p, v), v);
} // translate p twice

double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
double distToLine(point p, point a, point b, point &c) {
  // formula: c = a + u * ab
  vec ap = toVec(a, p), ab = toVec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);
  c = translate(a, scale(ab, u)); // translate a to c
  return dist(p, c);
} // Euclidean distance between p and c

// returns the distance from p to the line segment ab defined by
// two points a and b (still OK if a == b)
// the closest point is stored in the 4th parameter (byref)
double distToLineSegment(point p, point a, point b, point &c) {
  vec ap = toVec(a, p), ab = toVec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);
  if (u < 0.0) {
    c = point(a.x, a.y); // closer to a
    return dist(p, a);
  } // Euclidean distance between p and a
  if (u > 1.0) {
    c = point(b.x, b.y); // closer to b
    return dist(p, b);
  } // Euclidean distance between p and b
  return distToLine(p, a, b, c);
} // run distToLine as above

double angle(point a, point o, point b) { // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

long double area(point a, point b, point c) {
  return abs((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

double area2(point p, point q,
             point r) { // returns 'twice' the area of this triangle A-B-c
  return p.x * q.y - p.y * q.x + q.x * r.y - q.y * r.x + r.x * p.y - r.y * p.x;
}

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0;
}

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
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

// Returns max distance of all antipodal pairs. Assumes cp is a convex polygon.
// This is the second pseudo-code presented in
// https://en.wikipedia.org/wiki/Rotating_calipers#Shamos's_algorithm as this is
// much easier than dealing with angles in my opinion.
vector<pair<point, point>> rotating_calipers(vector<point> &cp) {
  // Special cases. Only actually calculate the calipers if there are at least
  // 3 points as the polygon.
//  if (cp.size() == 1) {
//    return 0;
//  }
//  if (cp.size() == 2) {
//    return dist(cp[0], cp[1]);
//  }

  long double max_dist = 0;
  vector<pair<point, point>> antipodals;
  auto N = cp.size();
  int first_point = 1;

  // Find a point that is antipodal to points 0, N-1.
  // We do this by ensuring that the area of the triangle (N-1, 0, first_point)
  // is larger or equal to the triangle (N-1, 0, first_point + 1).
  // This will force the points 0 and first_point to be antipodal.
  while (area(cp[N - 1], cp[0], cp[(first_point + 1) % N]) >
         area(cp[N - 1], cp[0], cp[first_point])) {
    ++first_point;
  }

  // Start running from point 0 and the first point we found,
  // until either the first counter (i) reaches the first point or
  // the second counter (j) reaches the first point.
  for (int i = 0, j = first_point; i <= first_point and j < N; ++i) {
    // Current points are antipodal.
    max_dist = max(max_dist, dist(cp[i], cp[j]));
    antipodals.emplace_back(cp[i], cp[j]);
    // Increment j as long as the point it represents is antipodal
    // to the point represented by the i.
    // This is done in similar fashion to before, where the points i,j are
    // antipodal iff the area of the triangle (i, i+1, j+1) is larger than
    // the area of the triangle (i, i+1, j) - this is because we know i,j are
    // currently antipodal.
    while (area(cp[i], cp[(i + 1) % N], cp[(j + 1) % N]) >
           area(cp[i], cp[(i + 1) % N], cp[j])) {
      // It is important to check that j < N here too, since it can go over
      // this value while iterating, and we don't need to calculate anything
      // else.
      if (j > N) {
        break;
      }
      // Current points are antipodal.
      max_dist = max(max_dist, dist(cp[i], cp[(j + 1) % N]));
      antipodals.emplace_back(cp[i], cp[(j + 1) % N]);
      ++j;
    }
  }
  // Due to the algorithm's way of calculating things, the antipodals vector can
  // include duplicate points or the same point twice. If used, remove them.

  return antipodals;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ull N;
  while (cin >> N){
    vector<point> points;
    long double x, y;
    for (int i = 0; i < N; ++i) {
      cin >> x >> y;
      points.emplace_back(x, y);
    }
    auto ch = convex_hull(points);
    if (ch.size() < 3){
      cout << 0 << endl;
      continue;
    }
    auto antipodal_points = rotating_calipers(ch);
    long double best_area = 0;
    for(auto &pair_of_points : antipodal_points) {
      for(auto &p : ch) {
        best_area = max(best_area, area(p, pair_of_points.first, pair_of_points.second));
      }
    }

//    long double best_area = 0;
//    auto n = ch.size();
//    for (int a = 0; a < n; ++a) {
//      int b = a + 1;
//      auto b_p = b % n;
//      for (int c = a + 2; c < a + n; ++c) {
//        auto c_p = c % n;
//
//        auto curr_area = area(ch[a], ch[b_p], ch[c_p]);
//        while(true){
//          b_p = (b_p + 1) % n;
//          if (area(ch[a], ch[b_p], ch[c_p]) < curr_area or b_p >= c_p){
//            break;
//          }
//          curr_area = area(ch[a], ch[b_p], ch[c_p]);
//        }
//
//        b_p = max((a + 1) % n, (b_p - 2) % n);
//        best_area = max(best_area, curr_area);
//      }
//    }

    printf("%.10Lf\n", best_area / 2);
  }
}