#include "Castle.h"

#include "..\GUI\GUI.h"

Castle::Castle()
{
	Towers[0].SetX(241);
	Towers[1].SetX(960);
	Towers[2].SetX(960);
	Towers[3].SetX(241);
	X[0]=241;
	X[1]=960;
	X[2]=960;
	X[3]=241;
}

void Castle::SetTowersHealth(double h)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetHealth(h);
	}
}

void Castle::TowersAttack()
{
	for(int i = 0; i < 4;i++)
		Towers[i].GetAttacked();
}

void Castle::AttackEnemies()
{
	for(int i = 0; i < 4;i++)
			Towers[i].Attack();
}

void Castle::SetConstants(double *c)//send array of constants to each tower
{
	for (int i = 0; i < 4; i++)
		Towers[i].SetConstants(c);
}

void Castle::SetTowersPower(double p)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetTowerFirepower(p);
	}
}

void Castle::SetTowersENum(int n)//ENUM->>N (number of enemies to shoot)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetNoOfEnemiesShoot(n);
		Towers[i].InitalizaHighPriority(n);  //dynamically alocate array of pointers to the attacked enemies
	}
}

void Castle::Disribute(Enemy*e)  //assign each new enemy to it's tower
{
	
	int region = e->GetRegion();
	switch (region)
	{
		case 0:
			Towers[0].AddEnemyToTower(e);
			break;
		case 1:
			Towers[1].AddEnemyToTower(e);
			break;
		case 2:
			Towers[2].AddEnemyToTower(e);
			break;
		case 3:
			Towers[3].AddEnemyToTower(e);
			break;
	}
}


void Castle::SetTimeStampForTowers(int T)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetCurrentTimeStamp(T);
	}
}

void Castle::Update()//calls func update for towers(at least for now xD)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].Update();
		X[i]=Towers[i].GetX();
	}
	for (int i = 0; i < 4; i++)
	{
		if (Towers[i].GetHealth()<=0)
		{
			int count = 4;
			int k = -1;
			int j=i;
			Towers[i].SetHealth(0);
			while (count > 0 )
			{
				j=j%4;
				if (Towers[j].GetHealth()>0)
				{
					k = j;
					count = -1;
					break;
				}
				count--;
				j++;
			}
			if (k!=-1)
			{
				Towers[j].addActiveList(Towers[i].GetActiveList(),j);
				Towers[i].SetNoOfEnemiesShoot(0);
			}
		}
	}
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].Update();
	}
}


void Castle::PrintInfo(GUI* pGUI)const
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].PrintInfo(i,pGUI);
	}
}

void Castle::IsDead(){}

bool Castle::IsAllTowersDead()
{
	int CountDeadTowers = 0;
	for(int i = 0;i < 4;i++)
		if(Towers[i].GetHealth() <= 0)
			CountDeadTowers++;
	if(CountDeadTowers == 4)
		return true;
	return false;
}

void Castle::Kill()//kills 3 enemies in each tower
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].Kill();
	}
}

void Castle::Enemies_to_Attack()
{
	for(int i=0; i<4; i++)
	{
		Towers[i].Updateto_be_Attacked();
	}
}

int Castle::GetX(int i)const
{
	return X[i];
}

double Castle::GetTowerdamage(int i) const
{
	return intial_health - Towers[i].GetHealth();
}

int Castle::Get_Unpaved(int i) const
{
	return Towers[i].Get_Unpaved();
}
