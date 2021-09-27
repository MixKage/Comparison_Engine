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
		if (a == 'ÿ')
			a = 'ß';
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
	case 'À': return "A";
	case 'Á': return "B";
	case 'Â': return "V";
	case 'Ã': return "G";
	case 'Ä': return "D";
	case 'Å': return "E";
	case '¨': return "JE";
	case 'Æ': return "ZH";
	case 'Ç': return "Z";
	case 'È': return "I";
	case 'É': return "Y";
	case 'Ê': return "K";
	case 'Ë': return "L";
	case 'Ì': return "M";
	case 'Í': return "N";
	case 'Î': return "O";
	case 'Ï': return "P";
	case 'Ð': return "R";
	case 'Ñ': return "S";
	case 'Ò': return "T";
	case 'Ó': return "U";
	case 'Ô': return "F";
	case 'Õ': return "KH";
	case 'Ö': return "C";
	case '×': return "CH";
	case 'Ø': return "SH";
	case 'Ù': return "JSH";
	case 'Ú': return "HH";
	case 'Û': return "IH";
	case 'Ü': return "JH";
	case 'Ý': return "EH";
	case 'Þ': return "JU";
	case 'ß': return "JA";
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
