#include "Enemy.h"


Enemy::Enemy(REGION r_region, int r_ArrivalTimeStamp, double r_Health, int r_FirePower, int r_ReloadTime, int r_ID,int r_Speed ,int r_Distance)
{
	Region = r_region;
	SetDistance(r_Distance);
	SetArrivalTime(r_ArrivalTimeStamp);
	SetEnemyHealth(r_Health);
	SetFirePower(r_FirePower);
	SetReloadTime(r_ReloadTime);
	SetAttackTime(r_ArrivalTimeStamp);
	SetEnemySpeed(r_Speed);
	ID = r_ID;
	settobeAttacked(false);
	shoot=false;
}
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

int Enemy::GetID() const
{
	return ID;
}


color Enemy::GetColor() const
{
	return Clr;
}


REGION Enemy::GetRegion() const
{
	return Region;
}

void Enemy::SetRegion(REGION R)
{
	Region = R;
}

void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}

void Enemy::SetEnemyHealth(double H)
{
	Health = H;
}
double Enemy::GetEnemyHealth()const
{
	return Health;
}

void Enemy::SetFirePower(int FP)
{
	FirePower=FP;
}
int Enemy::GetFirePower()const
{
	return FirePower;
}

void Enemy::SetReloadTime(int RT)
{
	ReloadTime=RT;
}
int Enemy::GetReloadTime()const
{
	return ReloadTime;
}

void Enemy:: SetAttackTime(int AT)
{
	AttackTime=AT;
}

int Enemy:: GetAttackTime()const
{
	return AttackTime;
}

void Enemy::SetArrivalTime(int AT)
{
	ArrivalTimeStamp=AT;
}
int Enemy::GetArrivalTime()const
{
	return ArrivalTimeStamp;
}


void Enemy::SetType(int T)
{
	if( T>=0 && T<=2)
		Type=T;
}
int Enemy::GetType()const
{
	return Type;
}

void Enemy::SetFirstShot(int FS)
{
	if(FS>=0)
		FirstShot=FS;
}
int Enemy::GetFirstShot()const
{
	return FirstShot;
}

void Enemy::SetKillTime(int KT)
{
	if(KT>=0)
		KillTime=KT;
}
int Enemy::GetKillTime()const
{
	return KillTime;
}

void Enemy::SetTimeToShoot(int T)
{
	TimeRemToShoot=T;
}
int Enemy::GetTimeToShoot()const
{
	return TimeRemToShoot;
}

int Enemy::KillDelay()
{
	return( KillTime-FirstShot);
}

int Enemy::FirstShotDelay()
{
	return (FirstShot-ArrivalTimeStamp);
}

int Enemy::LifeTime()
{
	return (KillTime-ArrivalTimeStamp);
}

void Enemy::settobeAttacked(bool T)
{
	to_be_Attacked=T;
}

bool Enemy::GettobeAttacked()const
{
	return to_be_Attacked;
}

void Enemy::SetEnemySpeed(int ESpeed)
{
	EnemySpeed = ESpeed;
}
int Enemy::GetEnemySpeed()
{
	return EnemySpeed;
}


bool Enemy:: is_shot()
{
	return shoot;
}
void  Enemy :: set_shot(bool z)
{
	shoot=z;
}



