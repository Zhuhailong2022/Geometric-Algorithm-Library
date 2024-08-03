# 关于本库

欢迎访问我的计算几何算法库项目 "dynamicLibrary"。该库包含多种常用的计算几何算法，如判断点与多边形的位置关系、计算重叠矩形面积、判断线段是否相交、Delaunay 三角剖分算法以及 Graham 求凸包算法。

### 主要特性

* **点与多边形位置关系**：判断给定点是否在多边形内部、外部或边上。
* **计算重叠矩形面积**：计算两个矩形的重叠区域面积。
* **判断线段是否相交**：利用快速排斥实验和跨立实验检测两条线段是否相交。
* **Delaunay 三角剖分**：生成一组点的 Delaunay 三角剖分。
* **Graham 求凸包**：利用 Graham 扫描算法计算一组点的凸包。

### 使用方法

1. **包含头文件**：在需要使用这些算法的文件中包含相应的头文件。
2. **编译链接**：在编译时链接该算法库。

### 示例

使用算法库的示例代码在 `src` 文件夹下的 `main.cpp` 中给出。部分示例需要调用 SFML 库，使用这些测试用例之前需要安装 SFML 库。您可以执行项目根目录下的"setup"脚本程序，自动完成 SFML 库的安装、dynamicLibrary库编译以及main示例程序的编译。

使用“setup”脚本步骤：

1. 赋予脚本执行权限
2. 执行脚本

```
chmod +x setup.sh 
./setup.sh
```

### CMake 配置

项目的 CMakeLists 文件已经配置好，能够编译算法库和使用示例程序 `main.cpp`。

# 计算几何

## 几何基础

### 1.判断一点在直线的哪边

- 我们有直线上的一点 P 和直线的方向向量 v，想知道某个点 Q在直线的哪边。我们利用向量积的性质，算出 PQ 向量与 v 向量的外积。如果向量积为负，则Q在直线下方，如果向量积为 0，则 Q 在直线上，如果向量积为正，则 Q 在直线上方。

  - 公式如下：
    $$
    \vec{PQ} \times \vec{v} = (Q_x - P_x) \times v_y - (Q_y - P_y) \times v_x
    $$
- 代码实现如下：
- point_line.h文件
- ```c++
  // point_line.h

  #ifndef POINT_LINE_H
  #define POINT_LINE_H

  #include <string>
  #include <iostream>

  // 定义点
  struct Point {
      double x;
      double y;
  };

  // 定义向量
  struct Vector {
      double x;
      double y;
  };

  // 函数用于计算 PQ 向量与 v 向量的叉积
  double crossProduct(const Point& P, const Point& Q, const Vector& v);

  // 函数用于判断点 Q 相对于过点 P 的直线的位置关系
  std::string determinePosition(const Point& P, const Point& Q, const Vector& v);

  #endif // POINT_LINE_H

  ```
- point_line.cpp文件
- ```c++
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

  ```

### 2.快速排斥实验与跨立实验

- 判断两条线段是否相交。

  - 首先考虑特殊情况
    1. 两直线平行，这种情况通过判断线段所在直线的斜率是否相等即可。
    2. 两直线重合，如果两线段重合或部分重合，只需要判断是否有三点共线的情况即可。
    3. 两直线相交
