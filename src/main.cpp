// #include <SFML/Graphics.hpp>
// #include "delaunay.h"
// #include <vector>

// int main() {
//     // 定义 20 个点
//     Point points[] = {
//         Point(100, 100, 0), Point(200, 100, 1), Point(300, 100, 2),
//         Point(400, 100, 3), Point(500, 100, 4), Point(150, 200, 5),
//         Point(250, 200, 6), Point(350, 200, 7), Point(450, 200, 8),
//         Point(550, 200, 9), Point(100, 300, 10), Point(200, 300, 11),
//         Point(300, 300, 12), Point(400, 300, 13), Point(500, 300, 14),
//         Point(150, 400, 15), Point(250, 400, 16), Point(350, 400, 17),
//         Point(450, 400, 18), Point(550, 400, 19)
//     };
//     int n = 20;

//     // 创建 Delaunay 对象并初始化
//     Delaunay dt;
//     dt.init(n, points);

//     // 使用 SFML 绘制
//     sf::RenderWindow window(sf::VideoMode(800, 600), "Delaunay Triangulation");

//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) window.close();
//         }

//         window.clear(sf::Color::White);

//         // 绘制点
//         for (int i = 0; i < n; ++i) {
//             sf::CircleShape shape(3);
//             shape.setPosition(points[i].x - shape.getRadius(), points[i].y - shape.getRadius());
//             shape.setFillColor(sf::Color::Red);
//             window.draw(shape);
//         }

//         // 绘制边
//         auto edges = dt.getEdge();
//         for (const auto& edge : edges) {
//             sf::Vertex line[] = {
//                 sf::Vertex(sf::Vector2f(points[edge.first].x, points[edge.first].y), sf::Color::Black),
//                 sf::Vertex(sf::Vector2f(points[edge.second].x, points[edge.second].y), sf::Color::Black)
//             };
//             window.draw(line, 2, sf::Lines);
//         }

//         window.display();
//     }

//     return 0;
// }


// #include <SFML/Graphics.hpp>
// #include <iostream>
// #include <vector>
// #include "convex_hull.h" // 确保这个头文件提供了 Point 结构体和 ConvexHull 类

// int main() {
//     // 原始点集合
//     std::vector<Point> points = {{0, 0}, {1, 1}, {2, 2}, {3, 1}, {0, 3},{4, 2}, {5, 3}, {6, 1}};
//     std::cout << "原始点：\n";
//     for (const auto& p : points) {
//         std::cout << "(" << p.x << ", " << p.y << ")\n";
//     }

//     // 计算凸包
//     std::vector<Point> hull = ConvexHull::grahamScan(points);

//     std::cout << "凸包点：\n";
//     for (const auto& p : hull) {
//         std::cout << "(" << p.x << ", " << p.y << ")\n";
//     }

//     // 创建窗口
//     sf::RenderWindow window(sf::VideoMode(1600, 1200), "Convex Hull");

//     // 创建 VertexArray 用于绘制
//     sf::VertexArray vertices(sf::LineStrip);

//     // 计算所有点的范围
//     double minX = std::numeric_limits<double>::max();
//     double maxX = std::numeric_limits<double>::lowest();
//     double minY = std::numeric_limits<double>::max();
//     double maxY = std::numeric_limits<double>::lowest();
    
//     for (const auto& point : hull) {
//         if (point.x < minX) minX = point.x;
//         if (point.x > maxX) maxX = point.x;
//         if (point.y < minY) minY = point.y;
//         if (point.y > maxY) maxY = point.y;
//     }

//     // 确定缩放因子
//     double scaleX = window.getSize().x / (maxX - minX);
//     double scaleY = window.getSize().y / (maxY - minY);
//     double scale = std::min(scaleX, scaleY); // 选择较小的缩放因子以保持图形比例

//     // 计算窗口的中心
//     double offsetX = (window.getSize().x - (maxX - minX) * scale) / 2;
//     double offsetY = (window.getSize().y - (maxY - minY) * scale) / 2;

//     // 转换点到 SFML 窗口坐标系
//     for (const auto& point : hull) {
//         sf::Vector2f screenPoint((point.x - minX) * scale + offsetX, window.getSize().y - (point.y - minY) * scale - offsetY);
//         vertices.append(sf::Vertex(screenPoint, sf::Color::Green));
//     }

//     // 闭合多边形
//     if (!hull.empty()) {
//         sf::Vector2f screenPoint((hull.front().x - minX) * scale + offsetX, window.getSize().y - (hull.front().y - minY) * scale - offsetY);
//         vertices.append(sf::Vertex(screenPoint, sf::Color::Green));
//     }

