#include <windows.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <iostream>

DWORD findProcessId(std::wstring& processName) {
	//printf("%s", processName);
	PROCESSENTRY32 pInfo;
	pInfo.dwSize = sizeof(pInfo);

	// hanle to the snapshot of processes
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (!hSnapshot) {
		printf("Error occured while getting a handle to the process. Error code: %d\n", ::GetLastError());
		return 0;
	}

	if (!::Process32First(hSnapshot, &pInfo)) {
		printf("Error occured while calling Process32First. Error code: %d\n", ::GetLastError());
		return 0;
	}

	::Process32First(hSnapshot, &pInfo);
	if (!processName.compare(pInfo.szExeFile)) {
		::CloseHandle(hSnapshot);
		return pInfo.th32ProcessID;
	}

	while (::Process32Next(hSnapshot, &pInfo)) {
		if (!::Process32Next(hSnapshot, &pInfo)) {
			printf("Error occured while calling Process32Next. Error code: %d\n", ::GetLastError());
			return 0;
		}
		if (!processName.compare(pInfo.szExeFile)) {
			::CloseHandle(hSnapshot);
			return pInfo.th32ProcessID;
		}

	}

	return 0;
}

DWORD processKiller(DWORD processId) {
	DWORD pid = processId;
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);

	if (!hProcess)	return 0;

	if (::TerminateProcess(hProcess, 1) == 0) {
		printf("Error occured while calling TerminateProcess. Error code: %d\n", ::GetLastError());
		return 0;
	}

	BOOL success = ::TerminateProcess(hProcess, 1);

	::CloseHandle(hProcess);
	return 1;
}	

int main() {
	std::wstring userInput;
	DWORD pid;

	printf("Enter the name of a process you would like to kill: ");
	std::wcin >> userInput;

	pid = findProcessId(userInput);

	DWORD op = processKiller(pid);
	
	if(op == 1)
		printf("The process has been terminated successfully!");
	else
		printf("The process has not been terminated. Error occured!");
	
	return 0;
}
