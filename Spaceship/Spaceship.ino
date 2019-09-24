//Anthony Dupont
//20 July 2019
//SpaceShip shooting game
#include <Arduboy2.h>
#include "Ship.h"
#include "Pair.h"
#include "MyVector.h"
#include "AllEnemies.h"
#include "Functions.h"
#include "Sprites.h"

enum class gameState
{
  titleScreen,
  setUpLevel,
  mainGame,
  endScreen
};

Arduboy2 arduboy;
Ship spaceShip;
static Enemy *maxEnemySpawns[10]; //keep in mind that I could potentially only use this array instead of having this array and another array that determines the 
int8_t enemiesLeftAlive;
int8_t totalEnemies;
byte currentLevel;
gameState state = gameState::titleScreen;
static currentEnemiesForLevel levelEnemyInfo;



void setup() {
  // put your setup code here, to run once:
  arduboy.begin();
  arduboy.clear();
  arduboy.setFrameRate(50);
  //Seeding the random number generator
  arduboy.initRandomSeed();
  Serial.begin(9600);
}

/*TODO: 
 * Create a boss, think of it like a fight cave type of wave
 * Fix the code that deals with the hitbox of each lazer, currently we have the same code copy pasted into an if and then an else
 * Fix the code for adding a new enemy, currently I have to altar the set up function, collapse function, collision function, draw all attack function etc etc(too messy)
 * Adjust the score awarded per kill, currently every ship gives 20, some ships should give more/less

CURRENT ERROR: 

*/
void loop() {
  // put your main code here, to run repeatedly:
  if(!arduboy.nextFrame()){ //if it's not the next frame, don't run this code yet
    return;
  }
  arduboy.clear();
  arduboy.pollButtons();
  Serial.print("Test\n");
  /*if(state == gameState::titleScreen){
    Serial.print("state = titleScreen\n");
  }
  else if(state == gameState::setUpLevel){
    Serial.print("state = setUpLevel\n");
  }
  else if(state == gameState::mainGame){
    Serial.print("state = mainGame\n");
  }
  else if(state == gameState::endScreen){
    Serial.print("state = endScreen\n");
  }
  else{
    Serial.print("state = no fucking clue\n");
  }*/
  switch(state){
    case gameState::titleScreen:
    Serial.print("Inside game state title screen\n");
      if(bstartScreen(arduboy)){
        Serial.print("User pressed A! switching to setting up!\n");
        state = gameState::setUpLevel;
      }
      break;
      
    case gameState::setUpLevel:
    Serial.print("Inside game state set up level\n");
      setUpLevel(enemiesLeftAlive, totalEnemies, maxEnemySpawns, spaceShip, arduboy, levelEnemyInfo);
      //enemies are spawned, ship is spwaned, play the level
      state = gameState::mainGame;
      Serial.print("set up has finshed, switching to play game!\n");
      break;
      
    case gameState::mainGame:
      Serial.print("Inside game state main game\n");
      /*Serial.print("enemiesLeftAlive = ");
      Serial.print(enemiesLeftAlive);
      Serial.print("\n");
      Serial.print("totalEnemies = ");
      Serial.print(totalEnemies);
      Serial.print("\n");
      Serial.print("current level = ");
      Serial.print(spaceShip.currentLevel);
      Serial.print("\n");*/
      playLevel(spaceShip, maxEnemySpawns, enemiesLeftAlive, arduboy, totalEnemies);
      //check if the ship is alive
      if(spaceShip.lifeRemaining <= 0)
      {
        state = gameState::endScreen;
      }
      
      if(enemiesLeftAlive <= 0 && isReadyToTransition(spaceShip) == true){  //We beat the level, time to move on to the next one
        spaceShip.currentLevel++;
        state = gameState::setUpLevel;
      }
      else if(enemiesLeftAlive <= 0){ //we beat the level but we can't transition just yet, we wait for the transition
        //we draw on the screen
        arduboy.setCursor(31,10);
        arduboy.print("Next level...\n");
      }
      break;
      
    case gameState::endScreen: //currently endScreen is the death screen
      Serial.print("Inside game state end screen\n");
      arduboy.setCursor(39, 20);
      arduboy.print("Game over!\n");
      arduboy.setCursor(46, 32);
      arduboy.print("Press B\n"); 
      arduboy.setCursor(14, 40);
      arduboy.print("for title screen\n");
      if(arduboy.justPressed(B_BUTTON)){
        spaceShip.reset();
        for(int8_t i = 0; i < 10; i++){
          maxEnemySpawns[i] = NULL;
        }
        levelEnemyInfo.currentRegEnemies = 0;
        levelEnemyInfo.currentBlobEnemies = 0;
        levelEnemyInfo.currentTwinEnemies = 0;
        state = gameState::titleScreen;
      }
      break;
      
    default:
      Serial.print("Inside game state default, error has happened\n");  //could delete this error to free up some space
      break;
  }
  arduboy.display();
}
