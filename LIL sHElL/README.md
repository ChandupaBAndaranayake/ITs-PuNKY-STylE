**Simple Shell in C for Windows**
    This is a simple shell implementation written in C for Windows      operating systems. It allows basic command execution and provides a minimalistic command-line interface.

**Features**
    - Executes commands entered by the user.
    - Supports basic commands like dir, notepad, etc.
    - Allows exiting the shell with the exit command.

**Requirements**
    - Windows operating system
    - MinGW (Minimalist GNU for Windows) or any other C compiler for Windows

**How to Use**
1. Compile the Shell:
    - Open a command prompt.
    - Navigate to the directory containing simple_shell.c.
    - Compile the code using gcc (MinGW):
        `gcc -o simple_shell simple_shell.c`

2. Run the Shell:
    - After compiling successfully, run the executable:
        `simple_shell`

3. Using the Shell:
    - The shell prompt (> ) will be displayed.
    - Enter commands (e.g., dir, notepad, etc.) and press Enter to execute them.
    - Use the exit command to quit the shell.