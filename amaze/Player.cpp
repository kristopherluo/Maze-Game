//
// Player.cpp
//
// Player class definition for maze game
// CPSC 1070
// Donald H. House, 10/21/2019
//

#include "Player.h"
#include "ezdraw.h"

#include <cmath>
#include <iostream>

using namespace std;

// constructor: start with Player at an impossible position
Player::Player(){
  row = col = -1;
  health = 3;
  newKeys.movenumber = 0;
}

// position the Player
void Player::SetPosition(int r, int c){
  row = r;
  col = c;
}

// get the Player position
void Player::GetPosition(int &r, int &c) const{
  r = row;
  c = col;
}

void Player::Move(DoorType d, const Room &room){
  if(room.IsDoor(d)){
    if(d == dleft){
      col--;
      newKeys.push(0);
    }
    else if(d == dright){
      col++;
      newKeys.push(1);
    }
    else if(d == ddown){
      row--;
      newKeys.push(2);
    }
    else if(d == dup){
      row++;
      newKeys.push(3);
    }else{
      cerr << "invalid door type: " << d << endl;
      exit(6);
    }
  }
}
// undo and hyperspeed function
void Player::UndoHyper(NewMove m, Room *rooms, int mazecols){
  if(m == undo){                  // undo player move code
    if(newKeys.pop(0) == 0){
      newKeys.pop(1);
      col = col + newKeys.pop(2);
    }
    else if(newKeys.pop(0) == 1){
      newKeys.pop(1);
      col = col - newKeys.pop(2);
    }
    else if(newKeys.pop(0) == 2){
      newKeys.pop(1);
      row = row + newKeys.pop(2);
    }
    else if(newKeys.pop(0) == 3){
      newKeys.pop(1);
      row = row - newKeys.pop(2);
    }
  }
// hyperspeed move code
  else if(m == hyperspeed){ //undo's while countdoors is greater than 2
    while((rooms[row * mazecols + col].CountDoors()) > 2){
      if(newKeys.pop(0) == 0){
        newKeys.pop(1);
        col = col + newKeys.pop(2);
      }
      else if(newKeys.pop(0) == 1){
        newKeys.pop(1);
        col = col - newKeys.pop(2);
      }
      else if(newKeys.pop(0) == 2){
        newKeys.pop(1);
        row = row + newKeys.pop(2);
      }
      else if(newKeys.pop(0) == 3){
        newKeys.pop(1);
        row = row - newKeys.pop(2);
      }
    }
    GetPosition(row, col);
    while((rooms[row * mazecols + col].CountDoors()) < 3 && newKeys.movenumber != 0){ //undo's while countdoors is less than 3 or in start position
      if(newKeys.pop(0) == 0){
        newKeys.pop(1);
        col = col + newKeys.pop(2);
      }
      else if(newKeys.pop(0) == 1){
        newKeys.pop(1);
        col = col - newKeys.pop(2);
      }
      else if(newKeys.pop(0) == 2){
        newKeys.pop(1);
        row = row + newKeys.pop(2);
      }
      else if(newKeys.pop(0) == 3){
        newKeys.pop(1);
        row = row - newKeys.pop(2);
      }
    }
  }
}



// get the Player's row
int Player::Row() const{
  return row;
}

// get the Player's column
int Player::Col() const{
  return col;
}

void Player::SetSize(int size){
  roomsize = size;
}

void Player::SetTextureID(int texid){
  texture = texid;
}

// player draw function
void Player::Draw(int width, int height) const{
  EZ_Rect playerrect;
  playerrect.x = (width/2) - 50;
  playerrect.y = (height/2) - 50;
  playerrect.w = playerrect.h = 100;

  EZ_DrawTexture(texture, NULL, &playerrect); // draws player in center of screen
}

int Player::GetHealth() const{
  return health;
}

// changes health by the value of "change" parameter
void Player::ChangeHealth(int change){
  health += change;
}
