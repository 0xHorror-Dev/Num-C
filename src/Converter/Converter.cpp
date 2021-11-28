#include"Converter.h"

int Converter::CharToInt(char c){
	if (c >= '0' && c <= '9' && (c - '0') < m_orig) {
		return c - '0';
	}
	else {
		if (c >= 'A' && c <= 'Z' && (c - 'A') < m_orig) {
			return c - 'A' + 10;
		}
		else {
			return -1;
		}
	}
}

char Converter::intToChar(int c){
	if (c >= 0 && c <= 9) {
		return c + '0';
	}
	else {
		return c + 'A' - 10;
	}
}

int Converter::NextNumber(int Final){
	int temp = 0;
	for (int i = 0; i < m_Num.size(); i++) {
		temp = temp * m_orig + m_Num[i];
		m_Num[i] = temp / Final;
		temp = temp % Final;
	}
	return temp;
}

bool Converter::Zero(){
	for (int i = 0; i < m_Num.size(); i++) {
		if (m_Num[i] != 0) {
			return false;
		}
	}
	return true;
}

void Converter::SetNumber(const std::string& str, int orig){
	m_orig = orig;

	for (int i = 0; i < str.length(); i++) {
		this->m_Num.push_back(CharToInt(str[i]));
	}
}

std::string Converter::ConvertTo(int NumSys){
	std::vector<int> b;
	int size = 0;
	do {
		b.push_back(NextNumber(NumSys));
		size++;
	} while (!Zero());

	std::string sTemp = "";
	for (int i = b.size() - 1; i >= 0; i--) {
		sTemp += intToChar(b[i]);
	}
	return sTemp;
}
