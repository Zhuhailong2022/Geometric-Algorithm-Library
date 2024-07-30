#ifndef FINDINTERSECTION_H
#define FINDINTERSECTION_H

#include <iostream>
#include <cmath>
#include <stdexcept>

struct Point {
    double x, y;
};

// 求两条直线的交点，输入直线方程的系数
Point findIntersection(double A1, double B1, double C1, double A2, double B2, double C2);

#endif // FINDINTERSECTION_H