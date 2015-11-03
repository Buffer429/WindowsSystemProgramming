/* Basic Copy File Program			          */
/* CopyFile file1 file2 : Copy file1 to file2 */

#include <windows.h>	// Always required for Windows
#include <stdio.h>

#define BUF_SIZE 256	// Increase for faster copy

int main(int argc, char* argv[])
{
	HANDLE hIn, hOut;	// Input and output handles
	DWORD nIn, nOut;	// Number bytes transferred
	CHAR buffer[BUF_SIZE];

	if (argc != 3)
	{
		printf("Usage: CopyFile file1 file2\n");
		return 1;
	}

	/*
		Create handles for reading and writing.
		Many default values are used.
	*/
	hIn = CreateFile(argv[1], GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hIn == INVALID_HANDLE_VALUE)
	{
		printf("Cannot open input file\n");
		return 2;
	}

	hOut = CreateFile(argv[2], GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		printf("Cannot open output file\n");
		return 3;
	}

	/*
		Input and output file handles are open.
		Copy file. Note end-of-file detection.
	*/
	while (ReadFile(hIn, buffer, BUF_SIZE, &nIn, NULL) && nIn > 0)
	{
		WriteFile(hOut, buffer, nIn, &nOut, NULL);
	}

	// Deallocate resource, such as open handles.
	CloseHandle(hIn);
	CloseHandle(hOut);

	return 0;
}