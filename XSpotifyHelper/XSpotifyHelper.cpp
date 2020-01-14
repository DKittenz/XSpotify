
#include <Windows.h>

int main()
{
	const char* buffer = "XSpotify.dll";
	DWORD proccess_ID;

	system("start Spotify.exe");
	Sleep(2000);
	HWND hWnd = FindWindow(0, L"Spotify Free");
	GetWindowThreadProcessId(hWnd, &proccess_ID);

	HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, false, proccess_ID);
	LPVOID loadLibAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
	LPVOID base = VirtualAllocEx(h, NULL, strlen(buffer), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	WriteProcessMemory(h, base, buffer, strlen(buffer), NULL);
	HANDLE hHandle = CreateRemoteThread(h, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibAddr, base, 0, NULL);
	WaitForSingleObject(hHandle, INFINITE);

	VirtualFreeEx(h, base, strlen(buffer), MEM_RELEASE);
	CloseHandle(hHandle);
	CloseHandle(h);

	return 0;
}
