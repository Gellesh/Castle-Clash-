#include "Tower.h"
#include "..\Shielded.h"
#include <sstream>
Tower::Tower()
{
	CountNoOfEnemies = 0;
	UnPaved = 30;
	CurrentTimeStamp = 0;
	ShieldedCount = 0;
	RecentUnpaved=30;
	KilledCounter = 0;
}
void Tower::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Tower::GetHealth() const
{
	return Health;
}

void Tower::SetTowerFirepower(double r_fire)
{
	TowerFirepower = r_fire;
}

double Tower::GetTowerFirepower() const
{
	return TowerFirepower;
}

void Tower::SetNoOfEnemiesShoot(int r_number)
{
	NoOfEnemiesShoot = r_number;
}

int Tower::GetNoOfEnemiesShoot() const
{
	return NoOfEnemiesShoot;
}


void Tower::SetConstants(double* C)
{
	for (int i = 0; i < 3; i++)
		Constants[i] = C[i];
}

void Tower::AddEnemyToTower(Enemy* e)  
{
	
	StatusActive.append(e);
	CountNoOfEnemies++;		
	if (e->GetType() == 2)
	{
		ShieldedCount++;
	}
}



void Tower::UpdateKilled()
{
	Enemy* ptr;
	int i = 0;
	bool increment = true;
	while(i< StatusActive.getLength())//checks if the health is zero or less then remove it from active list
	{
		ptr = StatusActive.getEntry(i);
		if (ptr->GetEnemyHealth()<=0)
		{
			StatusActive.remove(i);
			KilledCounter++;
			increment = false;
			if (ptr->GetType() == 2)
			{
				ShieldedCount--;
			}
		}
		else
			increment = true;
		if (increment)
		{
			i++;
		}
	}
}
LinkedList& Tower::GetActiveList()
{
	return StatusActive;
}




void Tower::InitalizaHighPriority(int N)//dynamic allocation to high priority array(called in member func of castle)
{
	HighPriortyEnemies = new Enemy* [N];
}



void Tower::Update()
{
	UpdateKilled();
	UpdateHighPriority();
	UpdateUnpaved();
}

void Tower::UpdateHighPriority()
{
	Updateto_be_Attacked();	
	if (StatusActive.getLength()>0)
		{
			int NoOfShielded=ShieldedCount;

			if(NoOfShielded>NoOfEnemiesShoot)
			{
				int i=0;
				int indx=-1;
				while(i<NoOfEnemiesShoot)
				{
					double Prio1=-1;
					double Prio2=-1;
					double A=Constants[0];
					double B=Constants[1];
					double C=Constants[2];
					for(int j = 0; j< StatusActive.getLength(); j++)
					{
						if(StatusActive.getEntry(j)->GetType()==2 && (StatusActive.getEntry(j)->GettobeAttacked()==false) )
						{
					
							Prio2=double((StatusActive.getEntry(j)->GetFirePower())/StatusActive.getEntry(j)->GetDistance())*A+double(B)/(StatusActive.getEntry(j)->GetTimeToShoot()+1)+StatusActive.getEntry(j)->GetEnemyHealth()*C;
							if(Prio2>Prio1)
							{
								Prio1=Prio2;
								indx=j;
							}
						}
					}
				
					StatusActive.getEntry(indx)->settobeAttacked(true);
					HighPriortyEnemies[i]=StatusActive.getEntry(indx);
					i++;
				}
			}

			else 
			{
				if (NoOfShielded<=NoOfEnemiesShoot && NoOfShielded>0)
				{
					int i=0;
					for(int j = 0; j< StatusActive.getLength(); j++)
					{
						if(StatusActive.getEntry(j)->GetType()==2 && (StatusActive.getEntry(j)->GettobeAttacked()==false) )
						{
							StatusActive.getEntry(j)->settobeAttacked(true);
							HighPriortyEnemies[i]=StatusActive.getEntry(j);
							i++;
						}
					}
					
					int Others;
					if(NoOfEnemiesShoot<=StatusActive.getLength())
						Others=NoOfEnemiesShoot-NoOfShielded;
					else
						Others=StatusActive.getLength()-NoOfShielded;
					for(int k = 0;Others>0; k++)
						{
							if((StatusActive.getEntry(k)->GetType()==1 || StatusActive.getEntry(k)->GetType()==0) )
							{
								StatusActive.getEntry(k)->settobeAttacked(true);
								HighPriortyEnemies[i]=StatusActive.getEntry(k);
								i++;
								Others--;
							}
						}
					}
				////////////////////////////////
				if(NoOfShielded==0)
				{
					if(NoOfEnemiesShoot<=StatusActive.getLength())
					{
						int i=0;
						int j = 0;
						int k = 0;
						while(j<NoOfEnemiesShoot&&k<StatusActive.getLength())
						{
							if((StatusActive.getEntry(k)->GetType()==1 || StatusActive.getEntry(k)->GetType()==0) && (StatusActive.getEntry(k)->GettobeAttacked()==false) )
							{
								StatusActive.getEntry(k)->settobeAttacked(true);
								HighPriortyEnemies[i]=StatusActive.getEntry(k);
								i++;
								j++;
							}
							k++;
						}
					}
					else
					{
						int i=0;
						for(int k = 0; k< StatusActive.getLength(); k++)
						{
							if((StatusActive.getEntry(k)->GetType()==1 || StatusActive.getEntry(k)->GetType()==0) && (StatusActive.getEntry(k)->GettobeAttacked()==false) )
							{
								StatusActive.getEntry(k)->settobeAttacked(true);
								HighPriortyEnemies[i]=StatusActive.getEntry(k);
								i++;
							}
						}	
					}
				 }//end if bta3 no.enemies ti shoot
			
			}//end of else


		}//end of first if
}


