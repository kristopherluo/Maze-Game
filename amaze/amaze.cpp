//
// Sample C++ solution to HW5 to load a maze and move a player around in the maze
//
// CPSC 1070
// Donald H. House, 10/21/2019
// Clemson University
//

#include "ezdraw.h"
#include "Maze.h"
#include "Player.h"

#include <cstdlib>
#include <iostream>

using namespace std;

// Maximum width of the display window
#define MAXWINDOWWIDTH    900



// The maze object that drives everything
Maze TheMaze;

//
// This routine is called every 1/30 of a second as long as EZ Draw is running
// Clear the screen, draw the maze, and the player
//


void updateDisplay(){
  EZ_ClearDrawing();

    TheMaze.Draw();

  EZ_DisplayDrawing();
}

//
//  This routine is called every time a key is pressed on the keyboard
//  The player moves in response to the w-a-s-d keys. Other keys are ignored.
//
void handleKey(unsigned char key){
  if(TheMaze.GetWin() == 0) //stops move controls when game is won
    TheMaze.MovePlayer(key);
}

//
// main function that loads the images, starts EZ Draw,
// and creates textures for each image.
//
int main(int argc, char *argv[]) {
  if(argc != 2){
    cerr << "usage: buildmaze <mazefilename>" << endl;
    exit(1);
  }
  // Load the images, maze dimensions, and room layout
  TheMaze.Load(argv[1]);

  // open the EZ Draw window with proportions matching the maze proportions
  // let the Maze determine this so that it knows the size of a room
  int winwidth, winheight;
  TheMaze.SizeWindow(MAXWINDOWWIDTH, winwidth, winheight);
  EZ_Init(winwidth, winheight, "Maze Game");

  // Make one texture for each image
  TheMaze.MakeTextures();

  // event loop to drive the display at 30 updates per second,
  // and to respond to keyboard presses to move the character
  bool quit = false;
  while(!quit){
    quit = EZ_HandleEvents(updateDisplay, handleKey, NULL, NULL);
  }

  EZ_Quit();

  return 0;
}
