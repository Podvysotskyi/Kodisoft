#include "stdafx.h"
#include "main.h"
#include "MyLib.h"
#include "_Process.h"

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::string;

vector<_Process*> proc_list;

int _tmain(int argc, _TCHAR * argv[]) {
	cout << argc - 1 << " processes will start." << endl;

	for (int i = 1; i < argc; ++i)
		Create_Process(argv[i]);

	Print_Help();

	bool exit = false;

	do {
		vector<string> input = Get_Input();

		if (input.size() == 1) {
			if (input.at(0) == "q" || input.at(0) == "exit")
				exit = true;

			else if (input.at(0) == "h" || input.at(0) == "?" || input.at(0) == "help")
				Print_Help();

			else if (input.at(0) == "l" || input.at(0) == "list")
				Print_List();
		}

		else if (input.at(0) == "add")
			Create_Process((_TCHAR*)Get_String(input).c_str());

		else if (input.size() == 2) {

			if (input.at(0) == "stop")
				try {
				int id = std::stoi(input.at(1));
				if (id < 0 || id >= proc_list.size())
					throw "No index";
				proc_list.at(id)->Stop();
			}
			catch (...) {
				Print_Error();
			}

			else if (input.at(0) == "start")
				try {
				int id = std::stoi(input.at(1));
				if (id < 0 || id >= proc_list.size())
					throw "No index";
				proc_list.at(id)->Start();
			}
			catch (...) {
				Print_Error();
			}

			else if (input.at(0) == "restart")
				try {
				int id = std::stoi(input.at(1));
				if (id < 0 || id >= proc_list.size())
					throw "No index";
				proc_list.at(id)->Restart();
			}
			catch (...) {
				Print_Error();
			}
		}
	} while (!exit);

	for each (_Process* procc in proc_list)
		delete procc;

	proc_list.clear();

	cout << "Press any key to exit";
	std::getchar();

	return 0;
}

void Create_Process(_TCHAR * str) {
	_Process * process = new _Process(str, proc_list.size());
	if (process->Start()) {
		cout << "Process ID : " << proc_list.size() << endl;
		proc_list.push_back(process);
	}
	else if (!File_Exists(str))
		cout << "Process \"" << str << "\" doesn't exist." << endl;
	else
		cout << "Process \"" << str << "\" wasn't started." << endl;
}

void Print_List() {
	if (proc_list.size() <= 0)
		cout << "There are no processes" << endl;
	else
		cout << "There are " << proc_list.size() << " processes" << endl;
	for each (_Process * proc in proc_list)
		proc->Print();
}
