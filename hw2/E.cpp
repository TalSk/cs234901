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
typedef long long ll;

using namespace std;

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
  long double x, y;        // only used if more precision is needed
  point() { x = y = 0.0; } // default constructor
  point(long double _x, long double _y) : x(_x), y(_y) {} // user-defined
  bool operator<(point other) const { // override less than operator
    if (fabs(x - other.x) > EPS)      // useful for sorting
      return x < other.x;             // first criteria , by x-coordinate
    return y < other.y;
  } // second criteria, by y-coordinate
  // use EPS (1e-9) when testing equality of two floating points
  bool operator==(point other) const {
    return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
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

// struct line { double a, b, c; };          // a way to represent a line

// the answer is stored in the third parameter (pass by reference)
// void pointsToLine(point p1, point p2, line &l) {
//  if (fabs(p1.x - p2.x) < EPS) {              // vertical line is fine
//    l.a = 1.0;   l.b = 0.0;   l.c = -p1.x;           // default values
//  } else {
//    l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
//    l.b = 1.0;              // IMPORTANT: we fix the value of b to 1.0
//    l.c = -(double)(l.a * p1.x) - p1.y;
//  } }

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

// bool areParallel(line l1, line l2) {       // check coefficients a & b
//  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }
//
// bool areSame(line l1, line l2) {           // also check coefficient c
//  return areParallel(l1 ,l2) && (fabs(l1.c - l2.c) < EPS); }
//
//// returns true (+ intersection point) if two lines are intersect
// bool areIntersect(line l1, line l2, point &p) {
//  if (areParallel(l1, l2)) return false;            // no intersection
//  // solve system of 2 linear algebraic equations with 2 unknowns
//  p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
//  // special case: test for vertical line to avoid division by zero
//  if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
//  else                  p.y = -(l2.a * p.x + l2.c);
//  return true; }

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
// void pointSlopeToLine(point p, double m, line &l) {
//  l.a = -m;                                               // always -m
//  l.b = 1;                                                 // always 1
//  l.c = -((l.a * p.x) + (l.b * p.y)); }                // compute this
//
// void closestPoint(line l, point p, point &ans) {
//  line perpendicular;         // perpendicular to l and pass through p
//  if (fabs(l.b) < EPS) {              // special case 1: vertical line
//    ans.x = -(l.c);   ans.y = p.y;      return; }
//
//  if (fabs(l.a) < EPS) {            // special case 2: horizontal line
//    ans.x = p.x;      ans.y = -(l.c);   return; }
//
//  pointSlopeToLine(p, 1 / l.a, perpendicular);          // normal line
//  // intersect line l with this perpendicular line
//  // the intersection point is the closest point
//  areIntersect(l, perpendicular, ans); }
//
//// returns the reflection of point on a line
// void reflectionPoint(line l, point p, point &ans) {
//  point b;
//  closestPoint(l, p, b);                     // similar to distToLine
//  vec v = toVec(p, b);                             // create a vector
//  ans = translate(translate(p, v), v); }         // translate p twice

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
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0;
}

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

struct segment {
  point s, e;
  long double m, b;
  segment() : s(0, 0), e(0, 0), m(0), b(0){};
  segment(point s, point e) : s(s), e(e) {
    m = (e.y - s.y) / (e.x - s.x);
    b = s.y - (m * s.x);
  };

  long double on_segment(long double x) const {
    if (x < s.x or x > e.x) {
      return -1;
    }
    return m * x + b;
  }
};

bool segmentSortByX(segment a, segment b) { return a.s.x < b.s.x; }

double det(double a, double b, double c, double d) { return a * d - b * c; }

