# C Data Processor & Indexer

## 📌 Overview
This project is a high-performance data processing application built in C. It was designed to parse, index, and analyze large datasets—specifically the Brazilian Table of Food Composition (TACO). The system demonstrates advanced usage of pure data structures, manual memory management, and custom sorting algorithms without relying on external libraries.

## 🚀 Key Features

* **Custom Data Structures:** Implementation of Linked Lists and Binary Search Trees (BST) from scratch to handle dynamic data insertion and retrieval.
* **Algorithmic Efficiency:** Custom implementations of sorting algorithms optimized for memory efficiency, using pointers to avoid unnecessary data replication.
* **Dynamic Memory Management:** Strict and safe memory allocation using `malloc`, `calloc`, `realloc`, and `free` to prevent memory leaks during execution.
* **File I/O Operations:** Capable of parsing raw text/CSV files and persisting data efficiently into binary formats (`dados.bin`).
* **Modular Architecture:** The codebase is strictly organized into header (`.h`) and implementation (`.c`) files to prevent code duplication and maintain a clean architecture.

## 🧠 Technical Architecture

The application handles 597 food items categorized into 15 distinct groups. The internal architecture relies on:
1. **Linked Lists:** To dynamically manage the variable number of categories and the foods within them, keeping them alphabetically sorted.
2. **Binary Trees:** For each category, two separate Binary Trees index the food items based on their Energy (Kcal) and Protein (g) values, allowing for fast queries (e.g., finding foods within a specific nutritional range).

## 🛠️ Technologies & Concepts
* **Language:** C
* **Core Concepts:** Pointers, Dynamic Memory Allocation, Structs, Enums, File I/O (Binary & Text).
* **Data Structures:** Linked Lists, Binary Search Trees.

## ⚙️ How to Run

1. Clone this repository:
```bash
git clone https://github.com/gabamaral13/c-data-indexer.git
```

2. Navigate to the project directory and create a build folder:
```bash
cd c-data-indexer
mkdir build && cd build
```

3. Generate the build files and compile using CMake:
```bash
cmake ..
make
```

4. Execute the program:
```bash
./your_executable_name
```
