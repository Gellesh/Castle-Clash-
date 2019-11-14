#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

// Enemy is the base class of each type of enemy
// Enemy is an abstract class.
class Enemy
{

protected:
	int ID;         //Each enemy has a unique ID (sequence number)
	color Clr;	    //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;  //Region of this enemy
	int Distance;	//Horizontal distance between enemy & the tower of its region  Always positive (ranges from 2 to 60)
	int FirePower; // FirePower of the enemey  
	int ReloadTime; // ReloadTime of the enemy
	int AttackTime ; //Time at which the enemy attack the tower
	int ArrivalTimeStamp; // the time at which the enemy arrives
	int Type;  //Ranges from 0-2
	int FirstShot; // Firstshot of the enemy
	int KillTime; // the time at which the enemy is killed
	double Health;	//Enemy health
	bool to_be_Attacked;
	int EnemySpeed;//Enemy Speed to make its stepmove faster
	int TimeRemToShoot;
	bool shoot;
public:
	Enemy(REGION r_region, int r_ArrivalTimeStamp, double r_Health, int r_FirePower, int r_ReloadTime, int r_ID,int r_Speed, int r_Distance = MaxDistance);
	Enemy();
	 ~Enemy();
	
	// return the color of the enemy
	color GetColor() const;
	// return the region to which the enemy belongs 
	REGION GetRegion() const;
	void SetRegion(REGION R);
	void DecrementDist(); //Decrement Distance each time step

	// return the ID(number) of the enemy
	int GetID() const;
	//set and get the distance of the enemy from the tower  
	void SetDistance(int d);  
	int GetDistance() const;

	//set and get the health of the enemy
	void SetEnemyHealth(double H);
	double GetEnemyHealth()const;

	//set and get the arrivaltime of the enemy
	void SetArrivalTime(int T);
	int GetArrivalTime()const;

	// set and get the fire power of the enemy
	void SetFirePower(int FP);
	int GetFirePower()const;
	
	// set and get the reload time of the enemy
	void SetReloadTime(int RT);
	int GetReloadTime()const;

	// set and get the attacktime of the enemy
	void SetAttackTime(int AT);
	int GetAttackTime()const;

	// set and get the type of the enemy
	void SetType(int TP);
	int GetType()const;

	// set and get the first shot of the enemy
    void SetFirstShot(int FS);
	int GetFirstShot()const;

	// set and get the killtime of the enemy
    void SetKillTime(int KT);
	int GetKillTime()const;
	//set and get to_be_Attacked
	void settobeAttacked(bool);
	bool GettobeAttacked()const;

	void SetTimeToShoot(int );
	int GetTimeToShoot()const;

	int KillDelay(); // calculate and return the kill delay
	int FirstShotDelay(); // calculate and return the first shot delay
	int LifeTime(); // calculate and return the life time delay

	virtual  double CalcDamageOnTower() = 0;// Calculate damage the enemy make on the tower
	virtual void CalcDamageOnEnemy(double FP) = 0;// Calculate damage the tower make on the enemy

	// Setting and Getting the speed of the enemy
	void SetEnemySpeed(int);
	int GetEnemySpeed();

	virtual void Move(int&) = 0;	    //All enemies can move
	virtual void Attack(int,double&,int&) = 0;	//All enemies can attack (attacking is paving or shooting)
	// to calculate first shot
	bool is_shot();
	void set_shot(bool);
};