inline bool betw(double l, double r, double x) {
  return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

inline bool intersect_1d(double a, double b, double c, double d) {
  if (a > b)
    swap(a, b);
  if (c > d)
    swap(c, d);
  return max(a, c) <= min(b, d) + EPS;
}

struct line {
  double a, b, c;

  line() {}
  line(point p, point q) {
    a = p.y - q.y;
    b = q.x - p.x;
    c = -a * p.x - b * p.y;
    norm();
  }

  void norm() {
    double z = sqrt(a * a + b * b);
    if (abs(z) > EPS)
      a /= z, b /= z, c /= z;
  }

  double dist(point p) const { return a * p.x + b * p.y + c; }
};

bool intersects(segment a, segment b, segment &intersection) {
  if (!intersect_1d(a.s.x, a.e.x, b.s.x, b.e.x) ||
      !intersect_1d(a.s.y, a.e.y, b.s.y, b.e.y))
    return false;
  line m(a.s, a.e);
  line n(b.s, b.e);
  double zn = det(m.a, m.b, n.a, n.b);
  if (abs(zn) < EPS) {
    if (abs(m.dist(b.s)) > EPS || abs(n.dist(a.s)) > EPS)
      return false;
    if (a.e < a.s)
      swap(a.s, a.e);
    if (b.e < b.s)
      swap(b.s, b.e);
    intersection.s = max(a.s, b.s);
    intersection.e = min(a.e, b.e);
    return true;
  } else {
    intersection.s.x = intersection.e.x = -det(m.c, m.b, n.c, n.b) / zn;
    intersection.s.y = intersection.e.y = -det(m.a, m.c, n.a, n.c) / zn;
    return betw(a.s.x, a.e.x, intersection.s.x) &&
           betw(a.s.y, a.e.y, intersection.s.y) &&
           betw(b.s.x, b.e.x, intersection.s.x) &&
           betw(b.s.y, b.e.y, intersection.s.y);
  }
}

// Assumes the segment vector does not contain overlapping segments.
long double area(const vector<segment> &skyline) {
  long double ans = 0;
  for (auto &seg : skyline) {
    ans += ((seg.s.y + seg.e.y) / 2) * (seg.e.x - seg.s.x);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ull N;
  while (cin >> N) {
    vector<segment> skyline;
    vector<segment> new_skyline;
    long double current_area, new_area, building_area;
    long double x1, x2, y1, y2;

    segment intersection;
    for (int i = 0; i < N; ++i) {
      sort(skyline.begin(), skyline.end(), segmentSortByX);
      current_area = area(skyline);

      cin >> x1 >> y1 >> x2 >> y2;
      segment cur_seg({x1, y1}, {x2, y2});
      building_area = ((y1 + y2) / 2) * (x2 - x1);

      vector<long double> temp;
      segment inter;
      bool add_seg = true;
      for (auto &seg : skyline) {
        if (seg.e.x <= cur_seg.s.x or seg.s.x >= cur_seg.e.x) {
          new_skyline.push_back(seg);
        } else {
          bool flag; // False is seg. True is cur_seg.
          point cur_p;
          if (seg.s.x < cur_seg.s.x) {
            flag = false;
            cur_p = seg.s;
            temp.push_back(cur_seg.s.x);
          } else if (cur_seg.s.x < seg.s.x) {
            flag = true;
            cur_p = cur_seg.s;
            temp.push_back(seg.s.x);
          } else {
            if (cur_seg.s.y < seg.s.y) {
              flag = false;
              cur_p = seg.s;
            } else {
              flag = true;
              cur_p = cur_seg.s;
            }
          }

          if (cur_seg.e.x <= seg.e.x) {
            add_seg = false;
            temp.push_back(cur_seg.e.x);
          } else {
            temp.push_back(seg.e.x);
          }

          if (intersects(seg, cur_seg, inter)) {
            if (find(temp.begin(), temp.end(), inter.s.x) == temp.end()) {
              temp.push_back(inter.s.x);
            }
            sort(temp.begin(), temp.end());
            for (auto &x : temp) {
              if (fabs(cur_seg.on_segment(x) - seg.on_segment(x)) < EPS) {
                if (flag) {
                  new_skyline.push_back({cur_p, {x, cur_seg.on_segment(x)}});
                }
                else {
                  new_skyline.push_back({cur_p, {x, seg.on_segment(x)}});
                }
                flag = not flag;
                cur_p = {x, seg.on_segment(x)};
              }
              if (not flag and cur_seg.on_segment(x) > seg.on_segment(x)) {
                flag = true;
                new_skyline.push_back({cur_p, {x, seg.on_segment(x)}});
                cur_p = {x, cur_seg.on_segment(x)};
              } else if (flag and cur_seg.on_segment(x) < seg.on_segment(x)) {
                flag = false;
                new_skyline.push_back({cur_p, {x, cur_seg.on_segment(x)}});
                cur_p = {x, seg.on_segment(x)};
              } else {
                assert(false);
              }
            }
            if (not add_seg) {
              // No segment of the given building is left.
              if (cur_seg.e.x < seg.e.x) {
                new_skyline.push_back(
                    segment({cur_seg.e.x, seg.on_segment(cur_seg.e.x)}, seg.e));
              }
              break;
            }
            // There is a part of the building segment left. Cut the remaining and
            // continue.
            cur_seg = segment({seg.e.x, cur_seg.on_segment(seg.e.x)}, cur_seg.e);
          } else {
            // Do not intersect

          }

        }
      }
      if (add_seg) {
        new_skyline.push_back(cur_seg);
      }
      new_area = area(new_skyline);

      //      auto poly_area = area(poly);
      //      polys.emplace_back(poly);
      //      new_area = polys_union_area(polys);
      //      if (new_area < current_area){
      //        cout << 0 << endl;
      //        continue;
      //      }
      printf("%.10Lf\n", (new_area - current_area) / building_area);
      skyline = new_skyline;
      new_skyline.clear();
    }
  }
}