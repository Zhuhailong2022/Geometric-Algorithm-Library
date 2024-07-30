#include "polygonArea.h"

double polygonArea(const std::vector<_Point>& vertices) {
    int n = vertices.size();
    if (n < 3) {
        return 0; // 不形成多边形
    }

    double area = 0.0;

    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n; // 下一个顶点
        area += vertices[i].x * vertices[j].y - vertices[i].y * vertices[j].x;
    }

    std::cout << "Computed raw area: " << area << std::endl;
    return std::fabs(area) / 2.0;
}