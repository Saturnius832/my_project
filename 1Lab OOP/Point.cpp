#include "Point.h"

#include <cmath>
#include <iostream>

Point::Point()
    : x_(0), y_(0), z_(0)
{
}

Point::Point(double x, double y, double z)
    : x_(x), y_(y), z_(z)
{
}

void Point::input()
{
    std::cin >> x_ >> y_ >> z_;
}

void Point::output() const
{
    std::cout << "(" << x_ << ", "
        << y_ << ", " << z_ << ")";
}

double Point::getX() const
{
    return x_;
}

double Point::getY() const
{
    return y_;
}

double Point::getZ() const
{
    return z_;
}

bool Point::isOnOx() const
{
    return y_ == 0 && z_ == 0;
}

bool Point::isOnOy() const
{
    return x_ == 0 && z_ == 0;
}

bool Point::isOnOz() const
{
    return x_ == 0 && y_ == 0;
}

int Point::getOctant() const
{
    if (x_ > 0 && y_ > 0 && z_ > 0)
        return 1;

    if (x_ < 0 && y_ > 0 && z_ > 0)
        return 2;

    if (x_ < 0 && y_ < 0 && z_ > 0)
        return 3;

    if (x_ > 0 && y_ < 0 && z_ > 0)
        return 4;

    if (x_ > 0 && y_ > 0 && z_ < 0)
        return 5;

    if (x_ < 0 && y_ > 0 && z_ < 0)
        return 6;

    if (x_ < 0 && y_ < 0 && z_ < 0)
        return 7;

    if (x_ > 0 && y_ < 0 && z_ < 0)
        return 8;

    return 0;
}

bool Point::isSymmetricToOrigin(const Point& point) const
{ 
    return x_ == -point.x_ &&
        y_ == -point.y_ &&
        z_ == -point.z_;
}

bool Point::isSymmetricToXOY(const Point& point) const
{
    return x_ == point.x_ &&
        y_ == point.y_ &&
        z_ == -point.z_;
}

bool Point::isSymmetricToXOZ(const Point& point) const
{
    return x_ == point.x_ &&
        y_ == -point.y_ &&
        z_ == point.z_;
}

bool Point::isSymmetricToYOZ(const Point& point) const
{
    return x_ == -point.x_ &&
        y_ == point.y_ &&
        z_ == point.z_;
}

double Point::getDistanceFromOrigin() const
{
    return std::sqrt((x_ * x_) + (y_ * y_) + (z_ * z_)); //базовая формула: корень x^2 + y^2 + z^2
}

bool Point::operator==(const Point& point) const // определеяем как, две точки сравнивать
{
    return x_ == point.x_ &&
        y_ == point.y_ &&
        z_ == point.z_;
}

Point Point::operator*(double number) const //опр умножение точки на число
{
    return Point(x_ * number,
        y_ * number,
        z_ * number);
}

double Point::getDistanceToOx() const
{
    return std::sqrt(y_ * y_ + z_ * z_);
}

double Point::getDistanceToOy() const
{
    return std::sqrt(x_ * x_ + z_ * z_);
}

double Point::getDistanceToOz() const
{
    return std::sqrt(x_ * x_ + y_ * y_);
} 

bool Point::formsTriangle(const Point& point2, const Point& point3) const //возвращает true(1) если треугольник сущ. , false(0) если не сущ.
{    
    //нахождение разницы координат
    double ax = point2.x_ - x_;
    double ay = point2.y_ - y_;
    double az = point2.z_ - z_;

    double bx = point3.x_ - x_;
    double by = point3.y_ - y_;
    double bz = point3.z_ - z_;

    double cx = ay * bz - az * by;
    double cy = az * bx - ax * bz;
    double cz = ax * by - ay * bx;

    return cx * cx + cy * cy + cz * cz > 0;
}

double Point::getTriangleArea(const Point& point2, const Point& point3) const //вычисление площади
{
    double ax = point2.x_ - x_;
    double ay = point2.y_ - y_;
    double az = point2.z_ - z_;

    double bx = point3.x_ - x_;
    double by = point3.y_ - y_;
    double bz = point3.z_ - z_;

    double cx = ay * bz - az * by;
    double cy = az * bx - ax * bz;
    double cz = ax * by - ay * bx;

    return 0.5 * std::sqrt(cx * cx + cy * cy + cz * cz);
}
