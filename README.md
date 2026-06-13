# Sudoku (Qt + C++)

A lightweight desktop Sudoku application implemented in C++ with a Qt Widgets GUI. The program generates puzzles at three difficulty levels and provides an animated backtracking solver with adjustable speed.

## Features

- Puzzle generation with a single-solution guarantee
- Three difficulty levels: Easy, Medium, Hard
- Animated computer solver (incremental updates to the GUI)
- Simple runtime checks and small test suite executed at startup

## Technologies

- C++ (standard library)
- Qt Widgets (Qt 5 or Qt 6)

## Repository layout

- main.cpp — program entry point (runs tests then opens UI)
- UserInterface.h / UserInterface.cpp — GUI, table drawing, animation, input handling
- Controller.h / Controller.cpp — generator, solver and validation logic
- Board.h / Board.cpp — simple 9x9 board model
- Tests.h / Tests.cpp — lightweight tests called on startup

## Quick start (Windows / Visual Studio)

Prerequisites

- Visual Studio (recommended) with C++ workload
- Qt (Qt Widgets) installed and configured for Visual Studio (Qt VS Tools or matching kit)

Steps

1. Open the project: open Sudoku.vcxproj in Visual Studio.
2. Ensure the project uses a Qt kit (configure Qt VS Tools or include/lib paths).
3. Build the solution (Build → Build Solution).
4. Run the application (Start). The small test suite runs first, then the UI opens.

## Usage

- Use the Easy / Medium / Hard buttons to generate a puzzle.
- Press "Computer" to start the animated solver; adjust speed with the slider.
- Use "Check" to validate your filled cells against the generated puzzle.

