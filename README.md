# .bat2cpp - Convert .bat Scripts to C++ for Invisible Execution

A utility designed to convert `.bat` scripts into C++ programs that run commands invisibly. It reads a configuration file (in `.json` format) containing command-line instructions, converts them into executable C++ code, and then runs them without showing a command window to the user. This tool is ideal for performing background tasks such as modifying system variables, registry settings, or running system commands without user interaction.

## Features

- **Invisible Command Execution**: Converts `.bat` script commands into C++ code that runs them in the background, without showing a console window.
- **Customizable**: Easily modify the commands in a configuration file to be converted to C++ code.
- **Silent Operation**: Ideal for making changes to system settings or performing maintenance tasks without user interference.

## Requirements

### C++ Environment

- **C++ Compiler** (e.g., Visual Studio, MinGW, or any C++17-compliant compiler)
- Windows OS (for Windows-specific commands like `wmic` and `sc`)

### Python Environment

- Python 3.7+
- Required Python packages:
  - `json`

You can install the necessary Python dependencies by running:

```bash
pip install -r requirements.txt
```

## How It Works

1. **Python Script (`convert_to_cpp.py`)**:
   - Reads the `config.json` file containing commands to be executed.
   - Converts each command into valid C++ code.
   - Outputs a `.cpp` file that executes the commands invisibly.

2. **C++ Code**:
   - The generated C++ code executes the commands using the `CreateProcessW` function to prevent the command window from being displayed.
   - The program waits for each command to finish before closing.

## Usage

### Step 1: Configure Commands in `config.json`

Begin by editing the `config.json` file to include the commands you wish to execute. Each command should be a string within the `commands` array. These can be typical `.bat` script commands, such as modifying registry values, setting process priorities, or changing system settings.

For example:

```json
{
  "commands": [
    "wmic process where name=\"FortniteClient-Win64-Shipping.exe\" CALL setpriority \"high priority\"",
    "reg add \"HKCU\\Control Panel\\Desktop\" /v DragFullWindows /t REG_SZ /d 0 /f",
    "powercfg -duplicatescheme e9a42b02-d5df-448d-aa00-03f14749eb61"
  ]
}
```

Or (just pasting the .bat script):

```json
wmic process where name="FortniteClient-Win64-Shipping.exe" CALL setpriority "high priority"
```

### Step 2: Run the Python Script to Generate C++ Code

Once the `config.json` file is configured, run the Python script `convert_to_cpp.py` to generate the C++ code:

```bash
python convert_to_cpp.py
```

The script will read the commands from `config.json`, convert them into C++ code, and output a `.cpp` file that contains the necessary logic to execute those commands invisibly.

### Step 3: Copy the C++ Code into Your Project

The output of the Python script will be a C++ file (e.g., `generated_commands.cpp`). Copy the contents of this file into your C++ project. Ensure that you also include the **C++ base code** from `useme.cpp`, which sets up the necessary environment for running the commands invisibly.

Here is a sample template for `useme.cpp`:

```cpp
#include <iostream>
#include <windows.h>
#include <string>

// Function to convert a std::string to std::wstring
std::wstring string_to_wstring(const std::string &str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

void run_command(const std::string &command) {
    std::wstring wcommand = string_to_wstring(command);

    // Set up the STARTUPINFO structure to hide the console window
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    ZeroMemory(&pi, sizeof(pi));

    // Execute the command
    if (CreateProcessW(NULL, &wcommand[0], NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        std::cerr << "Failed to execute command: " << command << std::endl;
    }
}

int main() {
    std::cout << "Running commands silently in the background..." << std::endl;

    // Execute all the commands from the generated C++ code
    run_command("wmic process where name=\"FortniteClient-Win64-Shipping.exe\" CALL setpriority \"high priority\"");
    
    return 0;
}
```

### Step 4: Compile and Run the C++ Program

Once you have copied the generated C++ code into your project and set up your `useme.cpp`, compile the program using your C++ development environment (e.g., Visual Studio or MinGW).

When you run the program, it will execute the commands in the background without showing the terminal window. This is particularly useful for making system changes, such as modifying the registry or setting process priorities.

## Notes and Limitations

This tool was primarily designed for running `.bat` scripts that contain commands related to changing system variables, modifying registry values, or performing other background tasks. However, **it may not work perfectly with all `.bat` scripts**, especially those that involve complex user interaction or need to display information to the user.

While the tool aims to provide a seamless way to execute background tasks silently, it may not be as accurate or versatile as expected in all cases. The repository owner will continue developing and improving this project to handle more scenarios.

### Disclaimer
A sample `.bat` script is included in this repository as an example, but please note that **this sample comes from a PC tweaker**. If you are familiar with my other repository, [Nexus Tweaker Source](https://github.com/spark4k0/Nexus-Tweaker-Src), you will know my opinion of PC tweakers. **I do not recommend running this sample script, and I am not liable for any damages caused by using it.** The `.bat` script included is only a demonstration of how the `.bat` script could look like and should be handled with caution.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Feel free to fork this repository, submit issues, and contribute improvements. To contribute, create a pull request with a detailed description of your changes.

## Acknowledgements

- Thanks to the [Windows API documentation](https://learn.microsoft.com/en-us/windows/win32/api/) for the details on using `CreateProcessW` to execute commands invisibly.
```
