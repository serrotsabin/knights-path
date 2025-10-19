# Knight's Tour Problem
--------------------------
Overview:
- This program solves the Knight’s Tour problem using recursive depth-first search with backtracking. 
- The program inputs: 
    - Board size N (4 ≤ N ≤ 8) 
    - Starting knight position (row & column) 
    - Number of solutions
- The program attempts to find the requested number of tours where the knight visits every square exactly once.

Features:
- Handles board sizes from 4x4 up to 8x8.
- Finds multiple distinct solutions.
- Outputs the solutions in a file named "kp.out" as N x N matrices. 
- Each number indicates the order of the knight’s move starting from 0.
- The user specifies the number of solutions to generate and the starting position.

Limitations:
- For larger boards (close to 8x8), computation may be slow and can take couple of minutes.
- Uses pure DFS + backtracking only.

## Files
- `main.cpp` : entry point

## How to Compile

### Option 1: Using Makefile (recommended)
- On Linux/macOS:
  ```bash
  make
  ./main

- On Windows:
  mingw32-make
  main.exe

### Option 2: Manual Compilation
- On Linux/macOS:
  g++ -std=c++17 main.cpp -o main
  ./main

- On Windows:
  g++ -std=c++17 main.cpp -o main.exe
  main.exe

