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

#define EPS 1e-9
#define MAX_SIZE 100

using namespace std;

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

  point operator*(double other) const{
    return {x * other, y * other};
  }
  long double operator* (point other) const{
    return x * other.x + y * other.y;
  }
  point operator +(point other) const{
    return {x + other.x, y + other.y};
  }
};

double dist(point p1, point p2) { // Euclidean distance
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

//// another variant
// int area2(point p, point q, point r) { // returns 'twice' the area of this
// triangle A-B-c
//  return p.x * q.y - p.y * q.x +
//         q.x * r.y - q.y * r.x +
//         r.x * p.y - r.y * p.x;
//}

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
//bool ccw(point p, point q, point r) {
//  return cross(toVec(p, q), toVec(p, r)) > 0;
//}
bool ccw(point a, point b, point c){
  return (c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x);
}

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

long double area(vector<point> poly) {
  long double shoelace_sum = 0;
  for (ull i = 0, j = 1; i < poly.size(); i++, j = (i + 1) % (poly.size())) {
    shoelace_sum += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
  }
  return abs(0.5 * shoelace_sum);
}

bool PointInPolygon(vector<point> points, point p) {
  bool c = false;

  for (ull i = 0; i < points.size(); ++i) {
    ull j = (i + 1) % points.size();
    if ((p.y < points[i].y != p.y < points[j].y) &&
        (p.x < points[i].x + (points[j].x - points[i].x) * (p.y - points[i].y) /
                                 (points[j].y - points[i].y)))
      c = !c;
  }

  return c;
}

double dot(point p, point q) { return p.x * q.x + p.y * q.y; }

double cross(point p, point q) { return p.x * q.y - p.y * q.x; }

bool parallel(point a, point b, point c, point d) {
  return abs(cross(a - b, c - d)) < EPS;
}
bool PointOnPolygon(vector<point> points, point p) {
  int i, j, nvert = points.size();
  for (i = 0, j = nvert - 1; i < nvert; j = i++) {
    if (dist(points[i], p) < EPS or dist(points[j], p) < EPS) {
      return true;
    }
    if (parallel(p, points[i], p, points[j]) and
        dot(p - points[i], p - points[j]) < 0) {
      return true;
    }
  }
  return false;
}

bool PointInPoly(point p, vector<point> poly) {
  return PointOnPolygon(poly, p) or PointInPolygon(poly, p);
}

// Checks if [a,b] intersects [c,d]
bool intersect(point p, point p2, point q, point q2, point &inter){
  auto r = p2 - p;
  auto s = q2 - q;
  auto rxs = cross(r, s);
  auto qpxr = cross((q - p), r);

  bool is_rxs_0 = abs(rxs) < EPS;
  bool is_qpxr_0 = abs(qpxr) < EPS;
  if (is_rxs_0 and is_qpxr_0){
    return (0 <= (q - p) * r && (q - p) * r <= r * r) ||
           (0 <= (p - q) * s && (p - q) * s <= s * s);
  }
  if (is_rxs_0 and not is_qpxr_0){
    return false;
  }

  auto t = cross((q - p),s)/rxs;
  auto u = cross((q - p),r)/rxs;

  if (not is_rxs_0 and (0 <= t and t <= 1) and (0 <= u and u <= 1)){
    inter = p + r * t;
    return true;
  }
  return false;

}

bool intersects(point a, point b, vector<point> poly, point &inter, ull &next) {
  for (ull i = 0, j = 1; i < poly.size(); ++i, j = (i + 1) % poly.size()) {
    if (intersect(a, b, poly[i], poly[j], inter)) {
      next = j;
      return true;
    }
  }
  return false;
}

bool union_polys(vector<point> poly1, vector<point> poly2, vector<point> &out) {
  ull outside_pos;
  bool found = false;
  for (ull i = 0; i < poly1.size(); ++i) {
    if (not PointInPoly(poly1[i], poly2)) {
      found = true;
      outside_pos = i;
      break;
    }
  }
  if (not found) {
    // Polygons contains each other or do not intersect.
    if (PointInPoly(poly2[0], poly1)) {
      // One contains two
      out = poly1;
      return true;
    }
    if (PointInPoly(poly1[0], poly2)) {
      // Two contains one
      out = poly2;
      return true;
    }
    return false;
  }

  // Assuming both polys are clockwise oriented, start from outside position.
  // For each step, get the next point in the current polygon, find if the other
  // polygon intersects it. If not, just add it to the output and continue.
  // Otherwise, add the intersection, turn anti-clockwise and shift to the other
  // poly.
  int current_poly = 1;
  ull current_pos = outside_pos;
  ull next_pos;
  vector<point> output;
  output.push_back(poly1[current_pos]);
  bool has_intersection = false;
  do {
    if (current_poly == 1) {
      next_pos = (current_pos + 1) % poly1.size();
      point intersection;
      ull next;
      if (intersects(poly1[current_pos], poly1[next_pos], poly2, intersection,
                     next)) {
        current_poly = 2;
        output.push_back(intersection);
        output.push_back(poly2[next]);
        current_pos = next;
        has_intersection = true;
      }
      else {
        current_pos = next_pos;
        output.push_back(poly1[current_pos]);
      }
    } else {
      next_pos = (current_pos + 1) % poly2.size();
      point intersection;
      ull next;
      if (intersects(poly2[current_pos], poly2[next_pos], poly1, intersection,
                     next)) {
        current_poly = 1;
        output.push_back(intersection);
        output.push_back(poly1[next]);
        current_pos = next;
        has_intersection = true;
      }
      else {
        current_pos = next_pos;
        output.push_back(poly2[current_pos]);
      }
    }

  } while (current_pos != outside_pos || current_poly == 2);

  if (not has_intersection){
    return false;
  }
  output.erase(output.end() - 1); // Erase last one
  out = output;
  return true;
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

    while (true) {
      if (polys.size() == 1){
        break;
      }
      vector<point> tmp;
      bool unioned = false;
      for (ull k = 0, l = 1; k < polys.size(); ++k, l = (k + 1) % polys.size()) {
        if (union_polys(polys[k], polys[l], tmp)){
          if (l > k){
            polys.erase(polys.begin() + k);
            polys.erase(polys.begin() + l);
          }
          else {
            polys.erase(polys.begin() + l);
            polys.erase(polys.begin() + k);
          }
          polys.push_back(tmp);
          unioned = true;
          break;
        }
      }
      if (not unioned){
        break;
      }
    }

    long double total_union_area = 0;
    for (auto &poly : polys) {
      total_union_area += area(poly);
    }
    printf("%.8Lf\n", total_union_area);
  }
  return 0;
}