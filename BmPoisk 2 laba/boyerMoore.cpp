#include "boyerMoore.h"

std::vector<int> makeShiftTable(const std::string& pattern)
{
    int m = static_cast<int>(pattern.length());
    std::vector<int> table(256, m);

    for (int i = 0; i < m - 1; ++i)
        table[static_cast<unsigned char>(pattern[i])] = m - 1 - i;


    return table;
}

int findFirstOccurrence(const std::string& text,
    const std::string& pattern)
{
    int n = static_cast<int>(text.length());
    int m = static_cast<int>(pattern.length());

    if (pattern.empty())
        return 0;


    if (m > n)
        return -1;


    std::vector<int> table = makeShiftTable(pattern);

    int i = m - 1;

    while (i < n)
    {
        int j = m - 1;
        int k = i;

        while (j >= 0 && text[k] == pattern[j])
        {
            --j;
            --k;
        }

        if (j < 0)      
            return k + 1;
        

        int shift = table[static_cast<unsigned char>(text[i])];

        if (shift == 0)      
            shift = 1;
        

        i += shift;
    }

    return -1;
}

std::vector<int> findAllOccurrences(const std::string& text,
    const std::string& pattern)
{
    std::vector<int> result;

    int n = static_cast<int>(text.length());
    int m = static_cast<int>(pattern.length());

    if (pattern.empty() || m > n)
        return result;


    std::vector<int> table = makeShiftTable(pattern);

    int i = m - 1;

    while (i < n)
    {
        int j = m - 1;
        int k = i;

        while (j >= 0 && text[k] == pattern[j])
        {
            --j;
            --k;
        }

        if (j < 0)
        {
            result.push_back(k + 1);

            // Сдвигаемся на один символ,
            // чтобы не пропустить пересекающиеся вхождения.
            ++i;
        }
        else
        {
            int shift = table[static_cast<unsigned char>(text[i])];

            if (shift == 0)           
                shift = 1;
           

            i += shift;
        }
    }

    return result;
}
