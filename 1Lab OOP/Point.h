#ifndef POINT_H
#define POINT_H

class Point
{
public: //открытая часть класса
    Point();
    Point(double x, double y, double z);

    void input(); //ввод координат
    void output() const;

    double getX() const;
    double getY() const;
    double getZ() const;
    
    //Проверить, находится ли точка на Ox,Oy,Oz
    bool isOnOx() const;
    bool isOnOy() const;
    bool isOnOz() const;
    int getOctant() const;

    bool isSymmetricToOrigin(const Point& point) const;

    bool isSymmetricToXOY(const Point& point) const;
    bool isSymmetricToXOZ(const Point& point) const;
    bool isSymmetricToYOZ(const Point& point) const;

    double getDistanceFromOrigin() const; //получить расстояние до начала координат

    bool operator==(const Point& point) const;
    Point operator*(double number) const;

    //РАССТОЯНИЕ ДО Ox,Oy,Oz
    double getDistanceToOx() const;
    double getDistanceToOy() const;
    double getDistanceToOz() const;

private: //закрытая часть класса
    double x_;
    double y_;
    double z_;
};

#endif