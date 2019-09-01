#include "pch.h"

/*unsigned convertXAndYToIndex(const unsigned x, const unsigned y)
{
	return 3 * y + x;
}*/

int stringToInt(const std::string a) 
{
	return atoi(a.c_str());
}

bool stringToBool(const std::string s)
{
	return s.at(0) == '1';
}

float stringToFloat(const std::string a)
{
	float b;
	std::stringstream ss;

	ss << a;
	ss >> b;

	return b;
}

short stringToShort(const std::string s)
{
	short newShort;
	std::stringstream ss;

	ss << s;
	ss >> newShort;

	return newShort;
}

int size_tToInt(size_t a)
{
	if (a > INT_MAX)
	{
		throw std::overflow_error("data is larger than INT_MAX");
	}
	int converta = static_cast<int>(a);
	return converta;
}