void Tower::Attack()
{
	if (!StatusActive.IsEmpty())
	{

		if (StatusActive.getLength() > 0 && StatusActive.getLength() >= NoOfEnemiesShoot)
		{
			for (int i = 0; i < NoOfEnemiesShoot; i++)
			{
				HighPriortyEnemies[i]->CalcDamageOnEnemy(TowerFirepower);
				if(!HighPriortyEnemies[i]->is_shot())
				{
					HighPriortyEnemies[i]->SetFirstShot(CurrentTimeStamp);
					HighPriortyEnemies[i]->set_shot(true);
				}
			}
		}
		else
		{
			for (int i = 0; i < StatusActive.getLength(); i++)
			{
				HighPriortyEnemies[i]->CalcDamageOnEnemy(TowerFirepower);
				if(!HighPriortyEnemies[i]->is_shot())
				{
					HighPriortyEnemies[i]->SetFirstShot(CurrentTimeStamp);
					HighPriortyEnemies[i]->set_shot(true);
				}
			}
		}
	}
}

void Tower::GetAttacked()
{
	for(int i = 0; i < StatusActive.getLength(); i++)
	{
		if(StatusActive.getEntry(i)->GetType()==0)
		     StatusActive.getEntry(i)->Attack(CurrentTimeStamp,Health,UnPaved);
	}
	for(int i = 0; i < StatusActive.getLength(); i++)
	{
		if(StatusActive.getEntry(i)->GetType()==1 || StatusActive.getEntry(i)->GetType()==2)
		     StatusActive.getEntry(i)->Attack(CurrentTimeStamp,Health,UnPaved);
	}
}

void Tower::Kill()//temp func only for simuation to kill the first 3 enemies in active list
{
	if (StatusActive.IsEmpty())//to make sure it isn't empty (but it's not needed)
	{
		return;
	}
	for (int i = 0; i < 3; i++)
	{
		StatusActive.getEntry(i)->SetEnemyHealth(0);
	}
}

void Tower::SetCurrentTimeStamp(int r_CurrentTimeStamp)
{
	CurrentTimeStamp = r_CurrentTimeStamp;
}

int Tower::GetCurrentTimeStamp()const
{
	return CurrentTimeStamp;
}

void Tower::IncrementTimeStamp()
{
	CurrentTimeStamp++;
}

void Tower::PrintInfo(int i ,GUI* pGUI) const
{
	stringstream s1,s2,s3,s4;
	stringstream EnemHealth[20],EnemFP[20],EnemArrTime[20],EnemID[20];
	s1 << GetHealth();
	string H = s1.str();
	s2 << StatusActive.getLength();
	string N = s2.str();
	s3 << UnPaved;
	string UP = s3.str();
	s4 << KilledCounter;
	string KC = s4.str();
	switch(i)
	{
		case 0:
			{
			pGUI->DecrementTextHeight(i+1);
			pGUI->PrintMessage("Region A                                   "+H+"		             				          "+N+"			             		          "+UP+"			             		          "+KC);
			}
			break;
		case 1:
			{
				pGUI->DecrementTextHeight(3);
				pGUI->PrintMessage("Region B                                   "+H+"		             				          "+N+"			             		          "+UP+"			             		          "+KC);
			}		
			break;
		case 2:
			{
				pGUI->DecrementTextHeight(5);
				pGUI->PrintMessage("Region C                                   "+H+"		             				          "+N+"			             		          "+UP+"			             		          "+KC);
			}		
			break;
		case 3:
			{
				pGUI->DecrementTextHeight(7);
				pGUI->PrintMessage("Region D                                   "+H+"		             				          "+N+"			             		          "+UP+"			             		          "+KC);
			}
			break;
	}
	
	pGUI->ResetTextWidth();		
}

void Tower::Updateto_be_Attacked()
{
	for(int i=0; i<StatusActive.getLength(); i++)
	{
		StatusActive.getEntry(i)->settobeAttacked(false);
	}
}

void Tower::UpdateUnpaved()
{
	if(RecentUnpaved-UnPaved>0)
	{
		if( X<601)
			X+=(RecentUnpaved-UnPaved)*8;
		else
			X-=(RecentUnpaved-UnPaved)*8;
		RecentUnpaved=UnPaved;
	}

}

void Tower::SetX(int N)
{
	X=N;
}

int Tower::GetX()const
{
	return X;
}

void Tower::addActiveList(LinkedList&temp, int r)
{
	REGION reg = A_REG;
	switch (r)
	{
	case 0: reg = A_REG;
		break;
	case 1: reg = B_REG;
		break;
	case 2: reg = C_REG;
		break;
	case 3: reg = D_REG;
		break;

	default:
		break;
	}
	
	
	Enemy* etemp;
	while (!temp.IsEmpty())
	{
		etemp = temp.getEntry(0);
		int eDistance = etemp->GetDistance();
		if (eDistance <= UnPaved)
		{
			eDistance = UnPaved+1;
			etemp->SetDistance(eDistance);
		}
		etemp->SetRegion(reg);
		if (etemp->GetType()==2)
		{
			StatusActive.append(etemp);
			ShieldedCount++;
			temp.remove(0);
		}
		else
		{
			for (int i = 0; i < StatusActive.getLength(); i++)
			{
				if (etemp->GetArrivalTime()<StatusActive.getEntry(i)->GetArrivalTime())
				{
					StatusActive.insert(i,etemp);
					temp.remove(0);
					etemp =NULL;
					break;
				}
			}
			if (etemp!=NULL)
			{
				StatusActive.append(etemp);
				temp.remove(0);
			}
		}
	}
}

int Tower::Get_Unpaved() const
{
	return UnPaved;
}
