# TicTacToe Console Game

> A simple Tic Tac Toe game in C for the console, with French/English language support and colored output (blue and red).

## Description

This program lets you play the classic Tic Tac Toe (also known as Noughts and Crosses) in a local two-player mode.  
- **Available languages**: French or English (select at startup).  
- **Colored display**: uses ANSI codes (blue for `X`, red for `O`).  
- **Score and history**: scores are tracked during the session, and an `historique.txt` file is created to log match results.

## Features

- Language selection (French/English).
- Prompts for player names (Player 1 = X, Player 2 = O).
- Displays the score (wins, losses, draws).
- Saves results in `historique.txt`.

## Requirements

- A C compiler (GCC, Clang, MinGW, etc.).
- A terminal that supports ANSI color codes (most modern terminals do).

## Installation

1. **Clone the repository** (or download the ZIP archive):
   ```bash
   git clone https://github.com/Brainfkt/TIC-TAC-TOE.git
   cd TIC-TAC-TOE
   ```

2. **Compile and execute the code:**
   
     Linux/Mac:
   ```bash
   gcc -o tictactoe tictactoe.c
   ./tictactoe
   ```
     Windows:
   ```bash
   gcc -o tictactoe.exe tictactoe.c
   tictactoe.exe
