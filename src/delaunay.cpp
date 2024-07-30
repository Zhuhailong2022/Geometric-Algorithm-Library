#include "delaunay.h"
#include <algorithm>
#include <cmath>

const double EPS = 1e-8;

struct Point3D {
    double x, y, z;
    Point3D(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c) {}
    Point3D(const Point& p) : x(p.x), y(p.y), z(p.x * p.x + p.y * p.y) {}
    Point3D operator-(const Point3D& p) const { return Point3D(x - p.x, y - p.y, z - p.z); }
    double dot(const Point3D& p) const { return x * p.x + y * p.y + z * p.z; }

    static Point3D cross(const Point3D& a, const Point3D& b) {
        return Point3D(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }
};

double Delaunay::cross(const Point& o, const Point& a, const Point& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

inline int cmp(double x) {
    if (std::fabs(x) < EPS) return 0;
    else return x < 0 ? -1 : 1;
}

int Delaunay::intersection(const Point &a, const Point &b, const Point &c, const Point &d) {
    return cmp(cross(a, c, b)) * cmp(cross(a, b, d)) > 0 &&
           cmp(cross(c, a, d)) * cmp(cross(c, d, b)) > 0;
}

int Delaunay::inCircle(const Point &a, Point b, Point c, const Point &p) {
    if (cross(a, b, c) < 0) std::swap(b, c);
    Point3D a3(a), b3(b), c3(c), p3(p);
    b3 = b3 - a3, c3 = c3 - a3, p3 = p3 - a3;
    Point3D f = Point3D::cross(b3, c3);
    return cmp(p3.dot(f));  // check same direction, in: < 0, on: = 0, out: > 0
}

void Delaunay::init(int n, Point p[]) {
    this->n = n;
    this->p.assign(p, p + n);
    std::sort(this->p.begin(), this->p.end(), [](const Point& a, const Point& b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    rename.resize(n);
    for (int i = 0; i < n; i++) rename[this->p[i].id] = i;
    head.resize(n);
    divide(0, n - 1);
}

std::vector<std::pair<int, int>> Delaunay::getEdge() const {
    std::vector<std::pair<int, int>> ret;
    for (int i = 0; i < n; i++) {
        for (const auto& e : head[i]) {
            if (e < i) continue;
            ret.push_back(std::make_pair(p[i].id, p[e].id));
        }
    }
    return ret;
}

void Delaunay::addEdge(int u, int v) {
    head[u].push_front(v);
    head[v].push_front(u);
}

void Delaunay::divide(int l, int r) {
    if (r - l <= 2) {  // #point <= 3
        for (int i = l; i <= r; i++)
            for (int j = i + 1; j <= r; j++) addEdge(i, j);
        return;
    }
    int mid = (l + r) / 2;
    divide(l, mid);
    divide(mid + 1, r);

    // Find and update convex hull
    int nowl = l, nowr = r;
    for (int update = 1; update;) {
        update = 0;
        Point ptL = p[nowl], ptR = p[nowr];
        for (auto it = head[nowl].begin(); it != head[nowl].end(); it++) {
            Point t = p[*it];
            double v = cross(ptR, ptL, t);
            if (cmp(v) > 0 || (cmp(v) == 0 && ptR.dist2(t) < ptR.dist2(ptL))) {
                nowl = *it, update = 1;
                break;
            }
        }
        if (update) continue;
        for (auto it = head[nowr].begin(); it != head[nowr].end(); it++) {
            Point t = p[*it];
            double v = cross(ptL, ptR, t);
            if (cmp(v) < 0 || (cmp(v) == 0 && ptL.dist2(t) < ptL.dist2(ptR))) {
                nowr = *it, update = 1;
                break;
            }
        }
    }

    addEdge(nowl, nowr);  // add tangent

    for (int update = 1; true;) {
        update = 0;
        Point ptL = p[nowl], ptR = p[nowr];
        int ch = -1, side = 0;
        for (auto it = head[nowl].begin(); it != head[nowl].end(); it++) {
            if (cmp(cross(ptL, ptR, p[*it])) > 0 &&
                (ch == -1 || inCircle(ptL, ptR, p[ch], p[*it]) < 0)) {
                ch = *it, side = -1;
            }
        }
        for (auto it = head[nowr].begin(); it != head[nowr].end(); it++) {
            if (cmp(cross(ptR, p[*it], ptL)) > 0 &&
                (ch == -1 || inCircle(ptL, ptR, p[ch], p[*it]) < 0)) {
                ch = *it, side = 1;
            }
        }
        if (ch == -1) break;  // upper common tangent
        if (side == -1) {
            for (auto it = head[nowl].begin(); it != head[nowl].end();) {
                if (intersection(ptL, p[*it], ptR, p[ch])) {
                    auto toErase = it++;
                    head[*toErase].remove(nowl);
                    head[nowl].erase(toErase);
                } else {
                    ++it;
                }
            }
            nowl = ch;
            addEdge(nowl, nowr);
        } else {
            for (auto it = head[nowr].begin(); it != head[nowr].end();) {
                if (intersection(ptR, p[*it], ptL, p[ch])) {
                    auto toErase = it++;
                    head[*toErase].remove(nowr);
                    head[nowr].erase(toErase);
                } else {
                    ++it;
                }
            }
            nowr = ch;
            addEdge(nowl, nowr);
        }
    }
}
