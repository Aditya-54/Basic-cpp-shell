# MyCLI Shell 🚀

Welcome to **MyCLI Shell**, a lightweight and customizable command-line interface built in C++! This shell provides a mix of custom commands and support for standard Windows commands, making it a versatile tool for developers and power users.

---

## Features ✨

- **Custom Commands**:
  - `help` or `--help`: Display a list of available commands.
  - `greet <name>`: Greet someone by name.
  - `reverse <text>`: Reverse the given text.
  - `fact <n>`: Calculate the factorial of a number (up to 20).
  - `new`: Open a new terminal window running MyCLI.
  - `clear` or `cls`: Clear the terminal screen.
  - `pwd`: Display the current working directory.
  - `debug`: Show debug information about the shell.
  - `exit`: Exit the shell.

- **Windows System Commands**:
  - Execute any standard Windows command like `dir`, `ping`, `ipconfig`, etc.

- **Interactive Shell**:
  - User-friendly interface with helpful error messages and examples.

- **Dynamic Terminal Management**:
  - Launch new terminal windows with MyCLI using multiple fallback methods.

---

## Getting Started 🚀

### Prerequisites
- Windows operating system.
- A C++ compiler (e.g., MinGW, MSVC).
- `mycli.exe` (compiled version of the project).

### Build Instructions
1. Clone the repository or copy the source code.
2. Compile the `a.cpp` file using your preferred C++ compiler:
   ```bash
   g++ a.cpp -o mycli.exe
   ```
3. Run the compiled executable:
   ```bash
   mycli.exe
   ```

---

## Usage 🛠️

### Launching the Shell
Simply run the `mycli.exe` file. The shell will open in a new terminal window.

### Example Commands
- Greet someone:
  ```bash
  mycli> greet John Doe
  Hello, John Doe! 👋
  ```
- Reverse text:
  ```bash
  mycli> reverse hello world
  Reversed: dlrow olleh
  ```
- Calculate factorial:
  ```bash
  mycli> fact 5
  Factorial(5) = 120
  ```
- Clear the screen:
  ```bash
  mycli> clear
  ```

---

## Debugging 🐞

Use the `debug` command to display information about the shell, including:
- Executable path.
- Console window status.
- Process ID.

---

## Troubleshooting ❓

If the shell fails to open in a new terminal window:
1. Ensure `mycli.exe` is in the same directory as the shell.
2. Check for the presence of `launch.bat` (it will be created automatically if missing).
3. Manually open a new terminal and run:
   ```bash
   mycli.exe --new-window
   ```

---

## Contributing 🤝

Contributions are welcome! Feel free to fork the project, submit issues, or create pull requests.

---

## License 📜

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Acknowledgments 🙌

- Inspired by the simplicity of traditional command-line interfaces.
- Built with ❤️ using C++.

---

Enjoy using **MyCLI Shell**! 🚀
