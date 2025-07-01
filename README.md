# 👾 Pacman Console Game in C++

A simple **Pacman game** built using **C++** and **Object-Oriented Programming (OOP)** principles. This game runs in the console and features movement logic, collisions, lives, and a scoring system.

## 🎮 Features
- Control Pacman using `W`, `A`, `S`, `D` keys
- Objective: collect all the dots to win
- Avoid the ghost that moves randomly
- Lose a life when touching the ghost
- Game ends when all dots are collected or lives reach zero
- Console-based character display

## 🛠 Technologies
- Language: C++
- Concepts: Class Inheritance, Polymorphism, Dynamic Memory Management
- Platform: Console (cross-platform — uses `system("cls")` for Windows and `clear` for Linux/macOS)

## 🧱 OOP Structure
- `Character` (abstract class): base class for both `Pacman` and `Ghost`
- `Dot`: collectible point objects
- `Pacman`: the main player with score and life management
- `Ghost`: randomly moving enemy

## 🚀 How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/pacman-cpp.git
   cd pacman-cpp
2. Compile using g++:
   g++ pacman.cpp -o pacman
   ./pacman
