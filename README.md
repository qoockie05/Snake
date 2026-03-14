# **Snake Game in C++ with ncurses**

A simple terminal-based **Snake** game written in **C++** using the **ncurses** library.

This project runs in a Linux terminal and presents a classic Snake game implemented in an object-oriented way, based on a simple window system.

## **Requirements**

The program works on **Linux-based systems** and requires the **ncurses** development library.

Install it with:

```bash
sudo apt install libncurses-dev
```
Build and Run
Compile the project using:
```bash
g++ -o snake main.cpp screen.cpp snake.cpp winsys.cpp -lncurses
```
Run the game with:
```bash
./snake
```


## **Features**
-Help screen with controls
-Pause and resume
-Restart option
-Snake movement using arrow keys
-Wall wrapping from one side of the board to the other
-Random food generation
-Snake growth after eating food
-Level progression and increasing speed
-Game over screen with points

## **Controls**
r - restart game
p - pause / resume
h - show / hide help
q - quit game

Arrow keys - move the snake
