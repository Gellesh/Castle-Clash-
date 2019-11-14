#pragma once
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"

#include "Tower.h"

class Castle
{
	Tower Towers[4];
	int X[4];
	bool GameLoss;
public:

	Castle();
	void SetTowersHealth(double h);//setting the health of each tower in each region
	void SetTowersPower(double p);// setting the power to each tower
	void SetTowersENum(int n); // setting the enemy number to each tower
	void SetConstants(double*);// setting the constants(in towers class) that will determine the priority of shielded enemys
	void SetTimeStampForTowers(int T); //set time stamp for e  towers
	void Update();//it's used to make tower attack its enemies and vice vesra(in phase TWO!)
	void TowersAttack();
	void AttackEnemies();

	void Enemies_to_Attack();
	
	void Disribute(Enemy*e); // distribute the enemy to the tower that belong to its region
	
	void IsDead(); //to check if one of the towers is destroyed and move its enemeies to the next one
	void Kill();//temp func to test simulation(kills 3 active enemies in each tower)

	void PrintInfo(GUI*)const; // used to call the the print info of each tower in each region

	bool IsAllTowersDead();//check the health of all the towers if they are -all- destroyed or not

	int GetX(int i)const;
	double intial_health;
	double GetTowerdamage(int )const;
	int Get_Unpaved(int )const;
};
