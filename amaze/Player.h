//
// Player.h
//
// Player class declaration for maze game
// CPSC 1070
// Donald H. House, 10/21/2019
//
#ifndef _PLAYER_H
#define _PLAYER_H

#include "Room.h"
#include <iostream>

using namespace std;

struct stack{
  int movenumber;
  int moves[1000];

  void push(int value){
      if(movenumber == -1){
        moves[movenumber + 2] = value;
        movenumber +=2;
      }
      else{
        moves[movenumber + 1] = value;
        movenumber++;
      }
  }

  int pop(int tf){
    if(movenumber >= 0){
      if(tf == 0){
        return moves[movenumber];
      }
      else if(tf == 1){
        movenumber--;
      }
      else if(tf == 2){
        return 1;
      }
    }else
      return 0;
    return movenumber;
  }
};

class Player{
private:
  int row, col;
  int roomsize;
  int texture;
  int health;

  stack newKeys;
public:
  Player();					// constructor, start with Player empty

  void SetPosition(int r, int c);
  void GetPosition(int &r, int &c) const;

  void Move(DoorType d, const Room &room);
  void UndoHyper(NewMove m, Room *rooms, int mazecols);

  int Row() const;
  int Col() const;

  void SetSize(int size);
  void SetTextureID(int texid);
  void Draw(int width, int height) const;

  int GetHealth() const;
  void ChangeHealth(int change);
};

#endif