//     // 主循环
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }
//         }

//         window.clear();
//         window.draw(vertices);
//         window.display();
//     }

//     return 0;
// }



//判断点在线段的哪个位置

// #include "point_line.h"

// int main() {
//     Point P = {0, 0};
//     Point Q = {1, 1};
//     Vector v = {1, 0}; // x轴方向的单位向量

//     std::cout << determinePosition(P, Q, v) << std::endl;

//     return 0;
// }


// #include <iostream>
// #include "LineSegmentIntersection.h"

// using namespace LineSegmentIntersection;

// void testIntersection(const Point& A1, const Point& A2, const Point& B1, const Point& B2) {
//     bool intersect = segmentsIntersect(A1, A2, B1, B2);
//     std::cout << "Line segment (" << A1.x << ", " << A1.y << ") to ("
//               << A2.x << ", " << A2.y << ") and line segment ("
//               << B1.x << ", " << B1.y << ") to ("
//               << B2.x << ", " << B2.y << ") ";
//     if (intersect) {
//         std::cout << "intersect.\n";
//     } else {
//         std::cout << "do not intersect.\n";
//     }
// }

// int main() {
//     // Define some test points and line segments
//     Point A1 = {0, 0};
//     Point A2 = {4, 4};
//     Point B1 = {0, 4};
//     Point B2 = {4, 0};

//     Point C1 = {0, 0};
//     Point C2 = {1, 1};
//     Point D1 = {2, 2};
//     Point D2 = {3, 3};

//     Point E1 = {0, 0};
//     Point E2 = {1, 1};
//     Point F1 = {2, 3};
//     Point F2 = {3, 4};

//     std::cout << "Testing intersections:\n";

//     // Test cases
//     testIntersection(A1, A2, B1, B2); // Expected: intersect
//     testIntersection(C1, C2, D1, D2); // Expected: do not intersect
//     testIntersection(E1, E2, F1, F2); // Expected: do not intersect

//     return 0;
// }


// #include <iostream>
// #include <vector>
// #include "PointInPolygon.h"

// using namespace PointInPolygon;

// void testPointInPolygon(const Point& pt, const std::vector<Point>& polygon) {
//     bool inPolygonRayCasting = isPointInPolygonRayCasting(pt, polygon);
//     bool inPolygonWindingNumber = isPointInPolygonWindingNumber(pt, polygon);

//     std::cout << "Point (" << pt.x << ", " << pt.y << "):\n";
//     std::cout << "  Ray Casting: " << (inPolygonRayCasting ? "Inside or On Edge" : "Outside") << "\n";
//     std::cout << "  Winding Number: " << (inPolygonWindingNumber ? "Inside or On Edge" : "Outside") << "\n";
// }

// int main() {
//     // 定义一个多边形
//     std::vector<Point> polygon = {
//         {0, 0}, {0, 2}, {3, 2}, {3, 1}, {2, 1}
//     };

//     // 定义一些测试点
//     std::vector<Point> testPoints = {
//         {2, 2}, // Inside
//         {4, 2}, // On edge
//         {5, 2}, // Outside
//         {0, 0}, // On vertex
//         {4, 4}, // On vertex
//         {-1, -1} // Outside
//     };

//     std::cout << "Testing points against polygon:\n";
//     for (const auto& pt : testPoints) {
//         testPointInPolygon(pt, polygon);
//     }

//     return 0;
// }





//测试求交点程序
// #include "findIntersection.h"

// int main() {
//     try {
//         // 测试交点
//         Point p1 = findIntersection(1, -1, 0, 1, 1, -4);
//         std::cout << "Intersection Point: (" << p1.x << ", " << p1.y << ")\n";

//         // 测试平行线（应抛出异常）
//         Point p2 = findIntersection(1, -1, 0, 1, -1, 1);
//         std::cout << "Intersection Point: (" << p2.x << ", " << p2.y << ")\n";
//     } catch (const std::runtime_error& e) {
//         std::cout << "Error: " << e.what() << std::endl;
//     }

//     return 0;
// }


//测试面积计算程序


#include <iostream>
#include <vector>
#include <polygonArea.h>
// 测试程序
int main() {
        // 定义一个多边形
        std::vector<_Point> polygon = {
            {0, 0}, {4, 0}, {4, 4}, {0, 4}
        };

        // 确保 polygon 的大小正确
        std::cout << "Polygon vertices size: " << polygon.size() << std::endl;

        // 计算面积
        double area = polygonArea(polygon);

        // 输出结果
        std::cout << "The area of the polygon is: " << area << std::endl;

    return 0;
}