#include "Battle.h"
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
#include <conio.h>

Battle::Battle()//needed initilization
{
	CurrentTimeStamp = 0;
	EnemyCount = 0;
	TotalEnemiesCount = 0;
	DeadCount = 0;
	for (int i = 0; i < MaxEnemyCount; i++)
	{
		BEnemiesForDraw[i] = NULL;

	}
	IsThereDead = false;
	IsThereLive = false;
	X[0]=241;
	X[1]=960;
	X[2]=960;
	X[3]=241;
}

void Battle::AddEnemy(Enemy* Ptr)//used to enemied to active list only!!!!!!!!!
{
	if (EnemyCount < MaxEnemyCount) 
		BEnemiesForDraw[EnemyCount++] = Ptr;
}

void Battle::DrawEnemies(GUI * pGUI)
{
	pGUI->DrawEnemies(BEnemiesForDraw, EnemyCount);
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}


void Battle::IncrementTimeStamp()
{
	++CurrentTimeStamp;
}

void Battle::LoadFile(GUI *ptr) // load the input file which contains the towers' and enemies' info
{
	
	ptr->DecrementTextHeight(1);

	string label =  ptr->GetString();
	
	ifstream inputfile;
	inputfile.open(label);
	bool exit = false;
	while (!exit)
	{
		if (inputfile.is_open())
		{
			exit = true;
		}
		else
		{
			ptr->ResetTextHeight();
			ptr->ClearStatusBar();
			ptr->PrintMessage("input file :"+label+" wasn't found");
			ptr->DecrementTextHeight(1);
			label =  ptr->GetString();
			inputfile.open(label);
		}
	}
	
	double TowerHealth,TowerNoEnemies,TowerAttack,Constants[3],EnemyHealth;
	int EnemyNumber,Type,ArriveTime,FirePower,ReloadTime,EnemySpeed;
	char CharRegion;
	REGION Region;
	if(inputfile.is_open())//first we read the towers and send them the constants
	{
		inputfile>>TowerHealth>>TowerNoEnemies>>TowerAttack;
		for(int i = 0; i < 3;i++)
			inputfile>>Constants[i];

		BCastle.SetTowersHealth(TowerHealth);
		BCastle.SetTowersPower(TowerAttack);
		BCastle.SetTowersENum(TowerNoEnemies);
		BCastle.SetConstants(Constants);
		

		while(!inputfile.eof())
		{
			inputfile>>EnemyNumber>>Type>>ArriveTime>>EnemyHealth>>FirePower>>ReloadTime>>EnemySpeed>>CharRegion;
			if(EnemyNumber == -1)  //to check if i have reched the end of my file
				break;
			Enemy *ptr;
			switch(CharRegion)//switch case on regions to assign each enemy to it's appropiate one
			{
				case 'A':
					Region = A_REG;
					break;
				case 'B':
					Region = B_REG;
					break;
				case 'C':
					Region = C_REG;
					break;
				case 'D':
					Region = D_REG;
					break;
			}
			switch (Type)//switch case on type to allocate the enemy with it's right type
			{
				case 0: 
					ptr = new Paver(Region, ArriveTime, EnemyHealth, FirePower, ReloadTime, EnemyNumber,EnemySpeed);
					break;
				case 1:
					ptr = new Fighter(Region, ArriveTime, EnemyHealth, FirePower, ReloadTime, EnemyNumber,EnemySpeed);
					break;
				case 2:
					ptr = new Shielded(Region, ArriveTime, EnemyHealth, FirePower, ReloadTime, EnemyNumber,EnemySpeed);
					break;
			}
			if (true)
			{

			}
			if (ptr->GetArrivalTime() <= CurrentTimeStamp) //if it's arrival time is zero then it's avtive already
			{
				BEnemiesForDraw[EnemyCount++] = ptr;
				BCastle.Disribute(ptr);//distrbutes enemies on towers
			}
			InactiveQueue.enqueue(ptr);//in both cases it will be added here
			TotalEnemiesCount++;
		}
	}
	BCastle.intial_health = TowerHealth;
}

int Battle::GetCurrentTimeStamp()const
{
	return CurrentTimeStamp;
}

void Battle::Update()//to update active list 
{
	int i = 0;
	bool increment = true;
	int no_ofkilled_at_instant = 0;
	while(i<EnemyCount)//while loop to remove dead enemies from active
	{
		if (BEnemiesForDraw[i]->GetEnemyHealth() <=0)
		{
			BEnemiesForDraw[i]->SetKillTime(CurrentTimeStamp);
			Killed.enqueue(BEnemiesForDraw[i]);
			BEnemiesForDraw[i] = BEnemiesForDraw[EnemyCount-1];//if found a dead one delete and bring the last and stay  in 
			// BEnemiesForDraw[EnemyCount - 1];
			BEnemiesForDraw[EnemyCount - 1] = NULL;				//the same postion (3lshan m3mlsh skip le 2lly 2na lsa gaybo)
			EnemyCount--;
			DeadCount++;
			TotalEnemiesCount--;
			increment = false;
			IsThereDead = true;
			no_ofkilled_at_instant++;
		}
		else
			increment = true;
		if (increment)
		{
			i++;
		}
	}
	if (no_ofkilled_at_instant > 1)
		sortkilledlist(Killed,no_ofkilled_at_instant);

	Enemy* temp;
	bool exit = false;
	while (!InactiveQueue.isEmpty()&&!exit)//for loop 3lshan 2n2l 2lly msh active le 2l active 3lshan ytrsmo
	{
		exit = true;
		temp = InactiveQueue.peekFront();
		int ArrivalTime = temp->GetArrivalTime();
		if (ArrivalTime <= CurrentTimeStamp  &&  temp->GetEnemyHealth()>0)
		{
			AddEnemy(temp);
			IsThereLive = true;
			InactiveQueue.dequeue();
			BCastle.Disribute(temp);
			exit = false;
		}
	}
	BCastle.Update();//b update 2l active list fe kol 2l towers
	for(int i=0; i<4; i++)
	{
		X[i]=BCastle.GetX(i);
	}
}

