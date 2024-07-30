#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <vector>

struct Point {
    double x, y, ang;

    Point operator-(const Point& p) const { return {x - p.x, y - p.y, 0}; }
};

class ConvexHull {
public:
    static std::vector<Point> grahamScan(std::vector<Point>& points);
};

#endif // CONVEX_HULL_H
