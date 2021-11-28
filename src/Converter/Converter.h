#ifndef _NUM_C_CONVERTER_H
#define _NUM_C_CONVERTER_H

#include <string>
#include <vector>

class Converter {

	std::vector<int> m_Num;
	int m_orig;

	int CharToInt(char c);
	char intToChar(int c);

	int NextNumber(int Final);

	bool Zero();
public:

	void SetNumber(const std::string& str, int orig);

	std::string ConvertTo(int NumSys);

};

#endif