#include "findIntersection.h"

// 求两条直线的交点，输入直线方程的系数
Point findIntersection(double A1, double B1, double C1, double A2, double B2, double C2) {
    double determinant = A1 * B2 - A2 * B1;
    if (std::fabs(determinant) < 1e-9) {
        throw std::runtime_error("The lines are parallel or coincident, no unique intersection point.");
    }
    double x = (B2 * C1 - B1 * C2) / determinant;
    double y = (A1 * C2 - A2 * C1) / determinant;
    return {x, y};
}