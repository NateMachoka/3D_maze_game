# 3D Maze Game: The Maze

A captivating 3D maze exploration game built using C, SDL2, and raycasting techniques (some aspects will be improved by OpenGL). Navigate an ancient Mayan-inspired maze in first-person view.

## Project Overview

The Maze is a 3D first-person maze game designed to challenge your navigation skills and immerse you in a mysterious environment. Initially starting as a 2D maze, it has evolved into a fully immersive 3D experience using raycasting techniques. The game challenges players to navigate through complex maze structures within a given time limit, with future plans to introduce traps, enemies, weapons, and other interactive elements as the development progresses.

## Features

- **2D Maze Exploration**: Start with a 2D top-down view of the maze.
- **First-Person Perspective**: Transition into a 3D first-person perspective using raycasting for enhanced immersion.
- **Player Movement**: Use the WASD keys to navigate the maze.
- **Sound Effects**: Enjoy a dynamic sound experience as you explore.
  - *Start Sound*: `start_sound.wav` plays when the game begins.
  - *Congratulations Sound*: `congrats_sound.wav` plays upon maze completion.
- **Dynamic Rendering**: Smooth rendering of the environment using SDL2.
- **Basic Trap Interaction (Planned)**: Enemies and other dynamic elements will be introduced in future updates.

[Deployed game](https://www.youtube.com/watch?v=I0QVUDr8rtU)

[Blog Article](#add-blog-link-when-finished)

## Project structure

3d_maze_game/<br>
├── assets/               # Game assets (textures, sounds, fonts, etc.)<br>
│   ├── Mayan_goddess     # Textures related to the Mayan goddess<br>
│   ├── Mayan_wall        # Wall textures for the maze<br>
│   ├── Surabanglus.ttf   # Font used in the game<br>
│   ├── congrats_sound.wav # Sound effect for game completion<br>
│   ├── congrats_sound.wav~# Backup/hidden version of the sound file<br>
│   ├── floor_plan        # Image/asset related to the maze's floor plan<br>
│   ├── mesy_guako.ttf    # Additional font used in the game<br>
│   ├── mesy_guako.zip    # Compressed version of mesy_guako.ttf<br>
│   ├── start_sound.wav   # Sound effect for game start<br>
│   ├── start_sound.wav~  # Backup/hidden version of the start sound<br>
│   └── ...               # Other potential assets<br>
├── include/              # Header files (definitions and declarations)<br>
│   ├── KHR/              # Khronos OpenGL headers<br>
│   ├── cleanup.h         # Header for cleanup functions<br>
│   ├── config.h          # Game configuration settings<br>
│   ├── create_maze.h     # Functions for maze generation<br>
│   ├── events.h          # Event handling declarations<br>
│   ├── glad.h            # OpenGL function loader<br>
│   ├── init.h            # Initialization functions for the game<br>
│   ├── main.h            # Main game definitions and structures<br>
│   ├── maze.h            # Maze-related logic and structures<br>
│   ├── player.h          # Player-related functions and variables<br>
│   ├── raycasting.h      # Raycasting functions for 3D rendering<br>
│   ├── render.h          # Rendering functions for the maze<br>
│   ├── sound.h           # Sound management functions<br>
│   ├── texture_utils.h   # Utility functions for handling textures<br>
│   └── timer.h           # Timer utility functions<br>
├── src/                  # Source code files<br>
│   ├── main.c            # Entry point of the game application<br>
│   └── ...               # Additional source code files<br>
├── build/                # Compiled binaries and object files<br>
├── .gitignore            # Git ignore file to exclude unnecessary files<br>
├── Makefile              # Makefile to build the project<br>
├── README.md             # Project documentation (this file)<br>
└── LICENSE               # License information for the project<br>


## Challenges and Solutions

1. **Raycasting the Mayan Wall Texture Sharpness, Depth, and Removing the Fish-Eye Effect**

-   **Challenge**: The walls appeared blurry and lacked depth, with a fish-eye effect at certain angles.<br>
-   **Solution**: Optimized the raycasting technique by adding vertical resolution functionality, improving wall clarity, and enhancing player movement calculations.

2. **Maze Going Out of Bounds and Rendering Issues**
-   **Challenge**: The maze occasionally exceeded its bounds, causing rendering glitches.<br>
-   **Solution**: I added boundary checks for both vertical and horizontal alignment to ensure that all wall edges are clearly rendered and do not exceed the screen boundaries, which improved the clarity and accuracy of the map.

3. **Creating a Good Static 2D Map That’s Immersive and Challenging**

   **Challenge**: The static 2D map lacked immersion and complexity, which made gameplay feel repetitive.<br>
   **Solution**: I replaced the static map with a dynamic one, using DFS and BFS algorithms to generate procedurally designed mazes. This improved both the immersion and the challenge by ensuring that no two mazes are identical.


## Installation

   **To run the Mayan Maze Adventure on your local machine, follow these step**:
Clone the repository:<br>
git clone https://github.com/NateMachoka/3D_maze_game.git

Navigate to the directory:<br>
cd 3D_maze_game

Install SDL2 and required dependencies<br>
Ensure you have SDL2 and related libraries installed on your system.

  **For Ubuntu users**:
Update your package lists: sudo apt-get update

Install SDL2: sudo apt-get install libsdl2-dev

Install SDL2 Image: sudo apt-get install libsdl2-image-dev

Install SDL2 Sound (Mixer): sudo apt-get install libsdl2-mixer-dev

Install SDL2 Font: sudo apt-get install libsdl2-ttf-dev

**Build the project: Run the Makefile to compile the source code**
   *make*<br>
   *Run the game*:./maze_game

Once the game is launched, navigate through the maze using the following controls:

W or UP Key: Move forward<br>
S or DOWN Key: Move backward<br>
A or LEFT Key: Turn left<br>
D or RIGHT Key: Turn right<br>
Press X: Exit the game

I'll add side quests to find hidden Mayan artifacts while exploring the maze, with various challenges and dynamic sounds enriching the experience.

## Contributing
   **We welcome contributions to improve and expand the Mayan Maze Adventure**

If you're interested in adding features, fixing bugs, or enhancing the design, follow these steps:

Fork the repository.<br>
Create a new branch for your feature or bug fix.<br>
git checkout -b feature_branch<br>
Commit your changes.<br>
git commit -m "Add feature"<br>
Push to the branch.<br>
git push origin feature_branch<br>
Open a pull request.

We’ll gladly review any contributions! Let's expand this world.
