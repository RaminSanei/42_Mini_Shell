# 🐚 42_Mini_Shell

A minimalistic Unix shell implemented in **C** as part of the 42 School curriculum.  
This project replicates core shell functionalities, giving hands-on experience with system-level programming and process management.

---

## ✨ Features

- ⚡ **Command Execution**: Supports execution of commands with or without arguments.  
- 🛠️ **Built-in Commands**: Implements essential shell built-ins like `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.  
- 🔄 **Pipes & Redirections**: Handles piping (`|`) and redirection (`<`, `>`, `>>`) of standard input/output.  
- 🌐 **Environment Variables**: Manages variables and supports `$VAR` expansions.  
- 🛎️ **Signal Handling**: Properly handles signals like `SIGINT` (Ctrl+C) and `SIGQUIT`.  
- 📜 **Command History**: Maintains a history of previously executed commands.  
- 📝 **Quoting Mechanisms**: Supports single (`'`) and double (`"`) quotes for grouping arguments.  
- ✅ **Exit Status**: Implements `$?` to return the exit status of the last executed command.  

---

## 🛠️ Installation

1. **Clone the repository**:

```bash
git clone https://github.com/RaminSanei/42_Mini_Shell.git
```

2. **Navigate into the project directory**:

```bash
cd 42_Mini_Shell
```

3. **Compile the project using the Makefile**:

```bash
make
```

4. **Run the shell**:

```bash
./minishell
```

---

## 💻 Usage

- Upon running, the shell will display the prompt `>msh`.  
- Enter commands as you would in a normal terminal.  
- To exit the shell, type `exit`.  

---

## 🤝 Contributing

Contributions are welcome! Please fork the repo, create a branch, and submit a pull request.  

---

## 📜 License

This project is licensed under the 42 School's internal license agreement.
