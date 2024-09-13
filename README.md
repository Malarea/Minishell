# Minishell

### Description
**Minishell** is a minimalistic Unix shell created as part of the École 42 curriculum. It replicates the core functionalities of a real shell, including executing commands, handling pipes, redirections, and job control (background and foreground processes). This project aims to deepen understanding of process management, signal handling, and low-level system calls in Unix-based operating systems.

### Features
- Execution of built-in commands and external programs
- Support for:
  - **Pipes** (`|`)
  - **Redirections** (`>`, `>>`, `<`)
  - **Environment variables** (`$VAR`)
  - **Job control** (foreground/background tasks)
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
- Error handling and proper memory management

### Installation
Clone the repository and compile it:

```bash
git clone https://github.com/Malarea/minishell.git
cd minishell
make
```

### Usage
Run **Minishell** by executing the compiled binary:

```bash
./minishell
```

You can then use it as a regular shell to run commands:

```bash
$ echo "Hello, World!"
$ ls | grep minishell > output.txt
$ cat output.txt
```

### Example
Here’s an example of a pipeline:

```bash
$ ls -l | grep minishell | wc -l
```

Let me know if you'd like any modifications!
