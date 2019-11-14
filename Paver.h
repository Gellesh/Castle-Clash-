#include"Enemies\Enemy.h"

#pragma once
class Paver:public Enemy
{
	bool to_Attack;
public:
	Paver(REGION r_region, int r_ArrivalTimeStamp, double r_Health, int r_FirePower, int r_ReloadTime, int r_ID,int r_Speed);
	Paver();
	virtual double CalcDamageOnTower();// Calculate damage the enemy make on the tower
	virtual void CalcDamageOnEnemy(double FP);// Calculate damage the tower make on the enemy
	virtual void Move(int &);
	virtual void Attack(int,double&,int&);
	~Paver();
};

