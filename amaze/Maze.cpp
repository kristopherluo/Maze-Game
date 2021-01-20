//
// Maze.cpp
//
// Maze class definition for maze game
// DPA 4010/6010
// Donald H. House, 10/21/2019
//

#include "Maze.h"
#include "ezdraw.h"

#include <cstdlib>
#include <iostream>
#include <fstream>

// don't need iostream or using namespace std, since both in .h file

void Maze::AllocateMaze(){
  maze = new Room[nrows * ncols];
}

void Maze::MakeDoors(){
  int dx, dy;

  for(int row = 0; row < nrows; row++){
    for(int col = 0; col < ncols; col++){
      dy = 0;
      for(dx = -1; dx <= 1; dx += 2)
        if(col + dx >= 0 && col + dx < ncols && maze[(row + dy) * ncols + (col + dx)].Type() != WALL)
          maze[row * ncols + col].MakeDoor(dx, dy);

      dx = 0;
      for(dy = -1; dy <= 1; dy += 2)
        if(row + dy >= 0 && row + dy < nrows && maze[(row + dy) * ncols + (col + dx)].Type() != WALL)
          maze[row * ncols + col].MakeDoor(dx, dy);
    }
  }
}

void Maze::SetRoomSize(int s){
  roomsize = s;
}

// constructor: start with no grid for the maze
Maze::Maze(): nrows(0), ncols(0), roomsize(50), win(0), doorwidth(0), doorheight(0), maze(NULL), startrow(-1),
              startcol(-1), goalrow(-1), goalcol(-1){
}

// destructor: delete the memory allocated for the maze
Maze::~Maze(){
  delete []maze;
}

//
// Establish the initial window width and height to have
// the same aspect ratio as the game rows and columns, given
// the maximum allowable width of the window
//
void Maze::SizeWindow(int maxwidth, int &winwidth, int &winheight){
  int cellsize = maxwidth / ncols;

  winheight = cellsize * nrows;
  winwidth = cellsize * ncols;

  doorwidth = winwidth;
  doorheight = winheight;

  SetRoomSize(cellsize);
  for(int row = 0; row < nrows; row++)
    for(int col = 0; col < ncols; col++)
      maze[row * ncols + col].SetSize(cellsize);
  player.SetSize(cellsize);
}

int Maze::GetRoomSize() const{
  return roomsize;
}

// Load in the maze description and the images from the
// data in the maze description file
void Maze::Load(const char *mazefilename){
  // open the maze description file
  ifstream mazefile;
  mazefile.open(mazefilename);
  if(!mazefile.is_open()) {
    cerr << "Unable to open maze file " << mazefilename << endl;
    exit(1);
  }

  // load the images from the names in the maze description file
  char imagenames[8][100];
  for(int i = WALL; i <= PLAYER; i++){
    mazefile >> imagenames[i];
    if(mazefile.eof()){
      cerr << "Error reading image filename from " << mazefilename << endl;
      exit(2);
    }
  }
  // load each image
  for(int i = WALL; i <= PLAYER; i++){
    images[i] = EZ_LoadBMPImage(imagenames[i]);
    if(images[i] == NULL){
      cerr << "Invalid BMP image: " << imagenames[i] << endl;
      exit(3);
    }
  }

  // get the number of maze rows and columns, and allocate the maze
  mazefile >> nrows >> ncols;
  if(mazefile.eof()){
    cerr << "Error reading number of rows and columns from the mazefile " << mazefilename << endl;
    exit(4);
  }
  AllocateMaze();

  // load the maze from the maze description file, then close the file
  unsigned char ch;
  for(int row = nrows - 1; row >= 0; row--){
    for(int col = 0; col < ncols; col++){
      for(mazefile >> ch; !mazefile.eof() && isspace(ch); mazefile >> ch);
      if(mazefile.eof()){
        cerr << "Error reading the rooms from the mazefile " << mazefilename << endl;
        exit(5);
      }

      maze[row * ncols + col].SetType(ch);

      // record the starting room and set the player
      // in it
      if(maze[row * ncols + col].Type() == START){
        startrow = row;
        startcol = col;
        player.SetPosition(startrow, startcol);
      }

      // record the goal room
      if(maze[row * ncols + col].Type() == GOAL){
        goalrow = row;
        goalcol = col;
      }
    }
  }
  mazefile.close();

  // build doors in each non-wall room
  MakeDoors();
}

