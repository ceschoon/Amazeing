# Amazeing
Game about maze solving

You are the red dot and have to join the funny red symbol (pseudo hilbert curve of order 2) in the least amount of time. 

![alt text](Screenshot.png?raw=true "Screenshot")

Options given by passing the "--help" argument:		./Maze-Generator --help

To generate a 101x101 labyrinth: ./Maze-Generator --mazeSizeX=101 --mazeSizeY=101

Currently, mazes are only genereted by a recursive method.

Each maze is generated from a seed that can be used to regenerate it.

Some controls to use in the window:
- Left/Right/Up/Down				to move in the maze
- LControl + Left/Right/Up/Down		to move the view
- LControl + Add/Subtract			to zoom
- S									to show the seed that generated the maze

NB:	the seed and other info are printed in the console, you can redirect the output with: "./Amazeing >> logFile.log"
