#include <bits/stdc++.h>
#include <windows.h>
#include <process.h>
using namespace std;

// Function declarations
void launchNewTerminal();
void showHelp();
void showCommandNotFound(const string& command);

vector<string> parseInput(const string& input) {
    stringstream ss(input);
    string token;
    vector<string> tokens;
    while(ss >> token) tokens.push_back(token);
    return tokens;
}

bool handleCustomCommand(const vector<string>& args) {
    if(args.empty()) return false;
    
    if(args[0] == "exit") {
        cout << "Exiting MyCLI Shell. Goodbye!\n";
        exit(0);
    }
    else if(args[0] == "help" || args[0] == "--help") {
        showHelp();
        return true;
    }
    else if(args[0] == "greet") {
        if(args.size() < 2) {
            cout << "Usage: greet <name>\n";
            cout << "Example: greet John Doe\n";
        }
        else {
            string name;
            for(int i = 1; i < args.size(); i++) {
                name += args[i];
                if(i != args.size() - 1) name += " ";
            }
            cout << "Hello, " << name << "! 👋\n";
        }
        return true;
    }
    else if(args[0] == "reverse") {
        if(args.size() < 2) {
            cout << "Usage: reverse <text>\n";
            cout << "Example: reverse hello world\n";
        }
        else {
            string text;
            for(int i = 1; i < args.size(); i++) {
                text += args[i];
                if(i != args.size() - 1) text += " ";
            }
            reverse(text.begin(), text.end());
            cout << "Reversed: " << text << "\n";
        }
        return true;
    }
    else if(args[0] == "fact") {
        if(args.size() < 2) {
            cout << "Usage: fact <n>\n";
            cout << "Example: fact 5\n";
        }
        else {
            try {
                int n = stoi(args[1]);
                if(n < 0) {
                    cout << "Error: Factorial not defined for negative numbers\n";
                } else if(n > 20) {
                    cout << "Error: Result too large (max n=20)\n";
                } else {
                    long long f = 1;
                    for(int i = 1; i <= n; i++) f *= i;
                    cout << "Factorial(" << n << ") = " << f << "\n";
                }
            } catch(const exception& e) {
                cout << "Error: Invalid number format\n";
            }
        }
        return true;
    }
    else if(args[0] == "new") {
        cout << "Opening new terminal window...\n";
        launchNewTerminal();
        return true;
    }
    else if(args[0] == "debug") {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        cout << "Executable path: " << buffer << endl;
        cout << "Console window: " << (GetConsoleWindow() != NULL ? "Yes" : "No") << endl;
        cout << "Process ID: " << GetCurrentProcessId() << endl;
        return true;
    }
    else if(args[0] == "clear" || args[0] == "cls") {
        system("cls");
        return true;
    }
    else if(args[0] == "pwd") {
        char buffer[MAX_PATH];
        GetCurrentDirectoryA(MAX_PATH, buffer);
        cout << "Current directory: " << buffer << endl;
        return true;
    }
    
    return false;
}

void showHelp() {
    cout << "\n=== MyCLI Shell Help ===\n\n";
    cout << "Available commands:\n";
    cout << "  help, --help    - Show this help message\n";
    cout << "  greet <name>    - Greet someone by name\n";
    cout << "  reverse <text>  - Reverse the given text\n";
    cout << "  fact <n>        - Calculate factorial of n (max 20)\n";
    cout << "  new             - Open a new terminal window\n";
    cout << "  clear, cls      - Clear the screen\n";
    cout << "  pwd             - Show current directory\n";
    cout << "  debug           - Show debug information\n";
    cout << "  exit            - Exit the shell\n\n";
    cout << "System commands:\n";
    cout << "  Any Windows command (dir, type, ping, etc.)\n\n";
    cout << "Examples:\n";
    cout << "  greet John Doe\n";
    cout << "  reverse hello world\n";
    cout << "  fact 5\n";
    cout << "  dir\n";
    cout << "  ping google.com\n\n";
}

void showCommandNotFound(const string& command) {
    cout << "Command '" << command << "' not found.\n";
    cout << "Type 'help' or '--help' to see available commands.\n\n";
}