void Maze::MakeTextures(){
  for(int i = WALL; i <= PLAYER; i++)
    textures[i] = EZ_CreateTexture(images[i]);

  for(int row = 0; row < nrows; row++)
    for(int col = 0; col < ncols; col++)
      maze[row * ncols + col].SetTextureID(textures);

  player.SetTextureID(textures[PLAYER]);
}

int Maze::Rows() const{
  return nrows;
}

int Maze::Cols() const{
  return ncols;
}

Room Maze::GetRoom(int row, int col) const{
  return maze[row * ncols + col];
}

int Maze::StartRow() const{
  return startrow;
}

int Maze::StartCol() const{
  return startcol;
}

int Maze::GoalRow() const{
  return goalrow;
}

int Maze::GoalCol() const{
  return goalcol;
}

void Maze::MovePlayer(unsigned char ch){
  NewMove newMove;
  DoorType move;
  int row, col;
  player.GetPosition(row, col);

  if(ch == 'w')
    move = dup;
  else if(ch == 'a')
    move = dleft;
  else if(ch == 's')
    move = ddown;
  else if(ch == 'd')
    move = dright;
  else if(ch == 'u')
    newMove = undo;
  else if(ch == 'h')
    newMove = hyperspeed;
  else
    return;   // ignore characters other than w-a-s-d

// if player presses new keys (u and h), calls undohyper function in player
  if(ch == 'u')
    player.UndoHyper(newMove, maze, ncols);
  else if(ch == 'h')
    player.UndoHyper(newMove, maze, ncols);
  else  // if w a s d is pressed, calls move function in player
    player.Move(move, maze[row * ncols + col]);



  player.GetPosition(row, col);
// whenever player lands on boss or heart, room type is changed to corridor so no health is changed here
  if(maze[row * ncols + col].Type() == BOSS){
    player.ChangeHealth(-1);
    maze[row * ncols + col].SetType('c');
  }

  if(maze[row * ncols + col].Type() == HEALTH){
    player.ChangeHealth(1);
    maze[row * ncols + col].SetType('c');
  }

  if(maze[row * ncols + col].Type() == GOAL){ // when landed on goal win = 1 (game controls end)
    cout << "YOU WIN" << endl;
    win = 1;
  }

  if(player.GetHealth() == 0){ // when no health remains, win = 1 (game controls end)
    cout << "YOU LOSE" << endl;
    win = 1;
  }
}

// main draw function (calls other draw functions)
void Maze::Draw() const{
  int row, col;
  player.GetPosition(row, col);
  maze[row * ncols + col].Draw(doorwidth, doorheight);

  player.Draw(doorwidth, doorheight); // calls draw in player

  for(int i = 0; i < player.GetHealth(); i++){
    EZ_Rect heartrect;
    heartrect.x = 0 + (50 * i);
    heartrect.y = 0;
    heartrect.w = heartrect.h = 50;

    EZ_DrawTexture(textures[5], NULL, &heartrect); // draws heart count in bottom left corner
  }

// draws doors on sides allowed to walk
  if(maze[row * ncols + col].GetDoor(0)){
    EZ_Rect doorrect;
    doorrect.x = 50;
    doorrect.y = (doorheight/2) - 50;
    doorrect.w = doorrect.h = 100;

    EZ_DrawTexture(textures[6], NULL, &doorrect);
  }
  if(maze[row * ncols + col].GetDoor(1)){
    EZ_Rect doorrect;
    doorrect.x = doorwidth - 150;
    doorrect.y = (doorheight/2) - 50;
    doorrect.w = doorrect.h = 100;

    EZ_DrawTexture(textures[6], NULL, &doorrect);
  }
  if(maze[row * ncols + col].GetDoor(2)){
    EZ_Rect doorrect;
    doorrect.x = (doorwidth/2) - 50;
    doorrect.y = 50;
    doorrect.w = doorrect.h = 100;

    EZ_DrawTexture(textures[6], NULL, &doorrect);
  }
  if(maze[row * ncols + col].GetDoor(3)){
    EZ_Rect doorrect;
    doorrect.x = (doorwidth/2) - 50;
    doorrect.y = doorheight - 150;
    doorrect.w = doorrect.h = 100;

    EZ_DrawTexture(textures[6], NULL, &doorrect);
  }
}

int Maze::GetWin() const{
  return win;
}
