#pragma once

#include"..\Data_Structure\LinkedBag.h"
#include"..\Data_Structure\LinkedList.h"
#include"..\Data_Structure\LinkedQueue.h"
#include "..\GUI\GUI.h"
class Tower
{
	double Health; // tower's health
	double TowerFirepower; //fire power of tower
	int NoOfEnemiesShoot;  //number of Enemies tower can shoot
	int CountNoOfEnemies; // counter for the number of enemies
	double Constants[3]; // constants that will determine the priority of the shielded enemy
	int UnPaved;// Determine the Unpaved Distance
	int CurrentTimeStamp; // current time of the game
	int ShieldedCount;//counter to number of shielded enemies
	LinkedList StatusActive; // list of the enemies whose arrival time is less than or equal the current time step
	Enemy ** HighPriortyEnemies; // Enemies that will attack first by the tower (Shielded enemies)
	void UpdateHighPriority(); //to update the array of high priority
	void UpdateKilled();//to remove killed enemies from active list
	int X;
	int RecentUnpaved;
	int KilledCounter;// the number of killed enemies in each region
	

public:
	
	Tower(void); 
	
	//set and get the health of each tower
	void SetHealth(double h);
	double GetHealth() const;
	
	//set and get the firepower of each tower
	void SetTowerFirepower(double r_fire);
	double GetTowerFirepower()const;
	
	//set and get the no of enemies to shoot of each tower
	void SetNoOfEnemiesShoot(int r_number); //N number in pdf
	int GetNoOfEnemiesShoot()const;
	

	void SetConstants(double*C);//used in the equation to calc priority of shielded
	void AddEnemyToTower(Enemy*);// add the enemy to each tower's active list if its arrival time is less than or equal the game current time otherwise it will be added to the inactive list
	
	LinkedList& GetActiveList();//those funcs for if the tower is destroyed the castle calls them and move the enemies to the next tower
	//LinkedBag GetKilledBag();
	void InitalizaHighPriority(int N); // to dynamicaly allocate the high priority array of enemies
	void Update();//used to update all lists included 
	void Attack();//when towers attacks enemies in high priority array
	void GetAttacked();//when enemies attacks the towers
	void PrintInfo(int i,GUI*)const; // printing info for each tower in each region : no killed enemies , tower's health , etc..
	void Kill();//temp func for simulation to kill the first 3 enemies
	void SetCurrentTimeStamp(int r_CurrentTimeStamp);//used to get the time stamp from battle
	int GetCurrentTimeStamp()const; // return the current time of the game
	void IncrementTimeStamp();//these func for if it's decided to maked two time counters in parallel with battle
	void Updateto_be_Attacked();
	void UpdateUnpaved();
	void SetX(int );
	int GetX()const;
	void addActiveList(LinkedList&temp,int r);
	int Get_Unpaved()const;
	
};

