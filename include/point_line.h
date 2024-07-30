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
