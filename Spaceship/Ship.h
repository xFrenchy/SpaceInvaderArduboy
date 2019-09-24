//File for spaceship properties

#ifndef	SPACESHIP_H
#define SPACESHIP_H

#include <Arduboy2.h>
#include "Pair.h"
#include "Myvector.h"
#include "Sprites.h"

#define SHIP_WIDTH 10
#define SHIP_HEIGHT 10

class Ship{
	public:
		int8_t x = random(0,128);
		int8_t y = random(50,65);
		MyVector lazers;  //A vector of pairs
		int8_t currentLevel = 1;
		Rect hitBox;
		int8_t lifeRemaining = 3;
		int8_t armor = 100;
		int score = 0;  //int is 2 bytes, -32,768 to 32,767
		//there will be a variable for powerups that affect the type of attack the ship will do

		//spawn and update ship based on current coordinates, draws the health, armor, score, and current level as well
		void drawShip(Arduboy2 arduboy);
		//Function that allows the ship to send out projectiles
		void shipAttack();
		//Movement of the ship
		void shipMovement(Arduboy2 arduboy);
		//calculates the damage taken
		void damageTaken(int damage);
		//regens armor
		void regenerate();
		//resets the variables to play again
		void reset();
};
#endif
