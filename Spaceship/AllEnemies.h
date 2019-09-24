//File for ALL Enemy properties

#ifndef ENEMY_H
#define ENEMY_H

#include <Arduboy2.h>
#include "MyVector.h"
#include "Pair.h"
#include "Sprites.h"

enum class EnemyType
{
	regular,
	blob,
	twin,
	enemy
};



class Enemy
{
	public:
		int8_t x;
		int8_t y;
		bool alive;
		int8_t width;
		int8_t height;
		Rect hitBox;	//uses default constructor
		MyVector lazers;  //A vector of pairs | uses default constructor
		EnemyType type;
//----------------------------------------------------------------------------	
		//constructor
		Enemy() : x(0), y(0), alive(true), width(10), height(10), type(EnemyType::enemy){};
		//Setters
		void setType(EnemyType x) { type = x; }
		//Function that draws the enemy on screen if alive
		virtual void drawEnemy();
		//Function that randomly moves the enemy around and updates the hitBox if it moves
		virtual void movement();
		//Function that makes the enemy shoot lazers
		virtual void attack();
		//Function that initially spawns and uses fixed spawn points, should only be called once to spawn, also sets the x and y of this enemy based on spawn point
		virtual void spawn(Pair spawnPoint);
		//Function to call when an enemy dies, it iterates through the vector and deletes every element inside of it
		virtual void death();
};


class RegEnemy : public Enemy	//derived from Enemy
{
  public:
	  RegEnemy() { Enemy(); setType(EnemyType::regular); }
	  //spawn and update RegEnemy based on current coordinates
	  virtual void drawEnemy();
	  //Function that initially spawns and uses fixed spawn points, should only be called once to spawn, also sets the x and y of this enemy based on spawn point
	  virtual void spawn(Pair spawnPoint);
};


class BlobEnemy : public Enemy
{
	public:
		BlobEnemy() { Enemy(); setType(EnemyType::blob); }
		//spawn and update BlobEnemy based on current coordinates
		virtual void drawEnemy();
		//Function that initially spawns and uses fixed spawn points, should only be called once to spawn, also sets the x and y of this enemy based on spawn point
		virtual void spawn(Pair spawnPoint);
		//Function that makes the enemy shoot lazers
		virtual void attack();
};

class TwinEnemy : public Enemy
{
	public:
		TwinEnemy() { Enemy(); setType(EnemyType::twin); }
		//spawn and update TwinEnemy based on current coordinates
		virtual void drawEnemy();
		//Function that initially spawns and uses fixed spawn points, should only be called once to spawn, also sets the x and y of this enemy based on spawn point
		virtual void spawn(Pair spawnPoint);
		//Function that makes the enemy shoot double lazers
		virtual void attack();
};

#endif
