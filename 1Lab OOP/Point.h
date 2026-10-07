#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point();
    Point(double x, double y, double z);

    void input();
    void output() const;

    double getX() const;
    double getY() const;
    double getZ() const;

    bool isOnOx() const;
    bool isOnOy() const;
    bool isOnOz() const;

    int getOctant() const;

    bool isSymmetricToOrigin(const Point& point) const;

    bool isSymmetricToXOY(const Point& point) const;
    bool isSymmetricToXOZ(const Point& point) const;
    bool isSymmetricToYOZ(const Point& point) const;

    double getDistanceFromOrigin() const;

    bool operator==(const Point& point) const;
    Point operator*(double number) const;

    double getDistanceToOx() const;
    double getDistanceToOy() const;
    double getDistanceToOz() const;

private:
    double x_;
    double y_;
    double z_;
};

#endif