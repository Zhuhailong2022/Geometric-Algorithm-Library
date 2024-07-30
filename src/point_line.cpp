// point_line.cpp

#include "point_line.h"

// 函数用于计算 PQ 向量与 v 向量的叉积
double crossProduct(const Point& P, const Point& Q, const Vector& v) {
    double pq_x = Q.x - P.x;
    double pq_y = Q.y - P.y;
    return pq_x * v.y - pq_y * v.x;
}

// 函数用于判断点 Q 相对于过点 P 的直线的位置关系
std::string determinePosition(const Point& P, const Point& Q, const Vector& v) {
    double cross = crossProduct(P, Q, v);
    if (cross > 0) {
        return "Point is above the line";
    } else if (cross < 0) {
        return "Point is below the line";
    } else {
        return "Pointis on the line";
    }
}
