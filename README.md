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

## Project Structure

3d_maze_game/
├── assets/               # Game assets (textures, sounds, fonts, etc.)
│   ├── Mayan_goddess     # Unused texture (for now)
│   ├── Mayan_wall        # Wall textures for the maze
│   ├── Surabanglus.ttf   # Font used in the game
│   ├── congrats_sound.wav # Sound effect for game completion
│   ├── congrats_sound.wav~# Backup/hidden version of the sound file
│   ├── floor_plan        # Image/asset related to the maze's floor
│   ├── mesy_guako.ttf    # Additional font used in the game
│   ├── mesy_guako.zip    # Compressed version of mesy_guako.ttf
│   ├── start_sound.wav   # Sound effect for game start
│   ├── start_sound.wav~  # Backup/hidden version of the start sound
│   └── ...               # Other potential assets
├── include/              # Header files (definitions and declarations)
│   ├── KHR/              # Khronos OpenGL headers
│   ├── cleanup.h         # Header for cleanup functions
│   ├── config.h          # Game configuration settings
│   ├── create_maze.h     # Functions for maze generation
│   ├── events.h          # Event handling declarations
│   ├── glad.h            # OpenGL function loader
│   ├── init.h            # Initialization functions for the game
│   ├── main.h            # Main game definitions and structures
│   ├── maze.h            # Maze-related logic and structures
│   ├── player.h          # Player-related functions and variables
│   ├── raycasting.h      # Raycasting functions for 3D rendering
│   ├── render.h          # Rendering functions for the maze
│   ├── sound.h           # Sound management functions
│   ├── texture_utils.h   # Utility functions for handling textures
│   └── timer.h           # Timer utility functions
├── src/                  # Source code files
│   ├── main.c            # Entry point of the game application
│   └── ...               # Additional source code files
├── build/                # Compiled binaries and object files (generated after compilation)
├── .gitignore            # Git ignore file to exclude unnecessary files from the repository
├── Makefile              # Makefile to build the project
├── README.md             # Project documentation (this file)
└── LICENSE               # License information for the project


## Challenges and Solutions

1. **Raycasting the Mayan Wall Texture Sharpness, Depth, and Removing the Fish-Eye Effect**

   **Challenge**: The walls appeared blurry and lacked depth, with a fish-eye effect at certain angles.  
   **Solution**: Optimized the raycasting technique by adding vertical resolution functionality, improving wall clarity, and enhancing player movement calculations.
   **Code Snippet**

/* Calculate perpendicular wall distance */
		if (side == 0)
		{
			perpWallDist = (mapX - player->pos.x / tile_size + (1 - stepX) / 2) / rayDirX;
		}
		else
		{
			perpWallDist = (mapY - player->pos.y / tile_size + (1 - stepY) / 2) / rayDirY;
		}

		/* Calculate height of the wall slice to draw */
		lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);

		/* Calculate the top and bottom of the line */
		drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;


2. **Maze Going Out of Bounds and Rendering Issues**
   **Challenge**: The maze occasionally exceeded its bounds, causing rendering glitches.
   **Solution**: I added boundary checks for both vertical and horizontal alignment to ensure that all wall edges are clearly rendered and do not exceed the screen boundaries, which improved the clarity and accuracy of the map.
   **Code Snippet**
   **maze.c**
bool in_bounds(int x, int y)
   {
   return (x >= 0 && x < MAZE_WIDTH && y >= 0 && y < MAZE_HEIGHT);
   }

   **raycasting.c**
   * Perform DDA (Digital Differential Analyzer) to find the wall */
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (maze[mapY][mapX] > 0) hit = 1; /* Wall hit */
		}

3. **Creating a Good Static 2D Map That’s Immersive and Challenging**
   **Challenge**: The static 2D map lacked immersion and complexity, which made gameplay feel repetitive.
   **Solution**: I replaced the static map with a dynamic one, using DFS and BFS algorithms to generate procedurally designed mazes. This improved both the immersion and the challenge by ensuring that no two mazes are identical.
   **Code Snippet**
   **maze.c**
void carve_passages(int x, int y, int maze[MAZE_HEIGHT][MAZE_WIDTH])
{
	int i;
	int dx, dy, nx, ny;

	static const int directions[4][2] = {
		{ 0, 2 },  /* Down */
		{ 2, 0 },  /* Right */
		{ 0, -2 }, /* Up */
		{ -2, 0 }  /* Left */
	};
	int shuffled_directions[4][2];

	memcpy(shuffled_directions, directions, sizeof(directions));
	shuffle_directions(shuffled_directions);

	maze[y][x] = PATH;

	for (i = 0; i < 4; i++)
	{
		dx = shuffled_directions[i][0];
		dy = shuffled_directions[i][1];
		nx = x + dx;
		ny = y + dy;

		if (in_bounds(nx, ny) && maze[ny][nx] == WALL)
		{
			maze[ny - dy / 2][nx - dx / 2] = PATH; /* Carve through wall */
			carve_passages(nx, ny, maze);
		}
	}
}


## Installation

   **To run the Mayan Maze Adventure on your local machine, follow these step**:
Clone the repository:
git clone https://github.com/NateMachoka/3D_maze_game.git

Navigate to the directory:
cd 3D_maze_game

Install SDL2 and required dependencies
Ensure you have SDL2 and related libraries installed on your system.

  **For Ubuntu users**:
Update your package lists
sudo apt-get update

Install SDL2
sudo apt-get install libsdl2-dev

Install SDL2 Image
sudo apt-get install libsdl2-image-dev

Install SDL2 Sound (Mixer)
sudo apt-get install libsdl2-mixer-dev

Install SDL2 Font
sudo apt-get install libsdl2-ttf-dev

   **Build the project: Run the Makefile to compile the source code**
make

Run the game
./maze_game

Once the game is launched, navigate through the maze using the following controls:

W or UP Key: Move forward
S or DOWN Key: Move backward
A or LEFT Key: Turn left
D or RIGHT Key: Turn right
Press X: Exit the game

I'll add side quests to find hidden Mayan artifacts while exploring the maze, with various challenges and dynamic sounds enriching the experience.

## Contributing
   **We welcome contributions to improve and expand the Mayan Maze Adventure**

If you're interested in adding features, fixing bugs, or enhancing the design, follow these steps:

Fork the repository.
Create a new branch for your feature or bug fix.
git checkout -b feature_branch
Commit your changes.
git commit -m "Add feature"
Push to the branch.
git push origin feature_branch
Open a pull request.

We’ll gladly review any contributions! Let's expand this world.
