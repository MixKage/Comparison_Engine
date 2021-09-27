#include "VariabilityName.h"

VariabilityName::VariabilityName(std::string input){
	VariabilityNameEng(input);
}

void VariabilityName::VariabilityNameEng(std::string input) {
	std::string firstName;
	std::string name;
	std::string lastName;
	int space = 0;
	for (char a : input) {
		if (a == '�')
			a = '�';
		else
			a = toupper(a);
		if (a == ' ') {
			space++;
			continue;
		}
		switch (space)
		{
		case (0):
			firstName += a;
			break;
		case (1):
			name += a;
			break;
		case (2):
			lastName += a;
			break;
		}
	}

	std::string firstName_t = Translit(firstName);
	std::string name_t = Translit(name);
	std::string lastName_t = Translit(lastName);

	_FIO = firstName + " " + name + " " + lastName;
	_IFO = name + " " + firstName + " " + lastName;
	_IOF = name + " " + lastName + " " + firstName;
	_FI = firstName + " " + name;
	_IF = name + " " + firstName;

	_FIO_t = firstName_t + " " + name_t + " " + lastName_t;
	_IFO_t = name_t + " " + firstName_t + " " + lastName_t;
	_IOF_t = name_t + " " + lastName_t + " " + firstName_t;
	_FI_t = firstName_t + " " + name_t;
	_IF_t = name_t + " " + firstName_t;
}

std::string VariabilityName::Translit(std::string input) {
	std::string output;
	for (char a : input)
		output += TranslitLetter(a);
	return output;
}

std::string VariabilityName::TranslitLetter(char input) {
	switch (input) {
	case '�': return "A";
	case '�': return "B";
	case '�': return "V";
	case '�': return "G";
	case '�': return "D";
	case '�': return "E";
	case '�': return "JE";
	case '�': return "ZH";
	case '�': return "Z";
	case '�': return "I";
	case '�': return "Y";
	case '�': return "K";
	case '�': return "L";
	case '�': return "M";
	case '�': return "N";
	case '�': return "O";
	case '�': return "P";
	case '�': return "R";
	case '�': return "S";
	case '�': return "T";
	case '�': return "U";
	case '�': return "F";
	case '�': return "KH";
	case '�': return "C";
	case '�': return "CH";
	case '�': return "SH";
	case '�': return "JSH";
	case '�': return "HH";
	case '�': return "IH";
	case '�': return "JH";
	case '�': return "EH";
	case '�': return "JU";
	case '�': return "JA";
	default: return std::to_string(input);
	};
}

std::string VariabilityName::GetFIO()
{
	return _FIO;
}

std::string VariabilityName::GetIFO()
{
	return _IFO;
}

std::string VariabilityName::GetIOF()
{
	return _IOF;
}

std::string VariabilityName::GetFI()
{
	return _FI;
}

std::string VariabilityName::GetIF()
{
	return _IF;
}

std::string VariabilityName::GetFIO_t()
{
	return _FIO_t;
}

std::string VariabilityName::GetIFO_t()
{
	return _IFO_t;
}

std::string VariabilityName::GetIOF_t()
{
	return _IOF_t;
}

std::string VariabilityName::GetFI_t()
{
	return _FI_t;
}

std::string VariabilityName::GetIF_t()
{
	return _IF_t;
}

bool VariabilityName::isVarName()
{
	std::string firstName;
	std::string name;
	std::string lastName;
	int space = 0;
	for (char a : _FIO) {
		if (a == ' ') {
			space++;
			continue;
		}
		switch (space)
		{
		case (0):
			firstName += a;
			break;
		case (1):
			name += a;
			break;
		case (2):
			lastName += a;
			break;
		}
	}
	try {
		if (!varNames[name].empty()) {
			name = varNames[name];
			std::string str = firstName + " " + name + " " + lastName;
			VariabilityNameEng(str);
			return true;
		}
	}
	catch (const std::exception& e) {
		return false;
	}
	return false;
}
