#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

#define SHARED_MEM_NAME L"l_shared_mem"
#define SHARED_MEM_SIZE 12288

int main() {
    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, SHARED_MEM_SIZE, SHARED_MEM_NAME);
    if (hMapFile == NULL) {
        std::cerr << "Failed to create file mapping object: " << GetLastError() << std::endl;
        return -1;
    }

    LPVOID pBuf = MapViewOfFile(hMapFile, FILE_MAP_WRITE, 0, 0, SHARED_MEM_SIZE);
    if (pBuf == NULL) {
		std::cerr << "Failed to map view of file: " << GetLastError() << std::endl;
		CloseHandle(hMapFile);
		return -1;
	}

    // Write data to shared memory
	string data = "Hello, shared memory!";
	CopyMemory(pBuf, data.c_str(), data.size());

	Sleep(50000); // Wait for the other process to read the data

	cout << "Data address closed" << data << endl;
	// Unmap the shared memory
	UnmapViewOfFile(pBuf);

	// Close the file mapping handle
	CloseHandle(hMapFile);

	return 0;
}
