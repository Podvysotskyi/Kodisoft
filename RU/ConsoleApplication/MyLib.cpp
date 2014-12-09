#include "stdafx.h"
#include "MyLib.h"

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::string;

void Print_Error() {
	cout << "There is an error in your input string." << endl << "Type '?' for help." << endl;
}

string Get_String(vector<string> input) {
	string result = "";
	for (int i = 1; i < input.size() - 1; i++)
		result += input.at(i) + " ";
	return result + input.at(input.size() - 1);
}


int File_Exists(_TCHAR * file) {
	WIN32_FIND_DATA FindFileData;
	HANDLE handle = FindFirstFile(file, &FindFileData);
	int found = handle != INVALID_HANDLE_VALUE;
	if (found)
		FindClose(handle);
	return found;
}

vector<string> Get_Input() {
	string str;
	cout << ">>> ";
	std::getline(std::cin, str);
	return split(str, ' ');
}

vector<string> split(const string &s, char ch) {
	vector<string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, ch))
		elems.push_back(item);
	return elems;
}

void Print_Help() {
	cout << "---------------------------------------------------" << endl;
	cout << "?, h, help       -  help" << endl;
	cout << "q, exit          -  exit" << endl;
	cout << "l, list          -  list of all processes" << endl;
	cout << "stop {id}        -  stop processes with {id}" << endl;
	cout << "start {id}       -  start processes with {id}" << endl;
	cout << "restart {id}     -  restart processes with {id}" << endl;
	cout << "add {path}{argc} -  add new process" << endl;
	cout << "---------------------------------------------------" << endl;
}
