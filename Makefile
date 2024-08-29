# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iinclude
LDFLAGS = -lSDL2 -lSDL2_mixer

# Source and object files
SRCS = src/main.c src/init.c src/events.c src/render.c src/cleanup.c src/player.c src/maze.c src/sound.c
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = maze_game

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild the project
rebuild: clean all
