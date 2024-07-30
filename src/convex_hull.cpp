#include "convex_hull.h"
#include <cmath>
#include <algorithm>
#include <iostream>

// 计算叉积
static double cross(const Point& p1, const Point& p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

// 比较函数用于排序
static bool cmp(const Point& p1, const Point& p2, const Point& p1_ref) {
    double angle1 = atan2(p1.y - p1_ref.y, p1.x - p1_ref.x);
    double angle2 = atan2(p2.y - p1_ref.y, p2.x - p1_ref.x);
    if (angle1 == angle2) {
        return sqrt((p1.x - p1_ref.x) * (p1.x - p1_ref.x) + (p1.y - p1_ref.y) * (p1.y - p1_ref.y)) <
               sqrt((p2.x - p1_ref.x) * (p2.x - p1_ref.x) + (p2.y - p1_ref.y) * (p2.y - p1_ref.y));
    }
    return angle1 < angle2;
}

std::vector<Point> ConvexHull::grahamScan(std::vector<Point>& points) {
    int n = points.size();
    if (n <= 1) return points;

    // 找到最低的点，若有多个相同最低点，则选择最左边的
    int min_point_idx = 0;
    for (int i = 1; i < n; ++i) {
        if (points[i].y < points[min_point_idx].y || (points[i].y == points[min_point_idx].y && points[i].x < points[min_point_idx].x)) {
            min_point_idx = i;
        }
    }
    std::swap(points[0], points[min_point_idx]);

    Point p1_ref = points[0];
    for (int i = 1; i < n; ++i) {
        points[i].ang = atan2(points[i].y - p1_ref.y, points[i].x - p1_ref.x);
    }

    std::sort(points.begin() + 1, points.end(), [p1_ref](const Point& p1, const Point& p2) {
        return cmp(p1, p2, p1_ref);
    });

    // 调试输出排序后的点
    std::cout << "Sorted Points:\n";
    for (const auto& p : points) {
        std::cout << "(" << p.x << ", " << p.y << ") Angle: " << p.ang << "\n";
    }

    std::vector<Point> hull;
    hull.push_back(points[0]);
    std::cout << "Initial Hull: (" << hull[0].x << ", " << hull[0].y << ")\n";

    for (int i = 1; i < n; ++i) {
        std::cout << "Processing Point: (" << points[i].x << ", " << points[i].y << ")\n";

        // 检查是否右拐，如果是则弹出栈顶的点
        while (hull.size() >= 2 && cross(hull[hull.size() - 1] - hull[hull.size() - 2], points[i] - hull[hull.size() - 1]) <= 0) {
            std::cout << "Popping Point: (" << hull.back().x << ", " << hull.back().y << ")\n";
            hull.pop_back();
        }

        hull.push_back(points[i]);
        std::cout << "Current Hull:\n";
        for (const auto& p : hull) {
            std::cout << "(" << p.x << ", " << p.y << ")\n";
        }
    }

    // 调试输出最终的凸包点
    std::cout << "Convex Hull Points:\n";
    for (const auto& p : hull) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return hull;
}
