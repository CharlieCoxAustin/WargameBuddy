//Wargame Buddy Version 2 by Charlie Cox
//File name: Army.h
//The purpose of this program is to create an algorithm that can
//play tabletop war-games with a player so that they may play
//alone. This specific version works with Warlord Games' Bolt Action.

#ifndef ARMY_H
#define ARMY_H

#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>
#include <string>
#include "decisionMaker.h"


namespace Army
{
	class army
	{
	public:
		army();
		army(const army& src);
		~army();

		decisionMaker::decisionMaker general; 
		void checkForCasualties();
		bool moraleCheck(int unitChoice);
		void moveAdvance(int unitChoice);
		void moveFire(int unitChoice);
		void moveRun(int unitChoice);
		void moveRally(int unitChoice);
		void moveAmbush(int unitChoice);
		void moveDown();
		void moveUnit();
		void intakeUnits();
		void setArmySize() { std::cin >> armySize;  }
		void setArmyNationality();
		void incrementUnitsKilled() { ++unitsKilled;  }
		void incrementUnitsMoved() { ++unitsMoved; }
		int getArmySize() { return armySize;  }
		void resetArmy();
		void statusReport();
		void addPins(int unitNumber, int newPins); 
		void checkForPins(); 
		void checkforHits();
		void addLosses(int unitNumber, int newHits); 
		int chooseUnit();

	private:
		struct unit {
			std::string name; 
			int hp;
			bool moved = false;
			bool isAlive = true;
			int numPins = 0;
			int numLosses = 0;
		};

		unit* armyArr;
		std::string compTeam;
		int armySize;
		int unitsKilled;
		int unitsMoved;
	};

}

#endif

