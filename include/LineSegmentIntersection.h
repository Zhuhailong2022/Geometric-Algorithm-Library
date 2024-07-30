#ifndef LINE_SEGMENT_INTERSECTION_H
#define LINE_SEGMENT_INTERSECTION_H

namespace LineSegmentIntersection {

struct Point {
    double x, y;
};

// 判断两个点的最大值和最小值
double min(double a, double b);
double max(double a, double b);

// 计算向量 (P1P2) 和向量 (P1P3) 的叉积
double crossProduct(const Point& P1, const Point& P2, const Point& P3);

// 快速排斥实验
bool boundingBoxIntersect(const Point& A1, const Point& A2, const Point& B1, const Point& B2);

// 跨立实验
bool crossProductIntersect(const Point& A1, const Point& A2, const Point& B1, const Point& B2);

// 判断两条线段是否相交
bool segmentsIntersect(const Point& A1, const Point& A2, const Point& B1, const Point& B2);

} // namespace LineSegmentIntersection

#endif // LINE_SEGMENT_INTERSECTION_H