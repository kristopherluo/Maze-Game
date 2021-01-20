//
// Maze.h
//
// Maze class declaration for maze game
// CPSC 1070
// Donald H. House, 10/21/2019
//

#ifndef _MAZE_H
#define _MAZE_H

#include "Room.h"
#include "Player.h"
#include <fstream>
#include "ezdraw.h"

using namespace std;

class Maze{
private:
  int nrows, ncols;
  int roomsize;

  int win; //win condition variable

  int doorwidth; //helps with drawing doors and other images
  int doorheight;

  Room *maze;    // 2D array for maze, to be allocated
  
  int startrow, startcol;
  int goalrow, goalcol;

  Player player;

  void AllocateMaze();
  void MakeDoors();

  void SetRoomSize(int s);

  // arrays to hold pointers to the images, and the texture ID's
  EZ_Image *images[PLAYER + 1];
  int textures[PLAYER + 1];

public:
  Maze();         // constructor, load grid from disk file
  ~Maze();        // destructor, delete allocated memory

  int GetWin() const;

  void SizeWindow(int maxwidth, int &winwidth, int &winheight);

  int GetRoomSize() const;

  void Load(const char *mazefilename);

  void MakeTextures();

  int Rows() const;
  int Cols() const;

  Room GetRoom(int row, int col) const;

  int StartRow() const;
  int StartCol() const;

  int GoalRow() const;
  int GoalCol() const;

  // player is moved via the "wasd" keys, w - up, a - left, s - down, d - right
  void MovePlayer(unsigned char ch);

  void Draw() const;

  friend std::ostream &operator<<(std::ostream &os, const Maze &m);
};

#endif
