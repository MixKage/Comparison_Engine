#pragma once
#include <string>
#include <map>
class VariabilityName
{
private:
	std::string _FIO;
	std::string _IFO;
	std::string _IOF;
	std::string _FI;
	std::string _IF;
	std::string _FIO_t;
	std::string _IFO_t;
	std::string _IOF_t;
	std::string _FI_t;
	std::string _IF_t;
	std::string Translit(std::string input);
	std::string TranslitLetter(char input);
	char ToUpper(char inputCh);
	std::string CheckVarName(std::string input);
	std::map <std::string, std::string> varNames = { {"���������", "����"},{"�������", "����"},
		{"������", "������"},{"������", "�������"},{"�������", "����"},{"������", "����"},
		{"�����", "����"},{"����������", "�����"},{"������", "����"},{"������", "����"},
		{"����", "����"},{"������", "����"},{"��������", "�����"},{"�������", "������"},
		{"�����", "���"},{"��������", "�����"},{"�����", "���"},{"���������", "����"},
		{"�������", "����"},{"���������", "�����"},{"�����", "����"},
		{"����������", "����"},{"�����", "����"}, {"�������", "����"}};
public:
	VariabilityName(std::string input);
	void VariabilityNameEng(std::string input);
	std::string GetFIO();
	std::string GetIFO();
	std::string GetIOF();
	std::string GetFI();
	std::string GetIF();
	std::string GetFIO_t();
	std::string GetIFO_t();
	std::string GetIOF_t();
	std::string GetFI_t();
	std::string GetIF_t();
	bool isVarName();
};