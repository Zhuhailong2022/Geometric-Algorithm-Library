#ifndef POINT_IN_POLYGON_H
#define POINT_IN_POLYGON_H

#include <vector>
#include <iostream>

namespace PointInPolygon {

struct Point {
    double x;
    double y;
};

//光线投射算法
bool isPointInPolygonRayCasting(const Point& pt, const std::vector<Point>& polygon);
//回转数算法
bool isPointInPolygonWindingNumber(const Point& pt, const std::vector<Point>& polygon);

} // namespace PointInPolygon

#endif // POINT_IN_POLYGON_H
