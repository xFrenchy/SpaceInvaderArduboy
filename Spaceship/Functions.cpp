#include "Functions.h"

//function that updates every attack on the screen, both arguments are optional, Better to only pass 1 argument
void drawAllAttacks(Ship &spaceship)
{
	//attack for our spaceship
	MyVector newCord;
	int8_t size = spaceship.lazers.vsize;
	for(int8_t i = 0; i < spaceship.lazers.vsize; i++)
	{
		//draw the lazer from the array of coordinates, make it move up the screen, and determine if they should be drawn
		Pair cord = spaceship.lazers[i];
		if(cord.second > 0) //it's valid and not off the screen
		{
			Pair toAddCord(cord.first, cord.second - 1);  
			Sprites::drawPlusMask(cord.first, cord.second, Lazer, 0);
			newCord.push_back(toAddCord);
		}
	}
	//empty the previous vector before deleting
	while(!spaceship.lazers.isEmpty()){
		spaceship.lazers.pop_back();
	}
	//pop back has deleted the vector and everything in it
	spaceship.lazers = newCord;
}//end of drawing all attacks function for ship


//function that updates every attack on the screen for enemies, determines which lazer to draw based on the type of enemy
void drawAllAttacks(Enemy &enemy)
{
	//attack for the enemy
	MyVector newCord;
	for(int8_t i = 0; i < enemy.lazers.vsize; i++)
	{
		//draw the lazer from the array of coordinates, make it move up the screen, and determine if they should be drawn
		Pair Cord = enemy.lazers[i];
		if(Cord.second < 64) //it's valid and not off the screen
		{
			Pair toAddCord(Cord.first, Cord.second + 1);
			if(enemy.type == EnemyType::regular || enemy.type == EnemyType::twin){
				Sprites::drawPlusMask(Cord.first, Cord.second, Lazer, 0);
			}
			else if(enemy.type == EnemyType::blob){
				Sprites::drawPlusMask(Cord.first, Cord.second, BlobLazer, 0);
			}
			newCord.push_back(toAddCord);
		}
	}
	//now iterate through the old vector, delete all elements and then delete pointer
	while(!enemy.lazers.isEmpty()){
		enemy.lazers.pop_back();
	}
	enemy.lazers = newCord;
}//end of drawing all attack function for enemies


//Determines if a collision has happened between ship and ship or ship and lazer, if collision with lazer, lazer is removed from the vector
bool checkCollision(Ship &spaceship, Enemy &enemy, int8_t &enemiesLeftAlive)
{
  //check if ships collide with each other
  if(Arduboy2Base::collide(spaceship.hitBox, enemy.hitBox) && enemy.alive == true){  //the spaceship collided with the enemy
    enemy.alive = false;
	enemy.death();	//gets rid of everything inside of the vector to free up memory
	spaceship.score += 20;
	enemiesLeftAlive--;
    spaceship.damageTaken(35);
	return true;
  }
  
  //check if enemy lazer collides with ship
  int8_t size = enemy.lazers.vsize;
  for(int8_t i = 0; i < size; i++)
  {
    Pair cord = enemy.lazers[i];
	  if(enemy.type == EnemyType::regular || enemy.type == EnemyType::twin){	//lazer is one pixel width so point is fine
		  Point x(cord.first, cord.second);
      if(Arduboy2Base::collide(x, spaceship.hitBox) && spaceship.lifeRemaining > 0){  //ship has been hit with a lazer
        spaceship.damageTaken(8);
        enemy.lazers.removeElement(i);  //delete lazer out of the vector since it has hit the ship
      }
	  }
	  else if(enemy.type == EnemyType::blob){
		  Rect x(cord.first, cord.second, 4, 3);	//Lazer is 4 pixels wide and 3 pixels high
      if(Arduboy2Base::collide(x, spaceship.hitBox) && spaceship.lifeRemaining > 0){  //ship has been hit with a lazer
        spaceship.damageTaken(12);
        enemy.lazers.removeElement(i);  //delete lazer out of the vector since it has hit the ship
      }
	  }
  }//end of for loop for enemy lazer collision
  
  //check if ship lazer has hit the enemy
  size = spaceship.lazers.vsize;
  for(int8_t i = 0; i < size; i++)
  {
    Pair sCord = spaceship.lazers[i];
    Point s(sCord.first, sCord.second);
    if(Arduboy2Base::collide(s, enemy.hitBox) && enemy.alive == true){  //enemy has been hit by a lazer
      enemy.alive = false;
	  enemy.death();
	  spaceship.score += 20;
	  enemiesLeftAlive--;
      spaceship.lazers.removeElement(i);
	  return true;
    }
  }
  return false;
}


//Function to play out the level
void playLevel(Ship &spaceship, Enemy *arrayOfEnemies[], int8_t &enemiesLeftAlive, Arduboy2 arduboy, const int8_t totalEnemies)
{
	//Comments about the function, I might not need to create loops based on the enemiesLeftAlive, I could create them
	//based on the total enemies and simply check if they are alive before calling functions(already do that check)
	//This would allow me to not have to rearrange the array at all
	
  //redraw every updated lazers
  drawAllAttacks(spaceship);
  for(int i = 0; i < totalEnemies; i++)
  {
	  drawAllAttacks(*arrayOfEnemies[i]);
  }
  //check for collision with lazers and ships
  for(int i = 0; i < totalEnemies; i++)
  {
	//here we have a chance of having an enemy die, we must check for this
	//if an enemy dies, we must rearrange the array
	if(arrayOfEnemies[i]->alive == true)	//since the enemy is alive, we check for collision
	{
		checkCollision(spaceship, *arrayOfEnemies[i], enemiesLeftAlive);	//if true, this will set the alive variable to false and decrement enemiesLeftAlive
	}
  }
  //check if the enemy is alive
  for(int i = 0; i < totalEnemies; i++)
  {
  	if(arrayOfEnemies[i]->alive == true)
  	{
      //allow enemy to move
      arrayOfEnemies[i]->movement();
      //allow enemy to shoot
      arrayOfEnemies[i]->attack();
  	}  
  }
  //allow the ship to move
  spaceship.shipMovement(arduboy);
  //allow ship to attack
  if(arduboy.justPressed(A_BUTTON))
  {
    spaceship.shipAttack();
  }
  //allow ship to regenerate armor very slowly
  if(arduboy.everyXFrames(80)){
    spaceship.regenerate();
  }
  //Spawn/update ship
  spaceship.drawShip(arduboy);
  //Spawn/update enemy
  for(int i = 0; i < totalEnemies; i++)
  {
	  if(arrayOfEnemies[i]->alive == true){
		  arrayOfEnemies[i]->drawEnemy();
	  }
  }
}//End of play game


