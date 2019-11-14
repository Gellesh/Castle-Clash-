#include"Enemies\Enemy.h"

#pragma once
class Shielded:public Enemy
{

public:
	Shielded(REGION r_region, int r_ArrivalTimeStamp, double r_Health, int r_FirePower, int r_ReloadTime, int r_ID,int r_Speed);
	Shielded();
	double CalcDamageOnTower();// Calculate damage the enemy make on the tower
	void CalcDamageOnEnemy(double FP);// Calculate damage the tower make on the enemy

	virtual void Move(int&);	    //All enemies can move
	virtual void Attack(int,double&,int&);	//All enemies can attack (attacking is paving or shooting)
	
	~Shielded();
};

