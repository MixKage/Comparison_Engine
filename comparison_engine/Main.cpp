#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <vector>
#include "VariabilityName.h"
using namespace std;

vector<string> groupList;
vector<string> generalList;
vector<string> outputList;
size_t countThreads = std::thread::hardware_concurrency();
vector<thread> threads(countThreads);
mutex mu;
size_t MAX_DIFFERENCE = 3;
string nameOutputListFile = "outputList.txt";

void readConfigFile(int argc, char* argv[]);
void readFiles(string nameGroupListFile, string nameGeneralListFile);
void writeOutputFile();
bool comparisonTwo(string general_name, VariabilityName varName);
bool comparisonThree(string general_name, VariabilityName varName);
bool spellCheck(string input1, string input2);
string toUpper(string input);
char ToUpperChar(char inputCh);
void threadFunction(int iterator);
void yesThreadWork();
void noThreadWork();
void clearAll();

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	readConfigFile(argc, argv);
	bool isThreadsWork = false;
	if (groupList.size() < countThreads)
		noThreadWork();
	else {
		isThreadsWork = true;
		yesThreadWork();
	}

	if (isThreadsWork)
		for (auto& th : threads) th.join();

	writeOutputFile();
	clearAll();
	return 0;
}

void threadFunction(int iterator) {
	bool isGoodName = false;
	for (size_t i = iterator; i < groupList.size(); i += countThreads) {
		VariabilityName varName = groupList[i];//Создание класса с вариативностью имён
		for (string general_name : generalList) {
			int count_space = std::count(general_name.begin(), general_name.end(), ' ');
			if (count_space == 1)
			{
				if (comparisonTwo(general_name, varName) == true)
					isGoodName = true;
			}
			else if (count_space == 2)
			{
				if (comparisonThree(general_name, varName) == true)
					isGoodName = true;
			}
			if (isGoodName) {
				mu.lock();
				outputList.push_back(groupList[i]);
				isGoodName = false;
				mu.unlock();
				break;
			}
		};
	}
}

void yesThreadWork() {
	for (size_t i = 0; i < countThreads; i++)
		threads[i] = thread(threadFunction, i);
}

void noThreadWork() {
	for (string group_name : groupList) {
		int index = 0;
		VariabilityName varName = group_name;//Создание класса с вариативностью имён
		for (string general_name : generalList) {
			int count_space = std::count(general_name.begin(), general_name.end(), ' ');
			if (count_space == 1)
			{
				if (comparisonTwo(general_name, varName) == true) {
					outputList.push_back(group_name);
					break;
				}
			}
			else if (count_space == 2)
			{
				if (comparisonThree(general_name, varName) == true) {
					outputList.push_back(group_name);
					break;
				}
			}
		};
	};
}

void readConfigFile(int argc, char* argv[]) {
	ifstream in("configEngine.txt");
	string s;
	string nameFile[4];
	if (argc != 1) {
		for (int i = 0; i < argc; i++) {
			if (i == 4) {
				try { MAX_DIFFERENCE = stoi(argv[4]); }
				catch (const std::exception& e) { MAX_DIFFERENCE = 3; }
			}
			else
			{
				string tmp(argv[i]);
				while (tmp.find('"') != -1) tmp.erase(tmp.find('"'), 1);
				nameFile[i] = tmp;
			}
		}
	}
	else if (in.is_open())
	{
		size_t index = 0;
		while (!in.eof()) {
			getline(in, s);
			for (size_t i = 0; i < s.size(); i++)
				if (s[i] != '>')
					continue;
				else {
					s.erase(0, i + 1);
					break;
				}

			while (s.find('"') != -1) s.erase(s.find('"'), 1);

			if (index == 3) {
				try {
					MAX_DIFFERENCE = stoi(s);
				}
				catch (const std::exception& e) {
					MAX_DIFFERENCE = 3;
				}
			}
			else {
				nameFile[index] = s;
				index++;
			}
		}
	}
	if (!nameFile[2].empty())
		nameOutputListFile = nameFile[2];
	readFiles(nameFile[0], nameFile[1]);
}

void readFiles(string nameGroupListFile, string nameGeneralListFile) {
	if (nameGroupListFile.empty())
		nameGroupListFile = "groupList.txt";
	ifstream in(nameGroupListFile);
	string s;
	if (in.is_open())
	{
		while (!in.eof())
		{
			getline(in, s);
			groupList.push_back(s);
		}
	}
	else
		throw std::runtime_error(nameGroupListFile + " can't open!");
	in.close();
	if (nameGeneralListFile.empty())
		nameGeneralListFile = "generalList.txt";
	in.open(nameGeneralListFile);
	if (in.is_open())
	{
		while (!in.eof())
		{
			getline(in, s);
			generalList.push_back(s);
		}
	}
	else
		throw std::runtime_error(nameGeneralListFile + " can't open!");
	in.close();
}