- **快速排斥实验**

  - “两直线离得太远了”，如以下两直线
  - ![Seg1](https://oi-wiki.org/geometry/images/2d-seg1.svg)
  - 它们各自占的区域：
    - ![Seg2](https://oi-wiki.org/geometry/images/2d-seg2.svg)
    - 规定「一条线段的区域」为以这条线段为对角线的，各边均与某一坐标轴平行的矩形所占的区域，那么可以发现，如果两条线段没有公共区域，则这两条线段一定不相交。这便是快速排除实验，上述情况称作未通过快速排斥实验。需要注意的是，未通过快速排斥实验是两线段无交点的 **充分不必要条件**，如果通过了，我们还需要进一步判断线段的相交与否。
- **跨立实验**

  - 因为两线段a,b相交，b线段的两个端点一定分布在 a 线段所在直线两侧；同理，a线段的两个端点一定分布在 b 线段所在直线两侧。我们可以直接判断一条线段的两个端点相对于另一线段所在直线的位置关系，如果不同，则两线段相交，反之则不相交。如上一节所说，直线与点的位置关系我们可以利用向量积判断。
  - 这就是跨立实验，如果对于两线段a,b,b线段的两个端点分布在 a 线段所在直线的两侧，且a线段的两个端点分布在b线段所在直线的两侧，这种情况称为**通过跨立实验**，即两端线相交。

    - c++实现代码如下：
    - LineSegmentIntersectionpoint_line.h文件
    - ```c++
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
      ```
    - LineSegmentIntersectionpoint_line.cpp文件
    - ```c++
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
      ```

### 3.判断一个点是否在任意多边形内部

- #### 光线投射算法 (Ray casting algorithm)


  - 特殊情况判断，如“这个点离多边形太远了”一个能够完全覆盖该多边形的最小矩形，如果这个点不在这个矩形范围内，那么这个点一定不在多边形内。这样的矩形很好求，只需要知道多边形横坐标与纵坐标的最小值和最大值，坐标两两组合成四个点，就是这个矩形的四个顶点了。
  - 以该点为端点引出一条射线，如果这条射线与多边形有奇数个交点，则该点在多边形内部，否则该点在多边形外部，我们简记为 **奇内偶外**。这个算法同样被称为奇偶规则 (Even-odd rule)。
- #### 回转数算法 (Winding number algorithm)


  - 回转数是数学上的概念，是平面内闭合曲线逆时针绕过该点的总次数。很容易发现，当回转数等于 0 的时候，点在曲线外部。这个算法同样被称为非零规则 (Nonzero-rule)。如何计算呢？我们依次从多边形中取出边，用需要判断的点与边两点进行回转数的计算，与每条边计算后若回转数为0则点在多边形外，不为0则在多边形内。
- 算法实现：

  - pointInPplygon.h文件
  - ```c++
    #ifndef POINT_IN_POLYGON_H
    #define POINT_IN_POLYGON_H

    #include <vector>
    #include <iostream>

    namespace PointInPolygon {

    struct Point {
        double x;
        double y;
    };
    //光线投射算法
    bool isPointInPolygonRayCasting(const Point& pt, const std::vector<Point>& polygon);
    //回转数算法
    bool isPointInPolygonWindingNumber(const Point& pt, const std::vector<Point>& polygon);

    } // namespace PointInPolygon

    #endif // POINT_IN_POLYGON_H

    ```
  - pointInPplygonpoint_line.cpp文件
  - ```c++
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

    ```

### 4.求两直线的交点

- 首先，我们需要确定两条直线相交，只需判断一下两条直线的方向向量是否平行即可。如果方向向量平行，则两条直线平行，交点个数为 0。进一步地，若两条直线平行且过同一点，则两直线重合。如果两直线相交，则交点只有一个，根据直线方程直接列解就能求得两直线的交点。

  - 代码实现
  - findIntersection.h文件

    - ```c++
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
      ```
  - findIntersection.cpp文件
  - ```c++
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
    ```

### 5.计算任意多边形的周长和面积

周长，直接计算即可

面积，考虑向量积的模的几何意义，将多边形的点逆时针标记为 `p1,p2,p3,...,pn,`再选一辅助点 O（通常选为原点 (0,0)），记向量 `vi = pi - O`，然后利用向量积来计算面积。

公式推导，多边形的面积可以通过求出所有由辅助点和多边形的各条边组成的三角形的面积之和得到。每个三角形的面积可以通过向量积计算。

给定两个顶点 `pi 和 pi+1`，以及辅助点 O，三角形的面积为：

$$
Area_ i= 1/2 ∣ v_i × v_{i+1}∣
$$

对于整个多边形，面积可以表示为所有这些三角形面积的绝对值和：

$$
Area= 1/2∣∑_{i=1}(x_iy_{i+1}−y_ix_ {i+1})∣
$$

代码实现：

```c++
double polygonArea(const std::vector<Point>& vertices) {
    int n = vertices.size();
    if (n < 3) {
        return 0; // 不形成多边形
    }

    double area = 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n; // 下一个顶点
        area += vertices[i].x * vertices[j].y - vertices[i].y * vertices[j].x;
    }
  
    return std::fabs(area) / 2.0;
}
```

### 6.求直线与圆的交点

- 首先判断直线与圆的位置关系。如果直线与圆相离则无交点，若相切则可以利用切线求出切点与半径所在直线，之后转化为求两直线交点。
- 若有两交点，则可以利用勾股定理求出两交点的中点，然后沿直线方向加上半弦长即可。
- 代码实现如下：
- ```c++
  #include <iostream>
  #include <cmath>
  #include <vector>

  struct Point {
      double x, y;
  };

  struct Line {
      double a, b, c; // 直线方程 ax + by + c = 0
  };

  struct Circle {
      Point center;
      double radius;
  };

  // 求直线到点的距离
  double distanceFromPointToLine(const Point& p, const Line& line) {
      return std::fabs(line.a * p.x + line.b * p.y + line.c) / std::sqrt(line.a * line.a + line.b * line.b);
  }

  // 判断直线与圆的位置关系并求交点
  std::vector<Point> lineCircleIntersection(const Line& line, const Circle& circle) {
      double dist = distanceFromPointToLine(circle.center, line);
      std::vector<Point> intersectionPoints;

      if (dist > circle.radius) {
          // 相离
          return intersectionPoints;
      }

      // 求直线与圆的交点
      double a = line.a;
      double b = line.b;
      double c = line.c + a * circle.center.x + b * circle.center.y; // 将圆心平移到原点
      double r = circle.radius;

      if (dist == r) {
          // 相切
          double x0 = -a * c / (a * a + b * b);
          double y0 = -b * c / (a * a + b * b);
          intersectionPoints.push_back({ x0 + circle.center.x, y0 + circle.center.y });
      }
      else {
          // 相交，圆心与直线的垂足
          double x0 = -a * c / (a * a + b * b);
          double y0 = -b * c / (a * a + b * b);
          double d = r * r - c * c / (a * a + b * b);
          double mult = std::sqrt(d / (a * a + b * b));
          double ax = x0 + b * mult;
          double ay = y0 - a * mult;
          double bx = x0 - b * mult;
          double by = y0 + a * mult;
          intersectionPoints.push_back({ ax + circle.center.x, ay + circle.center.y });
          intersectionPoints.push_back({ bx + circle.center.x, by + circle.center.y });
      }

      return intersectionPoints;
  }
  ```

  ### 7.求两圆的交点

  - 首先我们判断一下两个圆的位置关系，如果外离或内含则无交点，如果相切，可以算出两圆心连线的方向向量，然后利用两圆半径计算出平移距离，最后将圆心沿这个方向向量进行平移即可。
  - 如果两圆相交，则必有两个交点，并且关于两圆心连线对称。因此下面只说明一个交点的求法，另一个交点可以用类似方法求出。
  - 我们先将一圆圆心与交点相连，求出两圆心连线与该连线所成角。这样，将两圆心连线的方向向量旋转这个角度，就是圆心与交点相连形成的半径的方向向量了。
  - 代码如下：
  - ```c++
    #include <iostream>
    #include <cmath>
    #include <vector>
    #include <utility>

    struct Point {
        double x, y;
    };

    struct Circle {
        Point center;
        double radius;
    };

    // 求两点之间的距离
    double distance(const Point& p1, const Point& p2) {
        return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }

    // 求两圆的交点
    std::pair<bool, std::vector<Point>> circleCircleIntersection(const Circle& c1, const Circle& c2) {
        double d = distance(c1.center, c2.center);
        if (d > c1.radius + c2.radius || d < std::fabs(c1.radius - c2.radius)) {
            // 相离或内含，无交点
            return {false, {}};
        }
        //有交点
        std::vector<Point> intersectionPoints;

        double a = (c1.radius * c1.radius - c2.radius * c2.radius + d * d) / (2 * d);//计算c1圆心到圆心连线与交点连线交点之间的距离
        double h = std::sqrt(c1.radius * c1.radius - a * a);//计算交点连线长度的一半

        Point p0;//两条交线的交点 p0
        p0.x = c1.center.x + a * (c2.center.x - c1.center.x) / d;
        p0.y = c1.center.y + a * (c2.center.y - c1.center.y) / d;

        if (d == c1.radius + c2.radius || d == std::fabs(c1.radius - c2.radius)) {
            // 相切，有一个交点
            intersectionPoints.push_back(p0);
        } else {
            // 相交，有两个交点
            Point p1, p2;
            p1.x = p0.x + h * (c2.center.y - c1.center.y) / d;
            p1.y = p0.y - h * (c2.center.x - c1.center.x) / d;

            p2.x = p0.x - h * (c2.center.y - c1.center.y) / d;
            p2.y = p0.y + h * (c2.center.x - c1.center.x) / d;

            intersectionPoints.push_back(p1);
            intersectionPoints.push_back(p2);
        }

        return {true, intersectionPoints};
    }
    ```
