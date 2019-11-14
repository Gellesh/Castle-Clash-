#pragma once

#include "Enemies\Enemy.h"
#include "Paver.h"
#include "Fighter.h"
#include "Shielded.h"
#include "Castle\Castle.h"
#include <iostream>
#include"queue.h"

// it is the controller of the project
class Battle
{
private:
	Castle BCastle;
	int EnemyCount;							//the actual number of enemies in the game
	Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function
	LinkedQueue InactiveQueue;
	Queue Killed;
	int TotalEnemiesCount;  //count of all enemies in all states
	int CurrentTimeStamp;   //the general current time in the game
	bool IsThereDead;
	bool IsThereLive;
	int DeadCount;
	int X[4];
public:
	
	Battle();
	void AddEnemy(Enemy* Ptr);
	void DrawEnemies(GUI * pGUI);
	Castle * GetCastle();// used to return pointer of castle to call the function(s) of the castle
	void IncrementTimeStamp(); // increment the time stamp of the whole game
	void LoadFile(GUI* ptr);//load the data of all enemies
	int GetCurrentTimeStamp()const;//return the current time of the game
	void Update();//should update active enemies array then calls update for castle and draw then increment time
	void OutputFile();//produces the output file
	void SimpleSimulator();//simulation function 
	void DisplaySound();//Displayng Sound Effects
	bool IsAllEnemiesDead();//Check if All the Enemies are killeds
	bool IsAllTowersDestroyed();//Check if All the 4 towers are destroyed
	int GetX(int i)const;
	void sortkilledlist(Queue &,int); //to sort enemy who died in same time stamp
	~Battle();
};

