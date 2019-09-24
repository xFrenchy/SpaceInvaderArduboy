#include "AllEnemies.h"

//Function that draws the enemy on screen if alive
void Enemy::drawEnemy()
{
	Serial.print("Someone tried to draw an enemy!\n");
}


//Function that randomly moves the enemy around and updates the hitBox if it moves
void Enemy::movement()
{
  int8_t value = random(0-100); //this rolls between 0-99
  if(value >= 0 && value <= 4 && x > 0){ //5% chance
    x -= 3;
    if(x < 0){
      x = 0;
    }
  }//end of if going left
  if(value >= 5 && value <= 9 && (x + width) < 127){  //5% chance
    x += 3;
    if(x > 127){
      x = 127;
    }
  }//end of if going right
  if(value >= 10 && value <= 12 && y > 0){  //3% chance
    y -= 2;
    if(y < 0){
      y = 0;
    }//end of if going up
  }
  if(value == 13 && y + height < 63){  //1% chance
    y += 2;
    if(y > 63){
      y = 63;
    }
  }//end of if going down
  //else it has a 86% chance of not moving every frame
  //at this point the enemy has moved and we must update it's hitBox(even if it hasn't moved)
  hitBox.x = x;
  hitBox.y = y;
  hitBox.width = width;
  hitBox.height = height;
}//end of Enemy movement


//enemy will have a 5% chance of attacking
void Enemy::attack()
{
  int8_t value = random(0-20);
  if(value == 1)  //5% chance
  {
    //spawn a lazer right in front of the ship using the coordinates of it
    Sprites::drawPlusMask(x+3, y + 10, EnemyLazer, 0);  //+10 is needed for the middle
    //The lazer has been spawned for this frame but will be lost as soon as we clear it, so we add the coordinates to a vector
    //increment the coordinates and redraw them every frame so that it appears to be moving across the screen every frame
    Pair cord(x+3, y + 10);
    lazers.push_back(cord);  
  }
}//end of RegEnemy attack function


//Function that initially spawns and uses fixed spawn points, should only be called once to spawn, also sets the x and y of this enemy based on spawn point
void Enemy::spawn(Pair spawnPoint)
{
	Serial.print("Someone tried to spawn an enemy!\n");
}


//Function to call when an enemy dies, it iterates through the vector and deletes every element inside of it
void Enemy::death()
{
	while(!lazers.isEmpty()){
		lazers.pop_back();
	}
}


//Function that draws this specific enemy if alive
void RegEnemy::drawEnemy()
{
  if(alive == true){
    Sprites::drawPlusMask(x,y,RegularEnemy,0);  
  }
}//end of drawing RegEnemy


//Function that initially spawns and uses fixed spawn points, should only be called once to spawn, also sets the x and y of this enemy based on spawn point
void RegEnemy::spawn(Pair spawnPoint)
{
	Sprites::drawPlusMask(spawnPoint.first,spawnPoint.second,RegularEnemy,0);
 x = spawnPoint.first;
 y = spawnPoint.second;
}


//spawn and update BlobEnemy based on current coordinates
void BlobEnemy::drawEnemy()
{
	if(alive == true){
    Sprites::drawPlusMask(x,y,Blob,0);  
  }
}


//Function that initially spawns and uses fixed spawn points, should only be called once to spawn, also sets the x and y of this enemy based on spawn point
void BlobEnemy::spawn(Pair spawnPoint)
{
	Sprites::drawPlusMask(spawnPoint.first,spawnPoint.second,Blob,0);
	x = spawnPoint.first;
	y = spawnPoint.second;
}


//Function that makes the enemy shoot lazers
void BlobEnemy::attack()
{
	int8_t value = random(0-100);
	if(value >= 0 && value < 2)  //2% chance
	{
		//spawn a lazer right in front of the ship using the coordinates of it
		Sprites::drawPlusMask(x+3, y+7, BlobLazer, 0);  //+7 is needed for the middle
		//The lazer has been spawned for this frame but will be lost as soon as we clear it, so we add the coordinates to a vector
		//increment the coordinates and redraw them every frame so that it appears to be moving across the screen every frame
		Pair cord(x+3, y+7);
		lazers.push_back(cord);  
	}
}


//spawn and update BlobEnemy based on current coordinates
void TwinEnemy::drawEnemy()
{
	if(alive == true){
    Sprites::drawPlusMask(x,y,Twin,0);  
  }
}


//Function that initially spawns and uses fixed spawn points, should only be called once to spawn, also sets the x and y of this enemy based on spawn point
void TwinEnemy::spawn(Pair spawnPoint)
{
	Sprites::drawPlusMask(spawnPoint.first,spawnPoint.second,Twin,0);
	x = spawnPoint.first;
	y = spawnPoint.second;
}


//Function that makes the enemy shoot double lazers
void TwinEnemy::attack()
{
	int8_t value = random(0-100);
	if(value >= 0 && value < 4)  //5% chance
	{
		//spawn a lazer right in front of the ship using the coordinates of it
		Sprites::drawPlusMask(x+2, y+7, EnemyLazer, 0);	//the + on the x and y is determined by looking at the sprite itself
		//Spawn another lazer
		Sprites::drawPlusMask(x+7, y+7, EnemyLazer, 0);
		//The lazer has been spawned for this frame but will be lost as soon as we clear it, so we add the coordinates to a vector
		//increment the coordinates and redraw them every frame so that it appears to be moving across the screen every frame
		Pair cord(x+2, y+7);
		Pair cord2(x+7, y+7);
		lazers.push_back(cord);
		lazers.push_back(cord2);
	}
}
