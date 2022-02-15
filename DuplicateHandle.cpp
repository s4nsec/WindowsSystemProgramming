#include <Windows.h>
#include <stdio.h>

int main() {
	HANDLE hJob = ::CreateJobObject(nullptr, nullptr);
	HANDLE hJob2;

	// last parameter is dwOptions, we can put 0 to negate it, or DUPLICATE_CLOSE_SOURCE(0x00000001) to close the source handle
	// or DUPLICATE_SAME_ACCESS(0x00000002) to have the target handle have the same access rights as the source handle
	::DuplicateHandle(::GetCurrentProcess(), hJob, ::GetCurrentProcess(), &hJob2, JOB_OBJECT_ASSIGN_PROCESS | JOB_OBJECT_TERMINATE, FALSE, 0);







	return 0;
}
