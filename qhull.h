#ifndef QHULL_H_
#define QHULL_H_

#include <algorithm>
#include <cmath>
#include <vector>

struct Point {
  float x;
  float y;

  bool operator<(const Point &pt) const {
    if (x == pt.x) {
      return (y <= pt.y);
    }
    return (x < pt.x);
  }
};

// http://stackoverflow.com/questions/1560492/how-to-tell-whether-a-point-is-to-the-right-or-left-side-of-a-line
// A and B are used to define a line
// C is the point whose side we're trying to determine
int32_t SideOfLine(const Point &P1, const Point &P2, const Point &P3) {
    return (P2.x - P1.x) * (P3.y - P1.y) - (P2.y - P1.y) * (P3.x - P1.x);
}

// https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line#Line_defined_by_two_points
float DistanceFromLine(const Point &P1, const Point &P2, const Point &P3) {
  return (std::abs((P2.y - P1.y) * P3.x - (P2.x - P1.x) * P3.y + P2.x * P1.y - P2.y * P1.x) 
         / std::sqrt((P2.y - P1.y) * (P2.y - P1.y) + (P2.x - P1.x) * (P2.x - P1.x)));
}

// http://stackoverflow.com/questions/13300904/determine-whether-point-lies-inside-triangle
bool PointInTriangle(const Point &p, const Point &p1, const Point &p2, const Point &p3) {
  float a = ((p2.y - p3.y) * (p.x - p3.x) + (p3.x - p2.x) * (p.y - p3.y)) / ((p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y));
  float b = ((p3.y - p1.y) * (p.x - p3.x) + (p1.x - p3.x) * (p.y - p3.y)) / ((p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y));
  float c = 1.0f - a - b;
  return (0.0f < a && 0.0f < b && 0.0f < c);
}

// http://www.cse.yorku.ca/~aaw/Hang/quick_hull/Algorithm.html
void FindHull(const std::vector<Point> &Sk, const Point P, const Point Q, std::vector<Point> &hullPoints) {
  // If Sk has no point, then  return
  if (Sk.size() == 0) return;

  std::vector<Point> S0;
  std::vector<Point> S1;
  std::vector<Point> S2;

  // From the given set of points in Sk, find farthest point, say C, from segment PQ 
  float furthestDistance = 0.0f;
  Point C;
  for (const auto &pt : Sk) {
    float distance = DistanceFromLine(P, Q, pt);
    if (distance > furthestDistance) {
      furthestDistance = distance;
      C = pt;
    }
  }
  // Add point C to convex hull at the location between P and Q 
  hullPoints.push_back(C);

  /*
   * Three points P, Q, and C partition the remaining points of Sk into 3 subsets: S0, S1, and S2 
   * where S0 are points inside triangle PCQ, S1are points on the right side of the oriented 
   * line from  P to C, and S2 are points on the right side of the oriented line from C to Q.
   */
  for (const auto &pt : Sk) {
    if (PointInTriangle(pt, P, C, Q)) {
      S0.push_back(pt);
    } else if (0 < SideOfLine(P, C, pt)) {
      S1.push_back(pt);
    } else if (0 < SideOfLine(C, Q, pt)) {
      S2.push_back(pt);
    }
  }

  FindHull(S1, P, C, hullPoints);
  FindHull(S2, C, Q, hullPoints);
}

// http://www.cse.yorku.ca/~aaw/Hang/quick_hull/Algorithm.html
void QuickHull(const std::vector<Point> &s, std::vector<Point> &hullPoints) {
  // Find left and right most points, say A & B, and add A & B to convex hull 
  Point A = s[0];
  Point B = s[s.size() - 1];
  hullPoints.push_back(A);
  hullPoints.push_back(B);

  std::vector<Point> S1;
  std::vector<Point> S2;

  /*
   * Segment AB divides the remaining (n-2) points into 2 groups S1 and S2 
   * where S1 are points in S that are on the right side of the oriented line from A to B, 
   * and S2 are points in S that are on the right side of the oriented line from B to A 
   */
  for (auto it = s.begin() + 1; it != s.end() - 1; ++it) {
    const Point pt = *it;
    const int32_t s1 = SideOfLine(A, B, pt);
    const int32_t s2 = SideOfLine(B, A, pt);
    if (0 < s1) {
      S1.push_back(pt);
    } else if (0 < s2) {
      S2.push_back(pt);
    }
  }

  FindHull(S1, A, B, hullPoints);
  FindHull(S2, B, A, hullPoints);
}

#endif
