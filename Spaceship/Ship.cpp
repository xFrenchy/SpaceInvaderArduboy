#include "Ship.h"

//spawn and update ship based on current coordinates, draws the health, armor, score, and current level as well
void Ship::drawShip(Arduboy2 arduboy)
{
	if(lifeRemaining > 0){
		Sprites::drawPlusMask(x,y,Spaceship,0); //(x,y,image,frame)
		for(int8_t i = 0; i < lifeRemaining; i++)
		{
			Sprites::drawPlusMask(117,0 + (i*10),Health, 0);  
		}
		Sprites::drawPlusMask(100, 54, Armor, 0);
		arduboy.setCursor(110,56);
		arduboy.print(armor);
		arduboy.setCursor(110,40);
		arduboy.print(score);
		arduboy.setCursor(0,56);
		arduboy.print(currentLevel);
    }
}


void Ship::shipAttack()
{
	//spawn a lazer right in front of the ship using the coordinates of it
	Sprites::drawPlusMask(x+3, y - 1, Lazer, 0);  //+3 is needed for the middle
	//The lazer has been spawned for this frame but will be lost as soon as we clear it, so we add the coordinates to an array
	//increment the coordinates and redraw them every frame so that it appears to be moving across the screen every frame
	Pair cord(x+3, y - 1);
	lazers.push_back(cord);
}//end of ship attack function


//Allows the ship to be moved with arrows and updates the collision box
void Ship::shipMovement(Arduboy2 arduboy)
{    
  if(arduboy.pressed(LEFT_BUTTON) && x > 0){
    x -= 2;
    if(x < 0){
      x = 0;
    }
  }
  if(arduboy.pressed(RIGHT_BUTTON) && (x + SHIP_WIDTH) < 127){
    x += 2;
    if(x > 127){
      x = 127;
    }
  }
  if(arduboy.pressed(UP_BUTTON) && y > 0){
    y -= 1;
    if(y < 0){
      y = 0;
    }
  }
  if(arduboy.pressed(DOWN_BUTTON) && y + SHIP_HEIGHT < 63){
    y += 1;
    if(y > 63){
      y = 63;
    }
  }
  //movement has ended here, update collision box
  hitBox.x = x;
  hitBox.y = y; 
  hitBox.width = SHIP_WIDTH;
  hitBox.height = SHIP_HEIGHT;
}//end of ship movement function


void Ship::damageTaken(int damage)
{
  armor -= damage;
  if(armor < 0){  //ship has taken too much damage and we lost a life
    lifeRemaining -= 1;
    armor = 100;
  }
}


void Ship::regenerate()
{
  armor++;
  if(armor >= 100){
    armor = 100;
  }
}


void Ship::reset()
{
  x = random(0,128);
  y = random(50,54);
  delete lazers.vecPtr;
  currentLevel = 1;
  lifeRemaining = 3;
  armor = 100;
  score = 0;
}
