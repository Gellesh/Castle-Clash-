#include "Shielded.h"

Shielded::Shielded()
{}

Shielded::Shielded(REGION r_region, int r_ArrivalTimeStamp, double r_Health, int r_FirePower, int r_ReloadTime, int r_ID,int r_Speed):
	Enemy( r_region,  r_ArrivalTimeStamp,  r_Health,  r_FirePower,  r_ReloadTime,  r_ID, r_Speed)
{
	Clr = ORANGERED;
	Type = 2;
}


double Shielded::CalcDamageOnTower()
{
	return ((2/double(Distance))*FirePower);
}

void Shielded::Move(int& Unpaved)
{
	int Diff=Distance-Unpaved;
	if(Diff>EnemySpeed)
		Distance-=EnemySpeed;
	else
	{
		Distance-=Diff-1;
	}
}
void Shielded::Attack(int TimeStep,double& HealthOfTower,int& Unpaved)
{
	if(TimeStep == (AttackTime+1))
	{
		AttackTime += ReloadTime + 1;
		double EnemyDamage = CalcDamageOnTower();
		HealthOfTower -= EnemyDamage;
	}
	Move(Unpaved);
}

void Shielded::CalcDamageOnEnemy(double FirePower)
{
	Health=Health-((1/double(Distance))*FirePower*(1/2.0));
}

Shielded::~Shielded()
{
}
