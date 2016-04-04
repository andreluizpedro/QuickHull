#include <chrono>
#include <cstdio>
#include <random>
#include <vector>

#include "qhull.h"

int main() {
  const size_t number_of_points = 100;
  std::vector<Point> points;
  points.reserve(number_of_points);
  std::vector<Point> hullPoints;

  // Random number generator
  std::mt19937 mersenne_twister(std::chrono::high_resolution_clock::now().time_since_epoch().count());

  // Generate random points
  for (int i = 0; i < number_of_points; ++i) {
    Point pt;
    pt.x = (float)(mersenne_twister() % 1000);
    pt.y = (float)(mersenne_twister() % 1000);
    points.push_back(pt);
  }

  // Sort points so that we can find min and max
  std::sort(points.begin(), points.end());
  // Find convex hull points and place them into hullPoints
  QuickHull(points, hullPoints);

  // Save all points to a file
  {
    FILE *fp = fopen("points.csv", "w");
    for (const auto &pt : points) {
      fprintf(fp, "%.1f,%.1f\n", pt.x, pt.y);
    }
    fclose(fp);
  }

  // Save only convex hull points
  {
    FILE *fp = fopen("hull.csv", "w");
    for (const auto &pt : hullPoints) {
      fprintf(fp, "%.1f,%.1f\n", pt.x, pt.y);
    }
    fclose(fp);
  }
}
