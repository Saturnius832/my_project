#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#include <string>
#include <vector>

std::vector<int> makeShiftTable(const std::string& pattern);

int findFirstOccurrence(const std::string& text,
	const std::string& pattern);

std::vector<int> findAllOccurrences(const std::string& text,
	const std::string& pattern);

#endif