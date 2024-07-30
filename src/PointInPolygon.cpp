#include "PointInPolygon.h"
#include <cmath>
#include <algorithm>

namespace PointInPolygon {

// 判断点是否在线段上
bool isPointOnSegment(const Point& p, const Point& v1, const Point& v2) {
    double minX = std::min(v1.x, v2.x);
    double maxX = std::max(v1.x, v2.x);
    double minY = std::min(v1.y, v2.y);
    double maxY = std::max(v1.y, v2.y);
    bool onSegment = (p.x >= minX && p.x <= maxX && p.y >= minY && p.y <= maxY &&
                      std::fabs((v2.y - v1.y) * (p.x - v1.x) - (v2.x - v1.x) * (p.y - v1.y)) < 1e-9);
    return onSegment;
}

// 光线投射算法，射线默认向右侧发射
bool isPointInPolygonRayCasting(const Point& pt, const std::vector<Point>& polygon) {
    int intersectCount = 0; // 交点计数
    for (size_t i = 0; i < polygon.size(); ++i) {
        Point v1 = polygon[i];
        Point v2 = polygon[(i + 1) % polygon.size()];

        // 检查点是否在边界上
        if (isPointOnSegment(pt, v1, v2)) {
            return true;
        }

        if ((v1.y > pt.y) != (v2.y > pt.y)) {
            double slope = (v2.x - v1.x) / (v2.y - v1.y);
            double x = v1.x + slope * (pt.y - v1.y);
            if (x > pt.x) {
                intersectCount++; // 交点计数加1
            }
        }
    }
    // 如果交点数为奇数，点在多边形内
    return (intersectCount % 2) == 1;
}
// 计算方向
int computeOrientation(const Point& p, const Point& q, const Point& r) {
    double val = (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
    if (val == 0) return 0;  // 共线
    return (val > 0) ? 1 : -1; // 顺时针 或 逆时针
}

// 回转数算法
bool isPointInPolygonWindingNumber(const Point& pt, const std::vector<Point>& polygon) {
    int windingNumber = 0; // 回转数

    for (size_t i = 0; i < polygon.size(); ++i) {
        Point v1 = polygon[i];
        Point v2 = polygon[(i + 1) % polygon.size()];

        // 检查点是否在边界上
        if (isPointOnSegment(pt, v1, v2)) {
            return true; // 点在边界上
        }

        // 计算回转数
        if (v1.y <= pt.y) {
            if (v2.y > pt.y && computeOrientation(v1, v2, pt) == 1) {
                windingNumber++;
            }
        } else {
            if (v2.y <= pt.y && computeOrientation(v1, v2, pt) == -1) {
                windingNumber--;
            }
        }
    }

    // 如果回转数不为0，点在多边形内；否则在外部
    return windingNumber != 0;
}


} // namespace PointInPolygon
