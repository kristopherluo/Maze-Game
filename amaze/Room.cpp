//
// Room.cpp
//
// Room class definition for maze game
// CPSC 1070
// Donald H. House, 10/21/2019
//

#include "Room.h"
#include "ezdraw.h"

#include <iostream>
using namespace std;

//
// constructor: by default, room is a wall with no doors or texture
//
Room::Room(){
  type = WALL;
  texture = 0;

  for(int i = dleft; i <= dup; i++)
    doors[i] = false;
}

void Room::SetType(char ch){
  switch(ch){
      case 'w':
      type = WALL;
      break;
    case 's':
      type = START;
      break;
    case 'g':
      type = GOAL;
      break;
    case 'c':
      type = CORRIDOR;
      break;
    case 'h':
      type = HEALTH;
      break;
    case 'b':
      type = BOSS;
      break;
    default:
      cerr << "Illegal cell type: " << ch << endl;
  }
}

RoomType Room::Type() const{
  return type;
}

void Room::MakeDoor(int dx, int dy){
  if(dy == 0)
    doors[(dx + 1) / 2] = true;
  else
    doors[((dy + 1) / 2) + 2] = true;
}

bool Room::IsDoor(DoorType d) const{
  return doors[d];
}

bool Room::GetDoor(int side) const{
  return doors[side];
}

//function to return number of doors available
int Room::CountDoors() const{
  int count = 0;
  for(int i = 0; i < 4; i++){
    if(doors[i])
      count++;
  }
  return count;
}

void Room::SetTextureID(int texarray[]){
  texture = texarray[type];
}

int Room::GetTextureID() const{
  return texture;
}

void Room::SetSize(int size){
  roomsize = size;
}

//Room draw function
void Room::Draw(int width, int height) const{
  EZ_Rect roomrect;

  roomrect.x = 0;
  roomrect.y = 0;
  roomrect.w = width;
  roomrect.h = height;
  EZ_DrawTexture(texture, NULL, &roomrect);
}
