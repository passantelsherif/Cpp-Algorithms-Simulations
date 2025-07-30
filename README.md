# **C++ Programming Projects: Algorithms & Simulations**

## **Project 1: String Manipulation, Recursion, and Binary Utilities**
**File:** `A1_T1_25_20231036.cpp`

### **Features**

#### **String Splitting Function**
- Splits a given string into substrings based on a specified delimiter
- Returns a vector of substrings for further processing

#### **Teddy Bear Game (Recursive Puzzle)**
A mathematical game where the player tries to reduce a starting number of teddy bears to exactly 42 using specific rules:
- Divide by 2 (if even)
- Subtract the product of the last two digits (if divisible by 3 or 4)
- Subtract 42 (if divisible by 5)
- Uses recursion to explore possible paths to victory

#### **Binary Number Utilities**
- **Binary Conversion**: Converts a decimal number into its binary representation
- **Binary Generation**: Generates all possible binary numbers of a given length k with a specified prefix

#### **Phishing Email Scanner**
- Scans a text file (simulating an email) for common phishing keywords
- Assigns points based on keyword occurrences
- Calculates a total "phishing score"

## **Project 2: Game of Life Simulation**  
**File:** `GameOfLife.cpp`  

### **Rules**  
- **Underpopulation**: Live cells with <2 neighbors die  
- **Survival**: 2-3 neighbors → survives  
- **Overpopulation**: >3 neighbors → dies  
- **Reproduction**: Dead cells with 3 neighbors → revive  

### **Features**  
- 20x20 grid visualization (`*` = alive, `-` = dead)  
- Generational animation with console clearing  
- Interactive controls:  
  ```plaintext
  1. Start Simulation
  2. Exit
  3. Learn Rules

## **Key Programming Concepts Demonstrated**

- **Recursion**  
  - Teddy Bear Game  
  - Binary Generation  

- **String Manipulation**  
  - Splitting function  
  - Phishing Scanner  

- **Matrix Operations**  
  - Game of Life grid updates  

- **User Input Validation**  
  - Ensuring robust interactions  

- **File I/O**  
  - Reading/Writing email content for phishing scan  
