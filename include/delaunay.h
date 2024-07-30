#ifndef DELAUNAY_H
#define DELAUNAY_H

#include <vector>
#include <list>

struct Point {
    double x, y;
    int id;
    Point(double a = 0, double b = 0, int c = -1) : x(a), y(b), id(c) {}

    double dist2(const Point& p) const {
        double dx = x - p.x;
        double dy = y - p.y;
        return dx * dx + dy * dy;
    }
};

class Delaunay {
public:
    void init(int n, Point p[]);
    std::vector<std::pair<int, int>> getEdge() const;

private:
    std::vector<std::list<int>> head;  // 图
    std::vector<Point> p;  // 点
    int n;
    std::vector<int> rename;

    static int intersection(const Point &a, const Point &b, const Point &c, const Point &d);
    void addEdge(int u, int v);
    void divide(int l, int r);
    static double cross(const Point &o, const Point &a, const Point &b);
    static int inCircle(const Point &a, Point b, Point c, const Point &p);
};

#endif // DELAUNAY_H
