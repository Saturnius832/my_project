#include <iostream>
#include <string>
#include <locale.h>
#include <vector>

#include "boyerMoore.h"

void printIndexes(const std::vector<int>& indexes)
{
    if (indexes.empty())
    {
        std::cout << "Нет вхождений" << std::endl;
        return;
    }

    for (int index : indexes)
    {
        std::cout << index << ' ';
    }

    std::cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    std::string text;
    std::string pattern;
    std::cout << "Введите текст: ";
    std::getline(std::cin, text);

    std::cout << "Введите подстроку: ";
    std::getline(std::cin, pattern);
    std::vector<int> rangeIndexes =
        findAllOccurrences(text, pattern, 28, 36);

    std::cout << "Все вхождения в диапазоне: ";
    printIndexes(rangeIndexes);


    int firstIndex = findFirstOccurrence(text, pattern);

    std::cout << "Первое вхождение: "
        << firstIndex << std::endl;
   

    std::vector<int> indexes = findAllOccurrences(text, pattern);


    std::cout << "Все вхождения: ";
    printIndexes(indexes);


    return 0;
}