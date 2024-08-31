# 💻 Minishell

Welcome to **Minishell**! This project aims to create a mini version of a Unix shell, providing an educational and practical experience on the internal workings of a shell.

## 📋 Table of Contents

- [Introduction](#-introduction)
- [Features](#-features)
- [Installation](#-installation)
- [Usage](#-usage)
- [Built-in Commands](#-built-in-commands)
- [Bonus Features](#-bonus-features)
- [Technical Details](#-technical-details)

## 🌟 Introduction

**Minishell** is a simple shell implementation inspired by the basic functionalities of Unix shells like `bash`. The goal is to provide a minimalist environment to execute commands, handle redirections, and more.

## 🚀 Features

**Minishell** includes the following features:

- Display a prompt waiting for a command.
- Command history management.
- Execute commands based on the `PATH` variable or by specifying a relative/absolute path.
- Handle single and double quotes, environment variables, and special characters.
- Implement input/output redirections and pipelines.
- Basic built-in commands like `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- Signal handling for `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` as in `bash`.

## 🛠️ Installation

To install and run Minishell on your machine, follow these steps:

1. **Clone the repository:**
   ```bash
   git clone <repository-url>
   cd minishell
   ```
2. **compile the project:**
   ```bash
     make
   ```
3. **Run the shell:**
   ```bash
     ./minishell
   ```

### 🐳 Running with Docker

If you have Docker and Docker Compose installed, you can quickly test **Minishell** in an optimal environment by running:

   ```bash
   make docker
   ```

## 🎮 usage

Once you have compiled and launched **Minishell**, you will see a prompt similar to this:
```bash
user:/home/user$
```
You can start typing commands just like in a Unix shell. For example:
```bash
user:/home/user$ echo "Hello, world!"
Hello, world!
```

## 📜 Built-in Commands

**Minishell** supports the following built-in commands:

- **`echo`**: Prints text to the terminal. Supports the `-n` option to omit the trailing newline.
- **`cd`**: Changes the current directory.
- **`pwd`**: Prints the current working directory.
- **`export`**: Sets environment variables.
- **`unset`**: Unsets environment variables.
- **`env`**: Displays the current environment variables.
- **`exit`**: Exits the shell.

### Redirections and Pipelines

**Minishell** supports the following redirection operators:

- **`<`**: Redirects input.
- **`>`**: Redirects output (overwrite).
- **`>>`**: Redirects output (append).
- **`<<`**: Here document, where input is read until a delimiter is encountered.

Pipelines are supported via the `|` character, allowing you to chain commands by passing the output of one command as input to the next.

### Signal Handling

- **`Ctrl+C`**: Interrupts the current command and displays a new prompt.
- **`Ctrl+D`**: Exits the shell.
- **`Ctrl+\`**: Does nothing, matching `bash` behavior.

## ✨ Bonus Features

**Minishell** also includes features like:

- Logical operators **`&&`** and **`||`** for chaining commands with support for parentheses.
- Wildcard support (**`*`**) for pattern matching in the current working directory.

## ⚙️ Technical Details

- **Abstract Syntax Tree (AST)**: Minishell uses a binary tree-based AST to parse and organize commands. This structure is crucial for handling complex command sequences, like pipes and redirections, by ensuring the correct execution order and simplifying the parsing process.

- **Garbage Collector**: A custom garbage collector is implemented to manage dynamic memory allocation, preventing leaks. This is essential for maintaining performance and stability, especially as the shell processes multiple commands and builds the AST dynamically.

