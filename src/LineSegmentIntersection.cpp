#include "LineSegmentIntersection.h"

namespace LineSegmentIntersection {

// 判断两个点的最大值和最小值
double min(double a, double b) {
    return (a < b) ? a : b;
}

double max(double a, double b) {
    return (a > b) ? a : b;
}

// 计算向量 (P1P2) 和向量 (P1P3) 的叉积
double crossProduct(const Point& P1, const Point& P2, const Point& P3) {
    return (P2.x - P1.x) * (P3.y - P1.y) - (P2.y - P1.y) * (P3.x - P1.x);
}

// 快速排斥实验，判断两线段各自形成的矩形是否有交集，若没有则两线段一定不相交
bool boundingBoxIntersect(const Point& A1, const Point& A2, const Point& B1, const Point& B2) {
    return (min(A1.x, A2.x) <= max(B1.x, B2.x) &&
            min(B1.x, B2.x) <= max(A1.x, A2.x) &&
            min(A1.y, A2.y) <= max(B1.y, B2.y) &&
            min(B1.y, B2.y) <= max(A1.y, A2.y));
}

// 跨立实验
bool crossProductIntersect(const Point& A1, const Point& A2, const Point& B1, const Point& B2) {
    double d1 = crossProduct(A1, A2, B1);
    double d2 = crossProduct(A1, A2, B2);
    double d3 = crossProduct(B1, B2, A1);
    double d4 = crossProduct(B1, B2, A2);
    return (d1 * d2 <= 0) && (d3 * d4 <= 0);
}

// 判断两条线段是否相交
bool segmentsIntersect(const Point& A1, const Point& A2, const Point& B1, const Point& B2) {
    if (!boundingBoxIntersect(A1, A2, B1, B2)) {
        return false;
    }
    return crossProductIntersect(A1, A2, B1, B2);
}

} // namespace LineSegmentIntersection