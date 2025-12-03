# File System Simulator

A CLI-based hierarchical file system simulation implemented in C. This project demonstrates the usage of advanced data structures to manage directories and files efficiently in memory.

## 🚀 Features
* **Tree Structure:** Uses an **N-ary Tree** (represented via **Left-Child, Right-Sibling**) to allow unlimited subdirectories and files without fixed array limits.
* **CLI Interface:** Interactive command-line interface for user navigation.
* **Memory Management:** Dynamic memory allocation for nodes.
* **Recycle Bin:** Deleted files are moved to a **Queue** structure (Recycle Bin) before permanent deletion.
* **Fast Search:** Optimized search functionality using **Recursion** (DFS) and **Hash Tables**.

## 🛠 Supported Commands
* `mkdir [name]` : Create a new directory.
* `touch [name]` : Create a new file.
* `ls` : List contents of the current directory.
* `cd [name]` : Change directory (supports `..` for parent directory).
* `rm [name]` : Move a file/directory to the recycle bin.
* `search [name]` : Recursive search for a file in the entire tree.
* `tree` : Visualize the directory structure.

## 💻 How to Run
```bash
gcc main.c -o filesystem
./filesystem
