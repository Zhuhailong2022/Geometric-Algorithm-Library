#ifndef POLYGON_AREA_H
#define POLYGON_AREA_H

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>



struct _Point {
    _Point(double x, double y) : x(x), y(y) {}
    double x, y;
};
double polygonArea(const std::vector<_Point>& vertices);
#endif // POLYGON_AREA_H