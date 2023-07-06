#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
/*
 * 此示例是为了熟悉如何组织一个更好的类
 *
 *
 */
// 表示一个二维点的类
class Point
{
public:
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}

    // 获取x和y的值
    double getX() const { return x; }
    double getY() const { return y; }

private:
    double x;
    double y;
};

// 表示一条线段的类
class Line
{
public:
    Line(const Point &start, const Point &end) : start(start), end(end) {}

    // 获取起点和终点的值
    const Point &getStart() const { return start; }
    const Point &getEnd() const { return end; }

private:
    Point start;
    Point end;
};

// 表示一个形状的类，包含多个线段
class Shape
{
public:
    Shape() {}

    // 添加线段到形状中
    void addLine(const Line &line)
    {
        lines.push_back(line);
    }

    // 计算形状的周长
    double calculatePerimeter() const
    {
        double perimeter = 0;
        for (const auto &line : lines)
        {
            double deltaX = line.getStart().getX() - line.getEnd().getX();
            double deltaY = line.getStart().getY() - line.getEnd().getY();
            perimeter += std::sqrt(deltaX * deltaX + deltaY * deltaY);
        }
        return perimeter;
    }

private:
    std::vector<Line> lines;
};

int main()
{
    Point p1(0, 0);
    Point p2(3, 0);
    Point p3(3, 4);

    Line l1(p1, p2);
    Line l2(p2, p3);
    Line l3(p3, p1);

    Shape triangle;
    triangle.addLine(l1);
    triangle.addLine(l2);
    triangle.addLine(l3);

    std::cout << "Triangle perimeter: " << triangle.calculatePerimeter() << std::endl;

    return 0;
}