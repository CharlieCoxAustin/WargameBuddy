//Wargame Buddy Version 2 by Charlie Cox
//File name: Army.h
//The purpose of this program is to create an algorithm that can
//play tabletop war-games with a player so that they may play
//alone. This specific version works with Warlord Games' Bolt Action.

#ifndef DECISIONMAKER_H 
#define DECISIONMAKER_H

#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>
#include <string>

namespace decisionMaker
{
	class decisionMaker
	{
	public:
		decisionMaker();
		decisionMaker(const decisionMaker& src);
		~decisionMaker();

		void assignGeneral(int compTeam);
		int makeDecision(int numLosses, int numPins, int unitsKilled);
		int getaggressionLevel() { return aggressionLevel; }
		std::string getGeneralName() { return generalName; }
		

	private:
		
		int aggressionLevel = 0;
		std::string generalName;



	};

}

#endif
 
