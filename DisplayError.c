// Gets an error message id and if a message with the provided id exists, the program prints the message, if not, it just prints "No such error exists"
#include <windows.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

	if (argc < 2) {
		printf("Usage: DisplayError.exe <Error number>");
		return 0;
	}

	int message = atoi(argv[1]);
	LPWSTR text;
	DWORD chars = ::FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, message, 0,
		(LPWSTR)&text,
		0, nullptr);

	if (chars > 0) {
		printf("Message %d: %ws", message, text);
		::LocalFree(text);
	}
	else {
		printf("No such error exists");
	}




	return 0;
}
