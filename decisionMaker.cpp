//Wargame Buddy Version 2 by Charlie Cox
//File name: Army.h
//The purpose of this program is to create an algorithm that can
//play tabletop war-games with a player so that they may play
//alone. This specific version works with Warlord Games' Bolt Action.

#include "decisionMaker.h"
#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>
#include <string>

using namespace std;
namespace decisionMaker
{

	decisionMaker::decisionMaker()
	{
		cout << "A new instance of decision maker has been created. " << endl;
		aggressionLevel = 0;
		generalName = "not chosen.";
	}

	decisionMaker::decisionMaker(const decisionMaker& src)
	{
		aggressionLevel = src.aggressionLevel;
		generalName = src.generalName;
	}

    decisionMaker::~decisionMaker()
	{
		cout << "Clearing memory of decision maker." << endl;
	}



	void decisionMaker::assignGeneral(int compTeam)
	{

		switch (compTeam) 
		{
		case 1: 
			cout << "I shall be Patton." << endl;
			aggressionLevel = 10;
			generalName = "Patton";
			break;
		case 2:
			cout << "I shall be Montgomery." << endl;
			aggressionLevel = 7;
			generalName = "Montgomery";
			break;
		case 3: 
			cout << "I shall be Zhukov." << endl;
			aggressionLevel = 11;
			generalName = "Zhukov";
			break;
		case 4:
			cout << "I shall be Rommel." << endl;
			aggressionLevel = 9;
			generalName = "Rommel";
			break;
		case 5: 
			cout << "I shall be Yamamoto." << endl;
			aggressionLevel = 9;
			generalName = "Yamamoto";
			break;
		}
	}




	int decisionMaker::makeDecision(int numLosses, int numPins, int unitsKilled)
	{
		int answer = aggressionLevel - (numPins + ((numLosses / 2) + (unitsKilled / 3))); 
		if (answer <= 0)
		{
			return 0;
		}
		else if (answer == 1)
		{
			return 1;
		}
		else if (answer == 2)
		{
			return 2;
		}
		else if(answer == 3)
		{
			return 3;
		}
		else if (answer == 4)
		{
			return 4;
		}
		else
		{
			return 5;
		}
	}

}