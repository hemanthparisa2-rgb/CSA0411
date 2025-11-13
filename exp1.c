#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

// Function to get the Parent Process ID in Windows
DWORD GetParentProcessId(DWORD pid) {
    HANDLE hSnapshot;
    PROCESSENTRY32 pe32;
    DWORD ppid = 0;

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (pe32.th32ProcessID == pid) {
                ppid = pe32.th32ParentProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    return ppid;
}

int main() {
    DWORD pid = GetCurrentProcessId();
    DWORD ppid = GetParentProcessId(pid);

    printf("Process ID: %lu\n", pid);
    printf("Parent Process ID: %lu\n", ppid);

    system("pause");  // Keeps the console window open
    return 0;
}
