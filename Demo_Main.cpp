#include "Battle.h"
#include "GUI\GUI.h"
#include <fstream>
#include <sstream>

int main()
{


	Battle* pGameBattle = new Battle;

	GUI * pGUI = new GUI;
	
	Point p;
	
	pGUI->PrintMessage("Please Enter the inputfile name and its format for example: input.txt");

	pGameBattle->LoadFile(pGUI);//loading the data from the input file
	pGUI->ClearStatusBar();
	pGUI->PrintMessage("Please choose your mode from the menu bar");
	

		pGameBattle->DrawEnemies(pGUI);//Drawing the enemies whose arrival time is zero
		int ChosenMode = -1;
		while(ChosenMode == -1)
		{
			pGUI->GetPointClicked(p);
			if(p.y > 0 && p.y < 50)
			{
				if(p.x > 0 && p.x < 1*80)
				{
					pGUI->ClearStatusBar();
					pGUI->PrintMessage("Your Now in active Mode !! click anywhere to start the game");
					ChosenMode = 0;
					break;
				}
				if(p.x > 1*80 && p.x < 2*80)
				{
					pGUI->ClearStatusBar();
					pGUI->PrintMessage("Your Now in Step By Step Mode !! the game will start automatically");
					ChosenMode = 1;
					Sleep(2000);
					break;
				}
				if(p.x > 2*80 && p.x < 3*80)
				{
					pGUI->ClearStatusBar();
					pGUI->PrintMessage("Your Now in Silent Mode !! the game results will be in the output file , Check it!!!!!");
					Sleep(2000);
					ChosenMode = 2;
					break;
				}
				else
				{
					pGUI->ClearStatusBar();
					pGUI->PrintMessage("you have clicked on a wrong area plz select one of the 3 modes in the menu bar");
				}
			}
			else
			{
				pGUI->ClearStatusBar();
				pGUI->PrintMessage("you have clicked on a wrong area plz select one of the 3 modes in the menu bar");
			}
		}
		while(!pGameBattle->IsAllEnemiesDead() && !pGameBattle->IsAllTowersDestroyed())
		{
			if(ChosenMode == 0)
				pGUI->GetPointClicked(p);
			// Clear for redrawing
			if(ChosenMode != 2)
			{
				// Clear for redrawing
		        pGUI->ClearStatusBar();
		        pGUI->ClearBattleArea();
		        pGUI->DrawUnpaved(pGameBattle->GetX(0),pGameBattle->GetX(1),pGameBattle->GetX(2),pGameBattle->GetX(3));
		        pGUI->DrawCastle();

		        pGUI->IntializingWidth();
		        pGUI->ResetTextHeight();
		        pGUI->PrintMessage("	       TowerHealth      NoOfActiveEnems      Unpaved Dis      NoOfKilledEnems         ");
		        pGUI->ResetTextWidth();
			}

			pGameBattle->SimpleSimulator();//Updateing the List
	
			// Redraw the enemies
			if(ChosenMode != 2)
			{
				pGUI->ClearStatusBar();
		        pGUI->ClearBattleArea();
                pGUI->DrawUnpaved(pGameBattle->GetX(0),pGameBattle->GetX(1),pGameBattle->GetX(2),pGameBattle->GetX(3));
		        pGUI->DrawCastle();
		        pGameBattle->DrawEnemies(pGUI);
				pGUI->IntializingWidth();
				pGUI->PrintMessage("	       TowerHealth      NoOfActiveEnems      Unpaved Dis      NoOfKilledEnems         ");
		        pGUI->ResetTextWidth();
				pGameBattle->GetCastle()->PrintInfo(pGUI);
			}
		
			if(ChosenMode == 1)
				Sleep(1000);
		}
	

	pGUI->ResetTextWidth();
	pGUI->ResetTextHeight();
	pGUI->ClearStatusBar();
	pGameBattle->DisplaySound();
	if(pGameBattle->IsAllEnemiesDead())
	{
		pGUI->PrintMessage("Victoryyyyy!!!!!Congratulations !!! you have won,Click any where to continue");
	}
	if(!pGameBattle->IsAllEnemiesDead())
	{
		pGUI->PrintMessage("unfortunately you have Lost,Click any where to continue");
	}

	pGUI->GetPointClicked(p);
	delete pGUI;
	pGameBattle->OutputFile();
	delete pGameBattle;
	return 0;
}