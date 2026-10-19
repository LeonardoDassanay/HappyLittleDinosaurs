# Happy Little Dinosaurs — University Edition (C)

A terminal-based, multiplayer card game written in **C** for a university programming assignment at the University of Cagliari. Inspired by *Happy Little Dinosaurs*, this adaptation uses a university theme: players collect **CFU (university credits)** while facing obstacles inspired by student life.

## Overview

Players take turns drawing and playing cards, facing a randomly selected obstacle each round. Cards have credit values and different effects, while each player's character has bonuses or penalties depending on the obstacle category. The game tracks players' accumulated credits and declares a winner when someone reaches **60 CFU**.

## Technical highlights

- **C99** implementation with a text-based interface.
- **Linked lists and dynamic memory allocation** for players and card decks.
- **Structures and enumerations** to represent players, characters, cards, obstacles, and effects.
- **File input** to load characters, cards, and obstacles from `.txt` files.
- **Randomised decks**, turn-based interactions, and score calculation.
- Code separated into modules for players, CFU cards, and obstacle cards.

## Build and run

Requirements: a C99 compiler and **CMake 3.26 or newer**.

From the directory containing `CMakeLists.txt`:

```bash
cmake -S . -B build
cmake --build build
```

Run the generated executable from the build directory:

```bash
./build/progetto2
```

On Windows, the executable may be named `progetto2.exe`, and its location can depend on the CMake generator.

The CMake configuration copies the required game-data files (`carte.txt`, `ostacoli.txt`, `personaggi.txt`) into the build directory.

## Project structure

```text
main.c              # Main game loop and turn handling
giocatori.c/.h       # Players, characters, and scoring
carteCfu.c/.h        # CFU cards and deck operations
carteOstacolo.c/.h   # Obstacles and their deck
carte.txt           # Card definitions
ostacoli.txt        # Obstacle definitions
personaggi.txt      # Character definitions
CMakeLists.txt       # Build configuration
```

## Academic context

Developed as a **Programming 1 university project**. The goal was to practise procedural programming, pointers, linked data structures, dynamic memory management, file handling, and modular C code through a playable card-game application.

> **Note:** This is an educational, unofficial adaptation inspired by *Happy Little Dinosaurs*, not an official implementation or commercial product. The repository reflects a student project rather than production-ready software.

