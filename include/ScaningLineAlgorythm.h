#ifndef SCANING_LINE_ALGORITHM_H
#define SCANING_LINE_ALGORITHM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

// 定义点结构
struct Point {
    int x, y;
};

// 定义矩形结构
struct Rectangle {
    int x1, y1, x2, y2;
};

// 定义事件结构，竖线与矩形相交时覆盖范围相关信息
struct Event {
    int x, y1, y2, type;
};

// 比较事件的 x 坐标，按从小到大排序
bool compareEvents(const Event &a, const Event &b);

// 定义线段树的节点结构
struct Node {
    int left, right; // 左右边界
    int count;       // 被覆盖的次数
    int length;      // 被覆盖的长度

    Node() : left(0), right(0), count(0), length(0) {}
};

// 线段树类
class SegmentTree {
private:
    std::vector<Node> tree;
    std::vector<int> yCoordinates;  // 存储离散化后的 y 坐标，存储矩形上每个点的 y 坐标

public:
    SegmentTree(const std::vector<int>& coordinates);

    void build(int node, int start, int end);

    void update(int node, int start, int end, int value);

    int getLength();

private:
    int getCoordinate(int index);
};

// 计算矩形覆盖的总面积
int calculateArea(const std::vector<Rectangle> &rectangles);

#endif // SCANNING_LINE_ALGORITHM_H