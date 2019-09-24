#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduboy2.h>
#include "MyVector.h"
#include "Pair.h"
#include "Ship.h"
#include "AllEnemies.h"
#include "Sprites.h"

static Pair spawnPoints[] = {Pair(0,0), Pair(20,0), Pair(40,0), Pair(60,0), Pair(80,0), Pair(100,0), Pair(117,0) }; //7 spawn points total

struct currentEnemiesForLevel{
  int8_t currentRegEnemies = 0;
  int8_t currentBlobEnemies = 0;
  int8_t currentTwinEnemies = 0;
};


//function that updates every attack on the screen for ship
void drawAllAttacks(Ship &spaceship);

//function that updates every attack on the screen for enemies, determines which lazer to draw based on the type of enemy
void drawAllAttacks(Enemy &enemy);

//Determines if a collision has happened between ship and ship or ship and lazer, if collision with lazer, lazer is removed from the vector
bool checkCollision(Ship &spaceship, Enemy &enemy, int8_t &enemiesLeftAlive);

//Function to play out the level
void playLevel(Ship &spaceship, Enemy *arrayOfEnemies[], int8_t &enemiesLeftAlive, Arduboy2 arduboy, const int8_t totalEnemies);

//Function that draws the tittle screen and returns true if the player pressed A
bool bstartScreen(Arduboy2 arduboy);

//Function that servers to set up the variables before we go into the level
void setUpLevel(int8_t &enemiesLeftAlive, int8_t &totalEnemies, Enemy *maxEnemySpawns[], Ship &spaceShip, Arduboy2 arduboy, currentEnemiesForLevel &levelEnemyInfo);

//Function that collapses small enemies into bigger enemies if possible, used during set up
bool collapseEnemies(Enemy *maxEnemySpawns[], currentEnemiesForLevel &levelEnemyInfo);

//Function that fills the array of enemies based on what it needs to be and spawns them as well, used during set up
void fillAndSpawnEnemyArray(Enemy *maxEnemySpawns[], const currentEnemiesForLevel &levelEnemyInfo, const int8_t &totalEnemies);

//Function that serves as a transition for the next level(not to be confused with setting up for the next level)
bool isReadyToTransition(Ship spaceship);

#endif
