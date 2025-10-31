#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

struct Circle {
    Point c;
    double r;
    Circle() : c(Point(0, 0)), r(0) {}
    Circle(Point c, double r) : c(c), r(r) {}
};

// 计算两点之间的距离
double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// 判断点p是否在圆c内或圆上
bool is_inside(const Circle& c, const Point& p) {
    return dist(c.c, p) <= c.r;
}

// 求两点确定的圆
Circle circle_from_two(const Point& a, const Point& b) {
    Point c((a.x + b.x) / 2.0, (a.y + b.y) / 2.0);
    double r = dist(a, b) / 2.0;
    return Circle(c, r);
}
 
// 求三点确定的圆（外接圆）
Circle circle_from_three(const Point& a, const Point& b, const Point& c) {
    double A = b.x - a.x;
    double B = b.y - a.y;
    double C = c.x - a.x;
    double D = c.y - a.y;
    double E = A * (a.x + b.x) + B * (a.y + b.y);
    double F = C * (a.x + c.x) + D * (a.y + c.y);
    double G = 2 * (A * (c.y - b.y) - B * (c.x - b.x));//方程组行列式的一半 2（AD-BC）

    if (fabs(G) ==0) { // 三点共线，返回两点确定的最大圆
        double d1 = dist(a, b);
        double d2 = dist(b, c);
        double d3 = dist(a, c);
        if (d1 >= d2 && d1 >= d3) return circle_from_two(a, b);
        else if (d2 >= d1 && d2 >= d3) return circle_from_two(b, c);
        else return circle_from_two(a, c);
    }

    //克莱姆法则
    double cx = (D * E - B * F) / G;
    double cy = (A * F - C * E) / G;
    Point center(cx, cy);
    double r = dist(center, a);
    return Circle(center, r);
}

// 递归求解最小覆盖圆
Circle welzl_helper(vector<Point>& P, vector<Point> R, int n) {
    //递归终止条件
    if (n == 0 || R.size() == 3) {
        if (R.empty()) {
            return Circle(Point(0, 0), 0);
        }
        else if (R.size() == 1) {
            return Circle(R[0], 0);
        }
        else if (R.size() == 2) {
            return circle_from_two(R[0], R[1]);
        }
        else {
            return circle_from_three(R[0], R[1], R[2]);
        }
    }

    //递归调用

    // 递归求解 “不含 p” 的子问题
    Circle D = welzl_helper(P, R, n - 1);
	Point p = P[n - 1];
    //每一层递归调用有两种返回值的情况，同一递归函数在不同条件下返回 “符合当前约束的解”
    //当点在圆内时，上一层递归的结果已经满足当前问题的需求
    if (is_inside(D, p)) {
        return D;
    }

    // 当点不在圆内时，需要基于新约束（加入该点到边界集）重新计算解并返回
    R.push_back(p);
    return welzl_helper(P, R, n - 1);

    //总结：每一层递归在回溯时，会根据 “当前点是否在子问题的圆内” 来决定是否接受子问题的结果，
    // 还是基于新约束重新计算结果。这本质上是一种 “验证 - 调整” 的回溯逻辑。
}

// 计算最小覆盖圆
Circle minimal_enclosing_circle(vector<Point> P) {
    srand(time(0));
    random_shuffle(P.begin(), P.end());
    return welzl_helper(P, vector<Point>(), P.size());
}

int main() {
    int n;
    cin >> n;
    vector<Point> points;
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    Circle c = minimal_enclosing_circle(points);

    cout << fixed << setprecision(3);
    cout << c.c.x << " " << c.c.y << endl;
    cout << c.r << endl;

    return 0;
}