//Function that draws the tittle screen and returns true if the player pressed A
bool bstartScreen(Arduboy2 arduboy)
{
	Sprites::drawPlusMask(0,0,TitleScreen,0);  
  if(arduboy.justPressed(A_BUTTON)){
    return true;
  }
	return false;
}


//Function that servers to set up the variables before we go into the level
void setUpLevel(int8_t &enemiesLeftAlive, int8_t &totalEnemies, Enemy *maxEnemySpawns[], Ship &spaceShip, Arduboy2 arduboy, currentEnemiesForLevel &levelEnemyInfo)
{
	totalEnemies = (levelEnemyInfo.currentRegEnemies + levelEnemyInfo.currentBlobEnemies + levelEnemyInfo.currentTwinEnemies);
	//No matter where we are in the game, we check to see if we can make bigger enemies based on what we have, if we can't, we add the weakest enemy
	if(!collapseEnemies(maxEnemySpawns, levelEnemyInfo)){	//if no collapsing has been done, fill the array with enemies and spawn the lowest enemy as an addition
		fillAndSpawnEnemyArray(maxEnemySpawns, levelEnemyInfo, totalEnemies);
		//we have added all enemies to the array BUT the weakest since no collision has been detected
		maxEnemySpawns[totalEnemies] = new RegEnemy;
		levelEnemyInfo.currentRegEnemies++;
		totalEnemies++;
	}
	else{	//collapsing has happened, we just need to fill the array, no extra addition of mobs
		fillAndSpawnEnemyArray(maxEnemySpawns, levelEnemyInfo, totalEnemies);
	}
	totalEnemies = (levelEnemyInfo.currentRegEnemies + levelEnemyInfo.currentBlobEnemies + levelEnemyInfo.currentTwinEnemies);	//we update this variable again once numbers have gone up or down
	enemiesLeftAlive = totalEnemies;	//this variable is used everywhere so it's important to update it, I might be able to refactor my code and get rid of this variable
    //enemies are spawned, now spawn the ship
    spaceShip.drawShip(arduboy);
	//debugging
	/*Serial.print("enemiesLeftAlive: ");
	Serial.print(enemiesLeftAlive);
	Serial.print("\n");
	Serial.print("totalEnemies: ");
	Serial.print(totalEnemies);
	Serial.print("\n");*/
}


//Function that collapses small enemies into bigger enemies if possible
bool collapseEnemies(Enemy *maxEnemySpawns[], currentEnemiesForLevel &levelEnemyInfo)
{	
	//for future addition, we want to create this into an if/else if/else if... and go from the highest combination to the lowest
	if(levelEnemyInfo.currentBlobEnemies == 2){
		levelEnemyInfo.currentBlobEnemies = 0;
		levelEnemyInfo.currentTwinEnemies++;
		return true;
	}
	else if(levelEnemyInfo.currentRegEnemies == 2){	//we collapse them into a blob enemy
		levelEnemyInfo.currentRegEnemies = 0;	//we have consumed the regEnemies into a blob enemy
		levelEnemyInfo.currentBlobEnemies++;	//we have gained a blob enemy
		return true;
	}
	return false;
}


//Function that fills the array of enemies based on what it needs to be and spawns them as well, used during set up
void fillAndSpawnEnemyArray(Enemy *maxEnemySpawns[], const currentEnemiesForLevel &levelEnemyInfo, const int8_t &totalEnemies)
{
	byte regMob = levelEnemyInfo.currentRegEnemies;
	byte blobMob = levelEnemyInfo.currentBlobEnemies;	//this seems messy, we could potentially optimize this
	byte twinMob = levelEnemyInfo.currentTwinEnemies;
	for(int8_t i = 0; i < totalEnemies; i++)
	{
		//we fill the array with the lowest the strongest enemy based on the levelEnemyInfo variable
		if(regMob > 0){
			maxEnemySpawns[i] = new RegEnemy;
			maxEnemySpawns[i]->spawn(spawnPoints[i%7]);
			regMob--;
		}
		else if(blobMob > 0){
			maxEnemySpawns[i] = new BlobEnemy;
			maxEnemySpawns[i]->spawn(spawnPoints[i%7]);
			blobMob--;
		}
		else if(twinMob > 0){
			maxEnemySpawns[i] = new TwinEnemy;
			maxEnemySpawns[i]->spawn(spawnPoints[i%7]);
			twinMob--;
		}
	}
}


//Function that serves as a transition for the next level(not to be confused with setting up for the next level)
bool isReadyToTransition(Ship spaceship)
{
	//We wait until all of the ship's lazers are despawned from the game to return true, this allows us to not run into the issue where an alien spawns into a bullet and multiple die(somehow)
	if(spaceship.lazers.isEmpty()){	//if this is true, proceed to the next level
		return true;
	}
	return false;
}