void executeSystemCommand(const vector<string>& args) {
    // Convert vector<string> to single command string
    string command;
    for(const auto& arg : args) {
        command += arg + " ";
    }
    
    // Use Windows system() function
    int result = system(command.c_str());
    if(result == -1) {
        cout << "Error: Failed to execute system command\n";
    }
}

void launchNewTerminal() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string exePath = string(buffer);
    string exeDir = exePath.substr(0, exePath.find_last_of("\\"));
    string batchPath = exeDir + "\\launch.bat";
    
    cout << "Debug: Executable path: " << exePath << endl;
    
    // Check if launch.bat exists
    ifstream batchFile(batchPath);
    if(batchFile.good()) {
        batchFile.close();
        cout << "Using batch file launcher...\n";
        string batchCmd = "\"" + batchPath + "\"";
        int result = system(batchCmd.c_str());
        if(result == 0) return;
    }
    
    cout << "Attempting to launch in new Command Prompt window...\n";
    
    // Method 1: CMD (most reliable for paths with spaces)
    string cmdCmd = "start \"MyCLI Shell\" cmd /k \"\"" + exePath + "\" --new-window\"";
    int result1 = system(cmdCmd.c_str());
    
    if(result1 != 0) {
        cout << "Command Prompt failed, trying PowerShell...\n";
        // Method 2: PowerShell with proper escaping
        string powershellCmd = "start powershell -ArgumentList \"-Command\", \"& \\\"" + exePath + "\\\" --new-window; pause\"";
        int result2 = system(powershellCmd.c_str());
        
        if(result2 != 0) {
            cout << "PowerShell failed, trying Windows Terminal...\n";
            // Method 3: Windows Terminal (if available)
            string wtCmd = "wt.exe cmd /k \"\"" + exePath + "\" --new-window\"";
            int result3 = system(wtCmd.c_str());
            
            if(result3 != 0) {
                cout << "All methods failed. Creating batch file helper...\n";
                
                // Create launch.bat automatically
                ofstream batch(batchPath);
                if(batch.is_open()) {
                    batch << "@echo off\n";
                    batch << "start \"MyCLI Shell\" cmd /k \"%~dp0mycli.exe --new-window\"\n";
                    batch.close();
                    cout << "Created launch.bat. Running it...\n";
                    system(("\"" + batchPath + "\"").c_str());
                } else {
                    cout << "Manual instructions:\n";
                    cout << "1. Open a new Command Prompt window\n";
                    cout << "2. Run: \"" << exePath << "\" --new-window\n";
                    system("pause");
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Check if we have a special flag indicating we're already in a new window
    bool alreadyInNewWindow = false;
    if(argc > 1 && string(argv[1]) == "--new-window") {
        alreadyInNewWindow = true;
    }
    
    // If not already in new window, launch one
    if(!alreadyInNewWindow) {
        cout << "Launching in new terminal window...\n";
        launchNewTerminal();
        return 0;
    }
    
    // Main shell loop (only runs in the new window)
    cout << "🚀 Welcome to MyCLI Shell!\n";
    cout << "Type 'help' to see available commands or 'exit' to quit.\n\n";
    
    string input;
    while(true) {
        cout << "mycli> ";
        getline(cin, input);
        
        if(input.empty()) continue;
        
        cout << "[Command entered]: " << input << "\n";
        vector<string> args = parseInput(input);
        
        if(!handleCustomCommand(args)) {
            // Check if it's a known Windows command or show error
            string cmd = args[0];
            transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
            
            // Common Windows commands that should work
            vector<string> commonCommands = {
                "dir", "cd", "copy", "del", "type", "echo", "ping", "ipconfig",
                "tasklist", "taskkill", "whoami", "hostname", "systeminfo",
                "netstat", "tree", "findstr", "attrib", "xcopy", "robocopy"
            };
            
            bool isCommonCommand = find(commonCommands.begin(), commonCommands.end(), cmd) != commonCommands.end();
            
            if(isCommonCommand) {
                executeSystemCommand(args);
            } else {
                // Try to execute anyway, but show help if it fails
                int oldErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS);
                int result = system((args[0] + " >nul 2>nul").c_str());
                SetErrorMode(oldErrorMode);
                
                if(result != 0) {
                    showCommandNotFound(args[0]);
                } else {
                    executeSystemCommand(args);
                }
            }
        }
    }
    
    return 0;
}