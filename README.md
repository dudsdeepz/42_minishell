Minishell is an educational project from the 42 Network curriculum, designed to create a lightweight shell in C, mimicking core functionalities of a Unix shell like bash. It provides hands-on experience with process management, system calls, and command-line parsing, offering insight into how shells operate under the hood.
Overview
Minishell implements a command-line interpreter that executes user inputs, supports built-in commands, and handles external program execution. The project focuses on replicating key shell behaviors, such as command parsing, piping, redirections, and environment variable management, while adhering to strict C programming standards (C89/C90).

Understand process creation and management (fork, execve, etc.).
Implement command parsing and execution with proper error handling.
Support redirections, pipes, and environment variable expansion.
Learn signal handling for user interactions (e.g., Ctrl+C).

The shell operates in an interactive mode, reading commands from the user and executing them in a Unix-like environment.

Command Execution: Executes external programs (e.g., ls, grep) via execve.
Built-in Commands: Supports echo, cd, pwd, export, unset, env, and exit.
Redirections: Handles input (<), output (>), and append (>>) redirections.
Pipes: Supports piping (|) to chain commands.
Environment Variables: Manages variables (e.g., $PATH, $HOME) with expansion in commands.
Signal Handling: Handles SIGINT (Ctrl+C) and SIGQUIT (Ctrl+) for graceful interrupts.
Heredoc: Implements << for multi-line input until a delimiter.
Error Handling: Provides informative error messages compliant with bash behavior.

Note: Advanced features like wildcards (*), subshells, or complex scripting are not implemented.

Language: C (C89/C90 compliance for portability).
Libraries: Standard C library (<unistd.h>, <stdlib.h>, <sys/wait.h>); no external dependencies.
Build: Makefile with gcc compiler.
Testing: Compatible with Unix-like systems; tested against bash behavior.