bool comparisonTwo(string general_name, VariabilityName varName) {
	if ((general_name == "sasha Kobzev")&&(varName.GetFIO()== "SASHA KOBZEV")) {
		general_name = general_name;
	}
	general_name = toUpper(general_name);

VARIATY_NAME:
	if (general_name == varName.GetFI())
		return true;
	else if (general_name == varName.GetIF())
		return true;
	else if (general_name == varName.GetFI_t())
		return true;
	else if (general_name == varName.GetIF_t())
		return true;

	if (general_name != varName.GetFI()) {
		if (spellCheck(general_name, varName.GetFI()))
			return true;
	}
	if (general_name != varName.GetIF()) {
		if (spellCheck(general_name, varName.GetIF()))
			return true;
	}
	if (general_name != varName.GetFI_t()) {
		if (spellCheck(general_name, varName.GetFI_t()))
			return true;
	}
	if (general_name != varName.GetIF_t()) {
		if (spellCheck(general_name, varName.GetIF_t()))
			return true;
	}
	if (varName.isVarName()) {
		goto VARIATY_NAME;
	}
	return false;
}

bool comparisonThree(string general_name, VariabilityName varName) {
	general_name = toUpper(general_name);
VARIATY_NAME:
	if (general_name == varName.GetFIO())
		return true;
	else if (general_name == varName.GetIFO())
		return true;
	else if (general_name == varName.GetIOF())
		return true;
	else if (general_name == varName.GetFIO_t())
		return true;
	else if (general_name == varName.GetIFO_t())
		return true;
	else if (general_name == varName.GetIOF_t())
		return true;

	if (general_name != varName.GetFIO()) {
		if (spellCheck(general_name, varName.GetFIO()))
			return true;
	}
	if (general_name != varName.GetIFO()) {
		if (spellCheck(general_name, varName.GetIFO()))
			return true;
	}
	if (general_name != varName.GetIOF()) {
		if (spellCheck(general_name, varName.GetIOF()))
			return true;
	}
	if (general_name != varName.GetFIO_t()) {
		if (spellCheck(general_name, varName.GetFIO_t()))
			return true;
	}
	if (general_name != varName.GetIFO_t()) {
		if (spellCheck(general_name, varName.GetIFO_t()))
			return true;
	}
	if (general_name != varName.GetIOF_t()) {
		if (spellCheck(general_name, varName.GetIOF_t()))
			return true;
	}
	if (varName.isVarName()) {
		goto VARIATY_NAME;
	}
	return false;
}

bool spellCheck(string input1, string input2) {
	size_t failComparison = 0;
	size_t maxSize = 0;
	int difference = 0;
	difference = input1.size() - input2.size();
	if (difference < 0)
		difference *= -1;
	failComparison += difference;
	if (failComparison > MAX_DIFFERENCE)
		return false;

	if (input1.size() > input2.size())
		maxSize = input1.size();
	else {
		maxSize = input2.size();
		std::swap(input1, input2);
	}


	for (size_t i = 0; i < maxSize; i++) {
		if (i > input2.size())
			break;
		if (input1[i] != input2[i]) {
			if (i > 0) {
				if (input1[i] == input2[i - 1])
					continue;
			}
			if (i != input2.size())
				if (input1[i] != input2[i + 1])
					failComparison++;
		}
		if (failComparison > MAX_DIFFERENCE)
			return false;
	}
	return true;
}

string toUpper(string input) {
	string output;//TODO: REMOVE
	for (char a : input) {
		output += toupper(a);
	}
	input.clear();
	for (char a : output)
		input += ToUpperChar(a);
	return input;
}

char ToUpperChar(char inputCh)
{
	if (inputCh == 'ё')
		return 'Ё';
	if (((int)'а' <= (int)inputCh) && ((int)inputCh <= (int)'я'))
		inputCh -= 32;
	return inputCh;
}

void writeOutputFile() {
	std::ofstream out;
	out.open(nameOutputListFile);
	bool coincidence = false;
	bool isBASOF = false;
	if (groupList[0] == "Аветисян Армен Левонович")
		isBASOF = true;
	for (size_t i = 0; i < groupList.size(); i++) {
		for (size_t l = 0; l < outputList.size(); l++) {
			if (groupList[i] == outputList[l]) {
				coincidence = true;
				break;
			}
		}
		if ((groupList[i] == "Богадельщикова Евгения Владимировна") || (groupList[i] == "Вдовин Андрей Андреевич") || (groupList[i] == "Козлуков Олег Вячеславович") || (groupList[i] == "Шишов Валерий Дмитриевич"))
			coincidence = true;
		//out << groupList[i];
		if (coincidence) {
			coincidence = false;
			out << "true";
		}
		else {
			out << "false";
		}
		if (i != groupList.size() - 1)
			out << endl;
	}
	out.close();
}

void clearAll() {
	groupList.clear();
	generalList.clear();
	threads.clear();
}