#define WIN32_DEFAULT_LIBS

#include "stdafx.h"
#include "_Process.h"

using std::cout;
using std::endl;
using std::string;
using std::thread;

void run(_Process * proc) {
	WaitForSingleObject(proc->information.hProcess, INFINITE);
	DWORD result;
	GetExitCodeProcess(proc->information.hProcess, &result);
	if (result != -999 && result != 0)
		proc->OnProcCrash(result);
}

_Process::_Process(string name, int _id)
{
	id = _id;
	this->name = name;
	ZeroMemory(&startup, sizeof(STARTUPINFO));
	startup.cb = sizeof(STARTUPINFO);
}

_Process::~_Process()
{
	if (_thread != NULL)
		Stop();
	delete _thread;
}

_TCHAR * _Process::Get_Name() {
	return (_TCHAR *)name.c_str();
}

void _Process::Print() {
	cout << endl << "Process : \"" << name << "\"" << endl << "Id : " << id << endl << "Status : ";
	if (_thread == NULL)
		cout << "NULL";
	else
		cout << "RUNING";
	cout << endl;
}

void _Process::OnProcCrash(DWORD error) {
	string text = "Process crashed with code ";
	text += std::to_string(error);
	try {
		_thread->join();
	}
	catch (...) { }
	_thread = NULL;
	MessageBox(NULL, text.c_str(), name.c_str(), MB_OK);
}

void _Process::OnProcManuallyStopped() {
	cout << "Process \"" << this->name << "\" was stopped" << endl;
}

void _Process::OnProcStart() {
	cout << "Process \"" << this->name << "\" was started" << endl;
}

bool _Process::Start() {
	if (_thread == NULL && (CreateProcess(Get_Name(), NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startup, &information) ||
		CreateProcess(NULL, Get_Name(), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startup, &information))) {
		OnProcStart();
		_thread = new thread(run, this);
		return true;
	}
	return false;
}

void _Process::Stop() {
	if (_thread != NULL) {
		try {
			TerminateProcess(information.hProcess, -999);
			_thread->join();
		}
		catch (...) {}
		OnProcManuallyStopped();
		_thread = NULL;
	}
}

void _Process::Restart() {
	Stop();
	Start();
}