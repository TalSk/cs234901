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
#include <iomanip>      // std::setprecision


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

struct vec {
    double x, y; // name: `vec' is different from STL vector
    vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(point a, point b) { // convert 2 points to vector a->b
    return vec(b.x - a.x, b.y - a.y);
}

typedef pair<point, point> segment;

int seg_sort(segment a, segment b) {
    return a.first < b.first;
}

long double seg_area(segment seg) {
    return ((seg.first.y + seg.second.y) * (seg.second.x - seg.first.x)) / 2;
}

long double y_val(segment seg, float x) {
    long double x1 = seg.first.x, y1 = seg.first.y, x2 = seg.second.x, y2 = seg.second.y;
    long double m = (y2 - y1) / (x2 - x1);
    long double n = y1 - m * x1;
    return m * x + n;
}

point intersection(segment AB, segment CD) {
    // Line AB represented as a1x + b1y = c1 
    auto A = AB.first, B = AB.second, C = CD.first, D = CD.second;
    double a1 = B.y - A.y;
    double b1 = A.x - B.x;
    double c1 = a1 * (A.x) + b1 * (A.y);

    // Line CD represented as a2x + b2y = c2 
    double a2 = D.y - C.y;
    double b2 = C.x - D.x;
    double c2 = a2 * (C.x) + b2 * (C.y);

    double determinant = a1 * b2 - a2 * b1;

    if (determinant == 0)
    {
        // The lines are parallel. This is simplified 
        // by returning a pair of FLT_MAX 
        return { 1000000, 1000000 };
    }
    else
    {
        double x = (b2 * c1 - b1 * c2) / determinant;
        double y = (a1 * c2 - a2 * c1) / determinant;
        return { x, y };
    }
}

int main() {
	int N;
	cin >> N;
    double x1, y1, x2, y2;
    segment curr, new_seg;
	vector<segment> segments, segments_b;


	for (size_t i = 0; i < N; i++)
	{
        long double new_area = 0;
        cin >> x1 >> y1 >> x2 >> y2;
        curr = { {x1, y1}, {x2, y2} };

        long double curr_area = seg_area(curr);

        sort(segments.begin(), segments.end(), seg_sort);
        segments_b.clear();
        bool pushed_curr = false;

        for (pair<point, point> seg : segments)
        {
            if (pushed_curr) {
                segments_b.push_back(seg);
                continue;
            }
            if (seg.second.x <= curr.first.x || curr.second.x <= seg.first.x) {
                segments_b.push_back(seg);
                continue;
            }

            if (curr.first.x <= seg.first.x && curr.second.x <= seg.second.x) { // curr out on left, in on right
                new_seg = { curr.first , {seg.first.x, y_val(curr, seg.first.x)} };
                new_area += seg_area(new_seg);
                segments_b.push_back(new_seg);
                curr = {new_seg.second, curr.second};

                if (curr.first.y <= seg.first.y && curr.second.y <= y_val(seg, curr.second.x)) { // completly under
                    segments_b.push_back(seg);
                }
                else if (curr.first.y >= seg.first.y && curr.second.y >= y_val(seg, curr.second.x)) { // completly over
                    segments_b.push_back(curr);
                    segments_b.push_back({ {curr.second.x, y_val(seg, curr.second.x)},seg.second });
                    new_area += (seg_area(curr)) - (seg_area({ seg.first, {curr.second.x, y_val(seg, curr.second.x)} }));
                }
                else { // intersecting
                    point inter = intersection(curr, seg);
                    // up to down (of curr)
                    if (curr.first.y > seg.first.y) {
                        new_seg = {curr.first, inter};
                        new_area += seg_area(new_seg) - seg_area({seg.first, inter});
                        segments_b.push_back(new_seg);
                        segments_b.push_back({inter, seg.second});
                    }
                    // down to up
                    else {
                        segments_b.push_back({ seg.first,inter});
                        new_seg = {inter, curr.second};
                        new_area += seg_area(new_seg) - seg_area({ inter, {curr.second.x, y_val(seg, curr.second.x)} });
                        segments_b.push_back(new_seg);
                        segments_b.push_back({ {curr.second.x, y_val(seg, curr.second.x)}, seg.second});
                    }
                }
                
                pushed_curr = true;
                continue;
            }

            if (curr.first.x >= seg.first.x && curr.second.x <= seg.second.x) { // curr in on left, in on right
                new_seg = { seg.first, {curr.first.x, y_val(seg, curr.first.x)} };
                segments_b.push_back(new_seg);

                seg = {new_seg.second, seg.second};
                if (curr.first.y <= seg.first.y && curr.second.y <= y_val(seg, curr.second.x)) { // completly under
                    segments_b.push_back(seg);
                }
                else if (curr.first.y >= seg.first.y && curr.second.y >= y_val(seg, curr.second.x)) { // completly over
                    segments_b.push_back(curr);
                    segments_b.push_back({ {curr.second.x, y_val(seg, curr.second.x)},seg.second });
                    new_area += (seg_area(curr)) - (seg_area({ seg.first, {curr.second.x, y_val(seg, curr.second.x)} }));
                }
                else { // intersecting
                    point inter = intersection(curr, seg);
                    // up to down (of curr)
                    if (curr.first.y > seg.first.y) {
                        new_seg = { curr.first, inter };
                        new_area += seg_area(new_seg) - seg_area({ seg.first, inter });
                        segments_b.push_back(new_seg);
                        segments_b.push_back({ inter, seg.second });
                    }
                    // down to up
                    else {
                        segments_b.push_back({ seg.first,inter });
                        new_seg = { inter, curr.second };
                        new_area += seg_area(new_seg) - seg_area({ inter, {curr.second.x, y_val(seg, curr.second.x)} });
                        segments_b.push_back(new_seg);
                        segments_b.push_back({ {curr.second.x, y_val(seg, curr.second.x)}, seg.second });
                    }
                }

                pushed_curr = true;
                continue;
            }

            if (curr.first.x >= seg.first.x && curr.second.x >= seg.second.x) { // curr in on left, out on right
                new_seg = { seg.first , {curr.first.x, y_val(seg, curr.first.x)} };
                segments_b.push_back(new_seg);
                seg = { {curr.first.x, y_val(seg, curr.first.x)}, seg.second };

                if (curr.first.y <= seg.first.y && y_val(curr, seg.second.x) <= seg.second.y) { // completly under
                    segments_b.push_back(seg);
                }
                else if (curr.first.y >= seg.first.y && y_val(curr, seg.second.x) >= seg.second.y) { // completly over
                    new_seg = { curr.first, {seg.second.x, y_val(curr, seg.second.x)} };
                    segments_b.push_back(new_seg);
                    new_area += (seg_area(new_seg)) - (seg_area(seg));
                }
                else { // intersecting
                    point inter = intersection(curr, seg);
                    // up to down (of curr)
                    if (curr.first.y > seg.first.y) {
                        new_seg = { curr.first, inter };
                        new_area += seg_area(new_seg) - seg_area({ seg.first, inter });
                        segments_b.push_back(new_seg);
                        segments_b.push_back({ inter, seg.second });
                    }
                    // down to up
                    else {
                        segments_b.push_back({ seg.first,inter });
                        new_seg = { inter, {seg.second.x, y_val(curr,seg.second.x) } };
                        new_area += seg_area(new_seg) - seg_area({ inter, seg.second });
                        segments_b.push_back(new_seg);
                    }
                }
                curr = { {seg.second.x, y_val(curr, seg.second.x)}, curr.second };
                continue;
            }

            if (curr.first.x <= seg.first.x && curr.second.x >= seg.second.x) { // curr out on left, out on right
                new_seg = { curr.first, {seg.first.x, y_val(curr, seg.first.x)} };
                segments_b.push_back(new_seg);
                new_area += seg_area(new_seg);

                curr = { new_seg.second, curr.second };

                if (curr.first.y <= seg.first.y && y_val(curr, seg.second.x) <= seg.second.y) { // completly under
                    segments_b.push_back(seg);
                }
                else if (curr.first.y >= seg.first.y && y_val(curr, seg.second.x) >= seg.second.y) { // completly over
                    new_seg = { curr.first, {seg.second.x, y_val(curr, seg.second.x)} };
                    segments_b.push_back(new_seg);
                    new_area += (seg_area(new_seg)) - (seg_area(seg));
                }
                else { // intersecting
                    point inter = intersection(curr, seg);
                    // up to down (of curr)
                    if (curr.first.y > seg.first.y) {
                        new_seg = { curr.first, inter };
                        new_area += seg_area(new_seg) - seg_area({ seg.first, inter });
                        segments_b.push_back(new_seg);
                        segments_b.push_back({ inter, seg.second });
                    }
                    // down to up
                    else {
                        segments_b.push_back({ seg.first,inter });
                        new_seg = { inter, {seg.second.x, y_val(curr,seg.second.x) } };
                        new_area += seg_area(new_seg) - seg_area({ inter, seg.second });
                        segments_b.push_back(new_seg);
                    }
                }
                curr = { {seg.second.x, y_val(curr, seg.second.x)}, curr.second };
                continue;
            }

        }

        if (!pushed_curr) {
            new_area += seg_area(curr);
            segments_b.push_back(curr);
        }

        cout << setprecision(8) << new_area / curr_area << endl;
        segments = segments_b;

	}

	return 0;
}