#include "Paver.h"


Paver::Paver(REGION r_region, int r_ArrivalTimeStamp, double r_Health, int r_FirePower, int r_ReloadTime, int r_ID,int r_Speed):
	Enemy( r_region,  r_ArrivalTimeStamp,  r_Health,  r_FirePower,  r_ReloadTime,  r_ID, r_Speed)
{
	Clr = DARKBLUE;
	Type = 0;
	to_Attack=false;
}
Paver::Paver()
{}
void Paver::Attack(int TS,double& H, int& UNP)
{
	int Damage=CalcDamageOnTower();
	H-=Damage;
	if(TS==(AttackTime+1))
	{
		to_Attack=true;
		AttackTime+=ReloadTime+1;
		Move(UNP);
    }
	else
	{
		Move(UNP);
	}

}

void Paver::Move(int & UNP)
{     
	if(to_Attack)
	{
		to_Attack=false;
		int unpaved=UNP-FirePower;
		if(Distance>UNP && UNP>2 && (Distance-UNP==1) && (unpaved>2))
		{
			Distance-=FirePower;
			UNP-=FirePower;
			return;
		}
		int Diff=Distance-UNP-1;
		if(Distance>UNP && UNP>2 && (Diff>=FirePower) && (unpaved>2))
		{
			Distance-=FirePower;
			return;
		}

		if(Distance>UNP && UNP>2 && (Diff<FirePower) && (Diff>=1) && (unpaved>2))
		{
			Distance-=FirePower;
			UNP=UNP-(FirePower-Diff);
			return;
		}
		if(unpaved<=2)
		{
			if(UNP>=2)
			{
				UNP=2;
				Distance=3;
			}
		}
	}
	else
	{
		int Diff=Distance-UNP;
		if(UNP>2)
		{
	      if(Diff>EnemySpeed)
		     Distance-=EnemySpeed;
	      else
	      {
		     Distance-=Diff-1;
	      }
		}
	}
}

double Paver::CalcDamageOnTower()
{
	return 0;
}

void Paver::CalcDamageOnEnemy(double FirePower)
{
	Health=Health-((1/double(Distance))*FirePower);
}

Paver::~Paver()
{
}
