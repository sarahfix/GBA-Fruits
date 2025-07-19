# GBA-Fruits: A Game Boy Advance Game

A fruit-themed Game Boy Advance game developed in C, where players control a watermelon to catch falling fruit slices within a time limit, showcasing embedded systems programming and game development skills.

## Overview
GBA-Fruits is a fast-paced arcade game built for the Game Boy Advance using C and a Docker-based devkitARM toolchain. The player navigates a watermelon character to collect 20 fruit slices before time runs out, with intuitive controls and a win/lose screen displaying performance metrics. This project demonstrates proficiency in low-level programming, real-time input handling, sprite management, and containerized development environments.

- **Objective**: Collect 20 fruit slices to win; failure to do so within the time limit results in a loss.
- **Technologies**: C, devkitARM, Docker, mGBA (emulator).
- **Context**: Developed as a course project for CS 2110 at Georgia Institute of Technology.

## Features
- **Gameplay Mechanics**: Control a watermelon using arrow keys to catch falling fruit slices, with collision detection and a timer system.
- **Win/Lose Conditions**: Win by collecting 20 slices; lose if time expires before reaching the goal.
- **User Interface**: Displays a win screen with the time taken to collect 20 slices or a lose screen if unsuccessful.
- **Controls**:
  - **Enter**: Start the game.
  - **Arrow Keys**: Move the watermelon left or right.
  - **Backspace**: Exit the game.
- **Sprite and Animation**: Custom fruit slice sprites with smooth animations for engaging visuals.
- **Scoring System**: Tracks collected slices and displays results on the win screen.

## Installation and Setup
1. **Install Prerequisites**:
   - **Docker**: Install Docker Desktop for Windows[](https://www.docker.com/products/docker-desktop/).
   - **Java 11+**: Ensure Java 11 or higher is installed[](https://www.oracle.com/java/technologies/javase/jdk11-archive-downloads.html).
   - **GBA Emulator**: Download mGBA (recommended: https://mgba.io/) or VisualBoyAdvance.
2. **Clone the Repository**:
   ```bash
   git clone https://github.com/sarahfix/GBA-Fruits.git

## Run the Game
1. **Navigate to the project directory**
2. **Run the Docker script**
    - .\cs2110docker-gba.bat
    - run: make mgba

## Demo
<img src="screenshots/demo.png" alt="Gameplay Demo">

## Notes
- **Development**: Solo project, fully implemented game logic, rendering, and assets.
- **Context**: Created as a course project for CS 2110 at Georgia Tech to explore embedded systems and containerized development.
- **Academic Integrity**: This repository contains my original contributions and adheres to Georgia Tech’s honor code for sharing course-related work.
- **Future Improvements**:
  - Add difficulty levels with adjustable timers.
  - Implement additional fruit types and power-ups.
  - Enhance sound effects for immersive gameplay.