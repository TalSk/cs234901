#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <time.h>
#include <utility>
#include <vector>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define EPS 1e-9
#define MAX_SIZE 100

using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI                                                                     \
  acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

double DEG_to_RAD(long double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

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

long double dist(point p1, point p2) { // Euclidean distance
  // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
  return hypot(p1.x - p2.x, p1.y - p2.y);
}

struct command {
  enum cmd_t { MoveForward, MoveBack, TurnLeft, TurnRight };
  cmd_t cmd;
  string num_or_qm;
  ll number;

  command() : number(-1), num_or_qm(), cmd() {}
  command(const string &str_cmd, string num_or_qm_str)
      : number(-1) {
    num_or_qm = num_or_qm_str;
    if (str_cmd == "fd") {
      cmd = MoveForward;
    } else if (str_cmd == "bk") {
      cmd = MoveBack;
    } else if (str_cmd == "lt") {
      cmd = TurnLeft;
    } else if (str_cmd == "rt") {
      cmd = TurnRight;
    } else {
      assert(false);
    }
  }

  ll get_num() {
    if (number != -1){
      return number;
    }
    if (num_or_qm == "?") {
      return -1;
    }
    istringstream os(num_or_qm);
    os >> number;
    return number;
  }
};

vector<command> g_all;
// Walks over all commands in the global g_all vector, and finds out the final
// point to which the robot gets to. (Assumes that all the commands are filled)
point walk() {
  long double x = 0.0, y = 0.0;
  long double current_angle = 0.0;
  command::cmd_t cur_cmd;
  long double number;
  for (auto &cmd : g_all) {
    cur_cmd = cmd.cmd;
    number = cmd.get_num();
    switch (cur_cmd) {
    case command::MoveForward:
      x += number * cos(DEG_to_RAD(current_angle));
      y += number * sin(DEG_to_RAD(current_angle));
      break;
    case command::MoveBack:
      x -= number * cos(DEG_to_RAD(current_angle));
      y -= number * sin(DEG_to_RAD(current_angle));
      break;
    case command::TurnRight:
      current_angle -= number;
      break;
    case command::TurnLeft:

      current_angle += number;
      break;
    default:
      assert(false);
    }
  }
  return {x, y};
}

int main() {
  ull t;
  while (cin >> t) {
    for (int bla = 0; bla < t; ++bla) {
      ull n;
      cin >> n;
      string qm_command, num_str, command;
      int pos = 0;
      // Get all input plus find out whether we need to find angle or distance.
      for (int i = 0; i < n; ++i) {
        cin >> command >> num_str;
        g_all.emplace_back(command, num_str);
        if (num_str == "?") {
          qm_command = command;
          pos = i;
        }
      }
      if (qm_command == "bk" or qm_command == "fd") {
        // Set the distance walked on the question mark to 0 and find the final
        // point in this walk.
        g_all[pos].number = 0;
        auto xy = walk();
        // Calculate the distance from found point to 0,0
        auto distance = dist(point(xy.x, xy.y), point());
        cout << abs(distance) << endl;
      } else {
        // We need to find the appropriate degree. Since they are all integers,
        // just iterate over all possible values and it should be quick enough
        for (int i = 0; i < 360; ++i) {
          g_all[pos].number = i; // Change question mark to current degree.
          auto xy = walk();
          if (abs(xy.x) < 1e-2 and abs(xy.y) < 1e-2) {
            cout << i << endl;
            break;
          }
        }
      }
      g_all.clear();
    }
    return 0;
  }
}