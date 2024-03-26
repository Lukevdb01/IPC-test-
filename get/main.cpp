#include <iostream>
#include <windows.h>

using namespace std;

#define SHARED_MEM_NAME L"l_shared_mem"
#define SHARED_MEM_SIZE 12288

int main() {
    HANDLE hMapFile = OpenFileMapping(FILE_MAP_READ, FALSE, SHARED_MEM_NAME);
    if (hMapFile == NULL) {
		std::cerr << "Failed to open file mapping object: " << GetLastError() << std::endl;
		return -1;
	}

	LPVOID pBuf = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, SHARED_MEM_SIZE);
	if (pBuf == NULL) {
		std::cerr << "Failed to map view of file: " << GetLastError() << std::endl;
		CloseHandle(hMapFile);
		return -1;
	}

	

	// Read data from shared memory
	char data[SHARED_MEM_SIZE];
	CopyMemory(data, pBuf, SHARED_MEM_SIZE);

	cout << "Data read from shared memory: " << data << endl;

	// Unmap the shared memory
	UnmapViewOfFile(pBuf);

	// Close the file mapping handle
	CloseHandle(hMapFile);

	return 0;
}
