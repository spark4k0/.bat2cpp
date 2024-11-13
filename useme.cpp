#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

void printSlow(string ctext, int speed)
{
	int size = ctext.length();
	for (int i = 0; i < size; i++)
	{
		Sleep(speed);
		cout << ctext[i];
	}
}

std::wstring string_to_wstring(const std::string& str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

void run_command(const std::string& command) {
    std::wstring wcommand = string_to_wstring(command);

    // CreateProcess setup
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Initialize the STARTUPINFO structure
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW; // We want to set the window visibility
    si.wShowWindow = SW_HIDE; // Hide the window

    // Zero out the PROCESS_INFORMATION structure
    ZeroMemory(&pi, sizeof(pi));

    // Run the command silently (in the background)
    if (CreateProcessW(
        NULL,                   // Application name (NULL = use command line)
        &wcommand[0],           // Command line
        NULL,                   // Process handle not inheritable
        NULL,                   // Thread handle not inheritable
        FALSE,                  // Set handle inheritance to FALSE
        CREATE_NO_WINDOW,       // Don't show the command window
        NULL,                   // Use parent's environment block
        NULL,                   // Use parent's starting directory
        &si,                    // Pointer to STARTUPINFO structure
        &pi)                    // Pointer to PROCESS_INFORMATION structure
        ) {
        // Wait for the process to terminate and then close the handles
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        std::cerr << "Failed to execute command: " << command << std::endl;
    }
}


int main()
{
    printSlow("Running commands silently in the background...", 0100);
    // commands here
    system("pause >nul"); // pauses the programm, so you can view possible errors
}
