#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define MAX_INPUT 1024

// Function to read a line of input
char *read_line(void) {
    char *line = malloc(MAX_INPUT * sizeof(char));
    if (!line) {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }
    fgets(line, MAX_INPUT, stdin);

    // Remove newline character if present
    line[strcspn(line, "\n")] = '\0';

    return line;
}

// Function to parse input into tokens
char **parse_line(char *line) {
    int bufsize = MAX_INPUT, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    if (!tokens) {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(line, " ");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += MAX_INPUT;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                perror("Allocation error");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " ");
    }
    tokens[position] = NULL;
    return tokens;
}

// Function to execute the command
void execute_command(char **args) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Combine arguments into a single command string
    char command[MAX_INPUT];
    strcpy(command, args[0]);
    for (int i = 1; args[i] != NULL; ++i) {
        strcat(command, " ");
        strcat(command, args[i]);
    }

    // Create process
    if (!CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        fprintf(stderr, "CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    // Wait until child process exits
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

// Main loop of the shell
void shell_loop(void) {
    char *line;
    char **args;
    bool status = true;

    do {
        printf("> ");
        line = read_line();
        args = parse_line(line);

        if (args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0) {
                status = false;
            } else {
                execute_command(args);
            }
        }

        free(line);
        free(args);
    } while (status);
}

// Main function
int main(int argc, char **argv) {
    // Run command loop
    shell_loop();

    return EXIT_SUCCESS;
}
