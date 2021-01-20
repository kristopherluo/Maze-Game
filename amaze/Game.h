//
// Game.h
//
// Maze class declaration for maze game
// CPSC 1070
// Donald H. House, 10/21/2019
//


#ifndef _GAME_H
#define _GAME_H

#include "Room.h"
#include "Player.h"
#include <fstream>
#include "ezdraw.h"

using namespace std;

class Game{
private:


public:
  Game();         // constructor, load grid from disk file
  ~Game();        // destructor, delete allocated memory