void Battle::DisplaySound()
{
	if(IsThereLive)
	{
		PlaySound(TEXT("EnemyLive.wav"),NULL,SND_ASYNC);
		IsThereLive = false;
	}
	if(IsThereDead)
	{
		PlaySound(TEXT("Death.wav"),NULL,SND_ASYNC);
		IsThereDead = false;
	}
	if(IsAllEnemiesDead())
		PlaySound(TEXT("Victory.wav"),NULL,SND_ASYNC);
	if(IsAllTowersDestroyed())
		PlaySound(TEXT("Defeat.wav"),NULL,SND_ASYNC);
}
void Battle::OutputFile()
{
	double TotalShotdelay=0, Totalkilldelay=0;
	int count = 0;
	ofstream outfile("OutputFile.txt");

	outfile << "KTS " << " S " << " FD " <<" KD "<< " LT " << endl;
	while(count<DeadCount)
	{
			Killed.enqueue(Killed.peekFront());
			outfile << Killed.peekFront()->GetKillTime() << "  " << Killed.peekFront()->GetID() << "  " << Killed.peekFront()->FirstShotDelay() << "  " << Killed.peekFront()->KillDelay() << "  " << Killed.peekFront()->LifeTime() << endl;
			Totalkilldelay += Killed.peekFront()->KillDelay();
			TotalShotdelay += Killed.peekFront()->FirstShotDelay();
			Killed.dequeue();
			count++;
	}
	outfile << "T1_Total_Damage " << "  " << " T2_Total_Damage " << "  " << "T3_Total_Damage " << "  " << "T4_Total_Damage" << endl;
	outfile << "  "<<BCastle.GetTowerdamage(0) << "		" << BCastle.GetTowerdamage(1) << "	  " << BCastle.GetTowerdamage(2) << "		 " << BCastle.GetTowerdamage(3) << endl;
	outfile << "R1_Unpaved_Dist " << "  " << " R2_Unpaved_Dist " << "  " << "R3_Unpaved_Dist " << "  " << "R4_Unpaved_Dist" << endl;
	outfile << "	"<<BCastle.Get_Unpaved(0) << "		" << BCastle.Get_Unpaved(1) << "		 " << BCastle.Get_Unpaved(2) << "		 " << BCastle.Get_Unpaved(3) << endl;
	
	
	if (!BCastle.IsAllTowersDead())
	{
		outfile << " Game is won \n" << endl;
		outfile << " 1) Total number of enemy = " << DeadCount << endl;
		outfile << " 2) i) Average shot delay = " << TotalShotdelay / DeadCount << endl << "   ii) Average kill delay = " << Totalkilldelay / DeadCount << endl;

	}
	
	else
	{
		if(DeadCount == 0)
			DeadCount = 1;

		outfile << " Game is Lost \n" << endl;
		outfile << " 1)  Number of killed enemy = " << DeadCount << endl << " 2)  Number of alive enemy = " << EnemyCount <<endl;
		outfile << " 3) i) Average shot delay = " << TotalShotdelay / DeadCount << endl << "   ii) Average kill delay = " << Totalkilldelay / DeadCount << endl;
	}
}


void Battle::SimpleSimulator()
{
	
	BCastle.SetTimeStampForTowers(CurrentTimeStamp);//btde 2l time ll towers 3lshan y2dro y update 2l lists bta3thom
	
	BCastle.TowersAttack();
	BCastle.AttackEnemies();
	Update();//b update 2l BEnemiesToDraw[]
	BCastle.Enemies_to_Attack();
	IncrementTimeStamp();//btzwed time
	for (int i = 0; i < EnemyCount; i++)
	{
		BEnemiesForDraw[i]->SetDistance(BEnemiesForDraw[i]->GetDistance());
	}
	DisplaySound();
}

bool Battle::IsAllEnemiesDead()
{
	if((EnemyCount == 0) && (DeadCount > EnemyCount))
		return true;
	return false;
}
bool Battle::IsAllTowersDestroyed()
{
	return BCastle.IsAllTowersDead();
}

int Battle::GetX(int i)const
{
	return X[i];
}

void Battle::sortkilledlist(Queue & k, int n)
{
	Enemy **a = new Enemy*[n];
	for (int i = 0; i < DeadCount-n; i++)
	{
		k.enqueue(k.peekFront());
		k.dequeue();
	}
	for (int i = 0; i < n; i++)
	{
		a[i] = k.peekFront();
		k.dequeue();
	}

	for (int i = 0; i < n - 1; i++)
	{
			bool inserted = false;
			for (int j = 0; j < n - 1 - i; j++)
			{
				if (a[j]->FirstShotDelay() > a[j + 1]->FirstShotDelay())
				{
					swap(a[j], a[j + 1]);
					inserted = true;
				}
			}
			if (!inserted)
				break;
	}
	for (int i = 0; i < n; i++)
	
		k.enqueue(a[i]);

	delete[] a;
	
}



Battle::~Battle()
{
	for (int i = 0; i < EnemyCount; i++)
	{
		if(BEnemiesForDraw[i] != NULL)
			delete BEnemiesForDraw[i];
		BEnemiesForDraw[i] = NULL;
		
	}
	while (!Killed.isEmpty())
	{
		delete Killed.peekFront();
		Killed.dequeue();
	}
}