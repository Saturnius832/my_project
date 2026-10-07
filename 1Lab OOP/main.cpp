#include "Point.h"

#include <iostream>

int main()
{
    Point point1(3, 4, 5);
    Point point2(-3, -4, -5);

    std::cout << "Point 1: ";
    point1.output();

    std::cout << "\nPoint 2: ";
    point2.output();
    std::cout << "\n\n";

    std::cout << "X: " << point1.getX() << "\n";
    std::cout << "Y: " << point1.getY() << "\n";
    std::cout << "Z: " << point1.getZ() << "\n";

    std::cout << "\n";

    std::cout << "Point 1 is on Ox: "
        << point1.isOnOx() << "\n";

    std::cout << "Point 1 is on Oy: "
        << point1.isOnOy() << "\n";

    std::cout << "Point 1 is on Oz: "
        << point1.isOnOz() << "\n";

    std::cout << "Point 1 octant: "
        << point1.getOctant() << "\n";

    std::cout << "Symmetric to origin: "
        << point1.isSymmetricToOrigin(point2) << "\n";
    Point point3(4, 4, -5);
    Point point4(3, -4, 5);
    Point point5(-3, 4, 5);

    std::cout << "Symmetric to XOY: "
        << point1.isSymmetricToXOY(point3) << "\n";

    std::cout << "Symmetric to XOZ: "
        << point1.isSymmetricToXOZ(point4) << "\n";

    std::cout << "Symmetric to YOZ: "
        << point1.isSymmetricToYOZ(point5) << "\n";

    std::cout << "Distance from origin: "
        << point1.getDistanceFromOrigin() << "\n";

    Point point6(3, 4, 5);

    std::cout << "\n";

    std::cout << "Point 1 == Point 6: "
        << (point1 == point6) << "\n";

    Point point7 = point1 * 2;

    std::cout << "Point 1 * 2: ";
    point7.output();

    std::cout << "\n";

    std::cout << "Distance to Ox: "
        << point1.getDistanceToOx() << "\n";

    std::cout << "Distance to Oy: "
        << point1.getDistanceToOy() << "\n";

    std::cout << "Distance to Oz: "
        << point1.getDistanceToOz() << "\n";

    return 0;
}