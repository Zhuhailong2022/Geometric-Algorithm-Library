#include "ScaningLineAlgorythm.h"



// 比较事件的 x 坐标，按从小到大排序
bool compareEvents(const Event &a, const Event &b) {
    return a.x < b.x;
}
SegmentTree::SegmentTree(const std::vector<int>& coordinates) {
    yCoordinates = coordinates;
    tree.resize(yCoordinates.size() * 4); // 初始化线段树节点数量
    build(0, 0, yCoordinates.size() - 1); // 构建线段树
}

void SegmentTree::build(int node, int start, int end) {
    tree[node].left = start;
    tree[node].right = end;
    tree[node].count = 0;
    tree[node].length = 0;

    if (start < end) {
        int mid = (start + end) / 2;
        build(node * 2 + 1, start, mid);       // 构建左子树
        build(node * 2 + 2, mid + 1, end);     // 构建右子树
    }
}

void SegmentTree::update(int node, int start, int end, int value) {
    if (tree[node].left > end || tree[node].right < start) return; // 如果节点范围与更新范围无交集

    if (start <= tree[node].left && tree[node].right <= end) {
        tree[node].count += value; // 更新当前节点的覆盖计数
    } else {
        update(node * 2 + 1, start, end, value); // 更新左子树
        update(node * 2 + 2, start, end, value); // 更新右子树
    }

    if (tree[node].count > 0) {
        // 如果当前节点被覆盖，计算被覆盖的长度
        tree[node].length = getCoordinate(tree[node].right + 1) - getCoordinate(tree[node].left);
    } else if (tree[node].left == tree[node].right) {
        tree[node].length = 0; // 如果节点是叶子节点且未被覆盖，长度为0
    } else {
        // 否则，节点的长度为左右子树的长度之和
        tree[node].length = tree[node * 2 + 1].length + tree[node * 2 + 2].length;
    }
}

int SegmentTree::getLength() {
    return tree[0].length; // 返回根节点的长度
}

int SegmentTree::getCoordinate(int index) {
    if (index >= 0 && index < yCoordinates.size()) {
        return yCoordinates[index]; // 返回离散化后的 y 坐标
    }
    return 0;
}


// 计算矩形覆盖的总面积
int calculateArea(const std::vector<Rectangle> &rectangles) {
    std::vector<Event> events;
    std::set<int> yCoordinateSet;

    // 为每个矩形创建进入和离开事件，并收集 y 坐标
    for (const auto &rect : rectangles) {
        events.push_back({rect.x1, rect.y1, rect.y2, 1});
        events.push_back({rect.x2, rect.y1, rect.y2, -1});
        yCoordinateSet.insert(rect.y1);
        yCoordinateSet.insert(rect.y2);
    }

    // 按 x 坐标对事件进行排序
    std::sort(events.begin(), events.end(), compareEvents);

    // 将 y 坐标从 set 转换为 vector
    std::vector<int> yCoordinates(yCoordinateSet.begin(), yCoordinateSet.end());

    SegmentTree segmentTree(yCoordinates);
    int prevX = events.front().x; // 上一个 x 坐标
    int area = 0;

    // 遍历所有事件
    for (const auto &event : events) {
        int currX = event.x; // 当前事件的 x 坐标
        area += segmentTree.getLength() * (currX - prevX); // 计算被覆盖的面积
        // 更新线段树，记录当前 y 坐标范围的覆盖情况
        segmentTree.update(0, 
                           std::lower_bound(yCoordinates.begin(), yCoordinates.end(), event.y1) - yCoordinates.begin(), 
                           std::lower_bound(yCoordinates.begin(), yCoordinates.end(), event.y2) - yCoordinates.begin() - 1, 
                           event.type);
        prevX = currX; // 更新上一个 x 坐标
    }

    return area; // 返回总面积
}