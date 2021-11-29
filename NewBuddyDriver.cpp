//Wargame Buddy Version 2
//Created by Charlie Cox
//project started 7/10/2021
//Wargame Buddy Version 2 by Charlie Cox
//File name: NewBuddyDriver.cpp
//The purpose of this program is to create an algorithm that can
//play tabletop war-games with a player so that they may play
//alone. This specific version works with Warlord Games' Bolt Action.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Army.h"
#include "decisionMaker.h"

using namespace Army;
using namespace std;

int main() 
{
    
    army computerArmy;
    int numTurns;
    int currentTurn = 1;
    int extraTurns;
    int numMoves = 0;
    

    cout << "Hello! Welcome to Bolt Action Wargame Buddy!" << endl;

    computerArmy.setArmyNationality();
    computerArmy.intakeUnits(); 

    cout << "How many turns will the game be?" << endl;
    cin >> numTurns;

    while (numTurns < 1)
    {
        cout << "That is an invalid choice. Try again:" << endl;
        cin >> numTurns;
    }

    cout << "Very Well! Let the game begin! " << endl;
    
    int armySize = computerArmy.getArmySize(); 

    while (currentTurn <= numTurns)
    {
        while (numMoves < armySize) 
        {
           computerArmy.checkForPins();
           computerArmy.checkforHits();
           computerArmy.checkForCasualties(); 
           computerArmy.moveUnit();
           ++numMoves;
        }
        numMoves = 0;
        computerArmy.resetArmy(); 
        cout << "That's the end of turn number " << currentTurn << "." << endl;
        computerArmy.statusReport();
        ++currentTurn;
        
    }

    cout << "It looks like that's the end of all the turns! How many extra turns do" 
         << " we need to play? If 0, type 0." << endl;

    cin >> extraTurns;

    if (extraTurns > 0)
    {
        currentTurn = 1;
        while (currentTurn <= extraTurns)
        {
            while (numMoves < armySize)
            {
                computerArmy.checkForPins();
                computerArmy.checkforHits();
                computerArmy.checkForCasualties();
                computerArmy.moveUnit();
                ++numMoves;
            }
            numMoves = 0;
            computerArmy.resetArmy();
            cout << "That's the end of turn number " << currentTurn << ". " << endl;
            computerArmy.statusReport();
            ++currentTurn;
        }
    }

    cout << "It looks like that's the end of the game! I hope it was fun!" << endl;
         
    
    computerArmy.statusReport();

    return EXIT_SUCCESS;

}