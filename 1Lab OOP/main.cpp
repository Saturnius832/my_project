
#include "Point.h"
#include <iostream>
#include<locale.h>

int main()
{
    setlocale(LC_ALL, "Rus");
    Point point1(3, 4, 5);
    Point point2(-3, -4, -5);
 
    std::cout << "Точка 1: ";
    point1.output();
    std::cout << "\nТочка 2: ";
    point2.output();
    std::cout << "\n\n";

    std::cout << "Координата X: " << point1.getX() << "\n";
    std::cout << "Координата Y: " << point1.getY() << "\n";
    std::cout << "Координата Z: " << point1.getZ() << "\n";

    std::cout << "\n";

    std::cout << "Точка 1 лежит на оси Ox: "
        << point1.isOnOx() << "\n";

    std::cout << "Точка 1 лежит на оси Oy: "
        << point1.isOnOy() << "\n";

    std::cout << "Точка 1 лежит на оси Oz: "
        << point1.isOnOz() << "\n";

    std::cout << "Октант точки 1: "
        << point1.getOctant() << "\n";

    std::cout << "Точки симметричны относительно начала координат: "
        << point1.isSymmetricToOrigin(point2) << "\n";

    Point point3(4, 4, -5);
    Point point4(3, -4, 5);
    Point point5(-3, 4, 5);

    std::cout << "Точки симметричны относительно плоскости XOY: "
        << point1.isSymmetricToXOY(point3) << "\n";

    std::cout << "Точки симметричны относительно плоскости XOZ: "
        << point1.isSymmetricToXOZ(point4) << "\n";

    std::cout << "Точки симметричны относительно плоскости YOZ: "
        << point1.isSymmetricToYOZ(point5) << "\n";

    std::cout << "\nРасстояние от точки 1 до начала координат: "
        << point1.getDistanceFromOrigin() << "\n";

    Point point6(3, 4, 5);

    std::cout << "\n";

    std::cout << "Точка 1 равна точке 6: "
        << (point1 == point6) << "\n";

    Point point7 = point1 * 2;

    std::cout << "Умножение координат точки 1 на 2: ";
    point7.output();

    std::cout << "\n\n";

    std::cout << "Расстояние от точки 1 до оси Ox: "
        << point1.getDistanceToOx() << "\n";

    std::cout << "Расстояние от точки 1 до оси Oy: "
        << point1.getDistanceToOy() << "\n";

    std::cout << "Расстояние от точки 1 до оси Oz: "
        << point1.getDistanceToOz() << "\n";

    Point a(0, 0, 0);
    Point b(4, 0, 0);
    Point c(0, 3, 0);

    std::cout << "\nТочки образуют треугольник: "
        << a.formsTriangle(b, c) << "\n";

    std::cout << "Площадь треугольника: "
        << a.getTriangleArea(b, c) << "\n";
    std::cout << "\n(1 - истинно, 0 - ложь)  \n";

    return 0;
}
