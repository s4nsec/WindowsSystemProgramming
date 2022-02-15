#include <windows.h>
#include <stdio.h>
#include <string>
#include <TlHelp32.h>
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

int main() {
	std::wstring userInput;
	DWORD dwFlags;
	printf("Enter a process name first: \n");
	std::wcin >> userInput;

	HANDLE hObject = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, findProcessId(userInput));

	::SetHandleInformation(hObject, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);

	DWORD result = ::GetHandleInformation(hObject, &dwFlags);

	printf("GetHandleInformation dwFlag Result: %d\n", dwFlags);

	printf("GetHandleInformation Result: %d. GetLastError: %d \n", result, ::GetLastError());

	return 0;
}
