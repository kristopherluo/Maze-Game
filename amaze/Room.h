//
// Room.h
//
// Room class declaration for maze game
// CPSC 1070
// Donald H. House, 10/21/2019
//

#ifndef _ROOM_H_
#define _ROOM_H_

// All of the door types enumerated
enum DoorType{dleft, dright, ddown, dup};
// New Move types
enum NewMove{undo, hyperspeed};
// All of the room types enumerated
enum RoomType{WALL, START, CORRIDOR, GOAL, BOSS, HEALTH, DOOR, PLAYER};

class Room{
private:
  RoomType type;    // kind of room
  bool doors[4];    // true if there is a door
  int roomsize;
  int texture;

public:
  Room();           // constructor, start with room empty

  void SetType(char ch);
  RoomType Type() const;

  void MakeDoor(int dx, int dy);
  bool IsDoor(DoorType d) const;

  bool GetDoor(int side) const;
  int CountDoors() const;

  void SetSize(int size);
  void SetTextureID(int texarray[]);
  int GetTextureID() const;

  void Draw(int width, int height) const;
};

#endif
