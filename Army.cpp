//Wargame Buddy Version 2 by Charlie Cox
//File name: Army.cpp
//The purpose of this program is to create an algorithm that can
//play tabletop war-games with a player so that they may play
//alone. This specific version works with Warlord Games' Bolt Action.


#include "Army.h"
#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>
#include "decisionMaker.h"


using namespace std;
namespace Army
{

    //////////////////////////////////////////////////////////////
    //Function Name: army
    //This is a constructor.
    //It should instantiate a blank instance of army.
    //////////////////////////////////////////////////////////////

    army::army(): unitsKilled(0), unitsMoved(0), armySize(1)
    {
        cout << "A new instance of army has been created." << endl;
        armyArr = new unit[armySize];
    }

   //////////////////////////////////////////////////////////////
   //Function Name: army
   //This is a copy constructor.
   //It should instantiate a copy of instance src.
   //////////////////////////////////////////////////////////////

    army::army(const army& src)
    {
        unitsKilled = src.unitsKilled;
        unitsMoved = src.unitsMoved;
        armySize = src.armySize;
        armyArr = new unit[src.armySize];

        for (int i = 0; i < src.armySize; ++i)
        {
            armyArr[i].name = src.armyArr[i].name;
            armyArr[i].hp = src.armyArr[i].hp;
            armyArr[i].moved = src.armyArr[i].moved;
            armyArr[i].isAlive = src.armyArr[i].isAlive;
            armyArr[i].numPins = src.armyArr[i].numPins;
        }
    }

    //////////////////////////////////////////////////////////////
   //Function Name: ~army
   //This is a destructor.
   //It should delete the dynamic memory.
   //////////////////////////////////////////////////////////////

    army::~army()
    {
        cout << "Deleting army and clearing memory." << endl;

        delete [] armyArr;
        armyArr = nullptr;
    }

    //////////////////////////////////////////////////////////////
   //Function Name: setArmyNationality
   //This sets the army's nationality based on user input.
   //////////////////////////////////////////////////////////////

    void army::setArmyNationality()
    {
        int buddyNationality;
        

       cout << "Which army would you like me to control for you?" << endl
            << "Please enter the number which corresponds to your choice: " << endl
            << "1. The United States" << endl
            << "2. The United Kingdom" << endl
            << "3. The USSR" << endl
            << "4. Germany" << endl
            << "5. Japan" << endl;

       cin >> buddyNationality;

       while (buddyNationality > 5 || buddyNationality < 1)
       {
           cout << "That number is not an option. Please try again: " << endl;
           cin >> buddyNationality;
       }

       switch (buddyNationality)
       {
       case 1: compTeam = "The United States";
           break;
       case 2: compTeam = "The United Kingdom";
           break;
       case 3: compTeam = "The Soviet Union";
           break;
       case 4: compTeam = "Germany";
           break;
       case 5: compTeam = "Japan";
           break;
       }

       cout << "Very well! I shall control the army of " << compTeam << "!" << endl;

       general.assignGeneral(buddyNationality);


    }

    //////////////////////////////////////////////////////////////
    //Function Name: statusReport
    //This function prints the status of the computer controlled
    //army.
    //////////////////////////////////////////////////////////////

    void army::statusReport()
    {
        cout << "Here is the status of my army at this point: " << endl;

        for (int i = 0; i < armySize; ++i)
        {
            if (armyArr[i].isAlive == true)
            {
                cout << "unit " << i + 1 << ": " << armyArr[i].name
                    << ", members: " << armyArr[i].hp
                    << ", pins: " << armyArr[i].numPins
                    << ", casualties: " << armyArr[i].numLosses << endl; 
            }
            else
            {
                cout << "unit " << i + 1 << ": " << armyArr[i].name << " (destroyed)" << endl;
            }
        }
    }


   //////////////////////////////////////////////////////////////
   //Function Name: checkForCasualties
   //This function checks to see if the army has taken
   //any casualties, specifically if a unit has been killed.
   //////////////////////////////////////////////////////////////

    void army::checkForCasualties()
    {
        char deathChar;
        int deathNum;
        bool validEntry = false;

        while (validEntry == false)
        {
            cout << "Did I lose any units? y for yes and n for no." << endl;
            cin >> deathChar;
            if (deathChar == 'y' || deathChar == 'Y')
            {
                validEntry = true;
                cout << "Oh no! Who?! Pick from this list: " << endl;
                for (int i = 0; i < armySize; ++i)
                {
                    cout << i << "." << " " << armyArr[i].name << endl;
                }
                cin >> deathNum;
                armyArr[deathNum].isAlive = false;
                if (armyArr[deathNum].moved == true)
                {
                    armyArr[deathNum].moved = false;
                    --unitsMoved;
                }
                ++unitsKilled;
                cout << "We lost " << armyArr[deathNum].name << "? What a tragedy!" << endl
                    << "We shall bravely carry on without them. I'll write the letters home."
                    << endl;
            }
            else if (deathChar == 'n' || deathChar == 'N')
            {
                validEntry = true;
                cout << "Phew, that was a close one! I was starting to think that"
                    << " maybe wars are bad! " << endl;
            }
            else
            {
                cout << "That isn't a valid entry. Try again." << endl;
            }
        }

        //cout << unitsKilled << " units have been killed." << endl; //debug statement

    }

    //////////////////////////////////////////////////////////////
    //Function Name:checkForPins
    //Parameters:none
    //This function asks the user if there have been pins.
    //////////////////////////////////////////////////////////////

    void army::checkForPins()
    {
        int unitNumber;
        int numberOfPins;
        char pinChar;
        bool pinBool = false;

        cout << "Did any of my units take pins? " << endl;
        cin >> pinChar;

        while (pinBool == false)
        {
            if (pinChar == 'y' || pinChar == 'Y')
            {
                for (int i = 0; i < armySize; ++i)
                {
                    cout << i << ": " << armyArr[i].name << endl;
                }

                cin >> unitNumber;

                while (unitNumber >= armySize || unitNumber < 0)
                {
                    cout << "That's not a valid choice. Try again:" << endl;
                    cin >> unitNumber;
                }

                cout << "How many pins?" << endl;
                cin >> numberOfPins;

               addPins(unitNumber, numberOfPins); 

                cout << armyArr[unitNumber].name << " now has " << numberOfPins << " pins." << endl;
                pinBool = true;
            }
            else if (pinChar == 'n' || pinChar == 'N')
            {
                cout << "No additional pins added." << endl;
                pinBool = true;
            }
            else
            {
                cout << "That is not a valid input. Try Again: " << endl;
                cin >> pinChar;
            }
        }
         
    }


    //////////////////////////////////////////////////////////////
    //Function Name:addPins
    //Parameters:none
    //This function adds 1 or more pins to the unit's number of pins.
    //////////////////////////////////////////////////////////////

    void army::addPins(int unitNumber, int newPins)
    {
        armyArr[unitNumber].numPins += newPins; 
    }


    //////////////////////////////////////////////////////////////
    //Function Name: checkForHits
    //This function checks to see if the army has taken
    //any casualties, specifically if a unit has taken damage
    //////////////////////////////////////////////////////////////

    void army::checkforHits()
    {
        int unitNumber;
        int numberOfHits;
        char hitChar;
        bool hitBool = false;

        cout << "Did any of my units take losses? " << endl;
        cin >> hitChar;

        while (hitBool == false)
        {
            if (hitChar == 'y' || hitChar == 'Y')
            {
                for (int i = 0; i < armySize; ++i)
                {
                    cout << i << ": " << armyArr[i].name << endl;
                }

                cin >> unitNumber;

                while (unitNumber >= armySize || unitNumber < 0)
                {
                    cout << "That's not a valid choice. Try again:" << endl;
                    cin >> unitNumber;
                }

                cout << "How many losses?" << endl;
                cin >> numberOfHits;

                addLosses(unitNumber, numberOfHits);

                cout << armyArr[unitNumber].name << " now has " << armyArr[unitNumber].hp << " members." << endl;
                hitBool = true;

                if (armyArr[unitNumber].hp == 0)
                {
                    cout << armyArr[unitNumber].name << " is out of hp! They're dead! " << endl;
                    armyArr[unitNumber].isAlive = false;
                    ++unitsKilled;
                    if (armyArr[unitNumber].moved == true)
                    {
                        armyArr[unitNumber].moved = false;
                        --unitsMoved; 
                    }
                }
            }
            else if (hitChar == 'n' || hitChar == 'N')
            {
                cout << "No additional losses added." << endl;
                hitBool = true;
            }
            else
            {
                cout << "That is not a valid input. Try Again: " << endl;
                cin >> hitChar; 
            }
        }
    }

    //////////////////////////////////////////////////////////////
    //Function Name:addLosses
    //Parameters:none
    //This function subtracts 1 or more hits to the unit's hp.
    //////////////////////////////////////////////////////////////

    void army::addLosses(int unitNumber, int newHits)
    {
        armyArr[unitNumber].hp -= newHits;
        armyArr[unitNumber].numLosses += newHits; 
    }


    //////////////////////////////////////////////////////////////
    //Function Name:moraleCheck
    //Parameters:the unit number, and the army array
    //This function checks to see if the unit has passed its morale
    //check. If so, it returns true, if not, it returns false.
    //////////////////////////////////////////////////////////////

    bool army::moraleCheck(int unitChoice)
    {
        char moraleResult;
        bool validInput = false;

        while (validInput == false)
        {
            cout << "Did the unit pass their morale test? If no test needed, type y." << endl;
            cin >> moraleResult;
            if (moraleResult == 'y' || moraleResult == 'Y')
            {
                cout << "Glad to hear it! I knew they'd pass." << endl;
                if (armyArr[unitChoice].numPins > 0)
                {
                   --armyArr[unitChoice].numPins;
                }
                return true;
            }
            else if (moraleResult == 'n' || moraleResult == 'N')
            {
                cout << "What?! This is a shameful display! " << endl;
                return false;
            }
            else
            {
                cout << "That is an invalid input. Try again. " << endl;
            }
        }
    }
    /////////////////////////////////////////////////////////////
    //Function Name: moveAdvance
    //This function tells the user to advance the given unit.
    /////////////////////////////////////////////////////////////

    void army::moveAdvance(int unitChoice)
    {
        //cout << "Inside advance." << endl;
        bool moveSuccess = false;
        srand((unsigned int)time(NULL));
        int unitNum = rand();
        unitNum = unitNum % armySize;
        //cout << "unit num = " << unitNum << endl;
        while (moveSuccess == false)
        {
            if (unitsKilled + unitsMoved == armySize)
            {
                //cout << "out of units! " << endl; //debug statement
                moveSuccess = true;
            }
            else if (armyArr[unitNum].moved == false && armyArr[unitNum].isAlive == true)
            {
                cout << "I will move " << armyArr[unitNum].name << "." << endl;

                if (moraleCheck(unitChoice))
                {
                    cout << "Move " << armyArr[unitNum].name << " advance distance "
                        << "into closest cover (if possible) and "
                        << "shoot at the closest unit (if possible). " << endl;
                }
                armyArr[unitNum].moved = true;
                moveSuccess = true;
                ++unitsMoved;
            }
            else
            {
                //cout << "rearranging unit choice." << endl; //debug statement
                if (unitNum < (armySize - 1))
                {
                    ++unitNum;
                }
                else
                {
                    unitNum = 0;
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////
    //function name: moveFire
    //This function tells the user to fire the given unit.
    /////////////////////////////////////////////////////////////

    void army::moveFire(int unitChoice)
    {
        //cout << "Inside fire." << endl;
        bool fireSuccess = false;
        srand((unsigned int)time(NULL));
        int unitNum = rand();
        unitNum = unitNum % armySize;
        //cout << "unit num = " << unitNum << endl;
        while (fireSuccess == false)
        {
            if (unitsKilled + unitsMoved == armySize)
            {
                fireSuccess = true;
            }
            else if (armyArr[unitNum].moved == false && armyArr[unitNum].isAlive == true)
            {
                cout << armyArr[unitNum].name << " will fire!" << endl;

                if (moraleCheck(unitChoice))
                {
                    cout << armyArr[unitNum].name << " fires at the nearest enemy unit!" << endl;
                }
                armyArr[unitNum].moved = true;
                fireSuccess = true;
                ++unitsMoved;
            }
            else
            {
                //cout << "rearranging unit choice." << endl; //debug statement
                if (unitNum < (armySize - 1))
                {
                    ++unitNum;
                }
                else
                {
                    unitNum = 0;
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////
    //function name: moveRun
    //This function tells the user to run the current unit.
    /////////////////////////////////////////////////////////////

    void army::moveRun(int unitChoice)
    {
        //cout << "Inside run." << endl;
        bool runSuccess = false;
        srand((unsigned int)time(NULL));
        int unitNum = rand();
        unitNum = unitNum % armySize;
        //cout << "unit num = " << unitNum << endl;
        while (runSuccess == false)
        {
            if (unitsKilled + unitsMoved == armySize)
            {
                runSuccess = true;
            }
            else if (armyArr[unitNum].moved == false && armyArr[unitNum].isAlive == true)
            {
                cout << armyArr[unitNum].name << " will run!" << endl;

                if (moraleCheck(unitChoice))
                {
                    cout << armyArr[unitNum].name << " runs! IF within assault range, assault!" << endl;
                }
                armyArr[unitNum].moved = true;
                runSuccess = true;
                ++unitsMoved;
            }
            else
            {
                //cout << "rearranging unit choice." << endl; //debug statement
                if (unitNum < (armySize - 1))
                {
                    ++unitNum;
                }
                else
                {
                    unitNum = 0;
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////
    //function name: moveRally
    //This function tells the user to rally the given unit.
    /////////////////////////////////////////////////////////////

    void army::moveRally(int unitChoice)
    {
        //cout << "Inside rally." << endl;
        bool rallySuccess = false;
        srand((unsigned int)time(NULL));
        int unitNum = rand();
        unitNum = unitNum % armySize;
        //cout << "unit num = " << unitNum << endl;
        while (rallySuccess == false)
        {
            if (unitsKilled + unitsMoved == armySize)
            {
                rallySuccess = true;
            }
            else if (armyArr[unitNum].moved == false && armyArr[unitNum].isAlive == true) 
            {
                cout << armyArr[unitNum].name << " rallies!" << endl
                    << "If unit has no hits, advance and shoot(if possible)." << endl;

                if (armyArr[unitNum].numPins > 0)
                {
                    --armyArr[unitNum].numPins;
                }

                armyArr[unitNum].moved = true;
                rallySuccess = true;
                ++unitsMoved;
            }
            else
            {
                //cout << "rearranging unit choice." << endl; //debug statement
                if (unitNum < (armySize - 1))
                {
                    ++unitNum;
                }
                else
                {
                    unitNum = 0;
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////
    //function name: moveAmbush
    //This function tells the user to ambush the given unit.
    /////////////////////////////////////////////////////////////

    void army::moveAmbush(int unitChoice)

    {
        //cout << "Inside ambush." << endl;
        bool ambushSuccess = false;
        srand((unsigned int)time(NULL));
        int unitNum = rand();
        unitNum = unitNum % armySize;
        //cout << "unit num = " << unitNum << endl;
        while (ambushSuccess == false)
        {
            if (unitsKilled + unitsMoved == armySize)
            {
                ambushSuccess = true;
            }
            else if (armyArr[unitNum].moved == false && armyArr[unitNum].isAlive == true)
            {
                cout << armyArr[unitNum].name << " will ambush!" << endl;

                if (moraleCheck(unitChoice)) 
                {
                    cout << armyArr[unitNum].name << " sets an ambush!" << endl;
                }
                armyArr[unitNum].moved = true;
                ambushSuccess = true;
                ++unitsMoved;
            }
            else
            {
                //cout << "rearranging unit choice." << endl; //debug statement
                if (unitNum < (armySize - 1))
                {
                    ++unitNum;
                }
                else
                {
                    unitNum = 0;
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////
    //function name: moveDown
    //This function tells the user to make the given unit go down.
    /////////////////////////////////////////////////////////////

    void army::moveDown()

    {
        //cout << "Inside down." << endl;
        bool downSuccess = false;
        srand((unsigned int)time(NULL));
        int unitNum = rand();
        unitNum = unitNum % armySize;
        //cout << "unit num = " << unitNum << endl;
        while (downSuccess == false)
        {
            if (unitsKilled + unitsMoved == armySize)
            {
                downSuccess = true;
            }
            else if (armyArr[unitNum].moved == false && armyArr[unitNum].isAlive == true)
            {
                cout << armyArr[unitNum].name << " goes down!" << endl;
                armyArr[unitNum].moved = true;
                downSuccess = true;
                ++unitsMoved;
            }
            else
            {
                //cout << "rearranging unit choice." << endl; //debug statement
                if (unitNum < (armySize - 1))
                {
                    ++unitNum;
                }
                else
                {
                    unitNum = 0;
                }
            }
        }
    }


    /////////////////////////////////////////////////////////////
    //function name: chooseUnit
    //This function picks a unit to move.
    /////////////////////////////////////////////////////////////

    int army::chooseUnit()
    {
        srand((unsigned int)time(NULL));
        int unitChoice = rand();
        unitChoice = unitChoice % armySize;
        bool unitFound = false;

        while (unitFound == false)
        {
            if (unitsKilled + unitsMoved == armySize)
            {
                unitFound = true;
                return -1;
            }
            else if (armyArr[unitChoice].moved == false && armyArr[unitChoice].isAlive == true)
            {
                unitFound = true;
                return unitChoice;
            }
            else if (armyArr[unitChoice].moved == true || armyArr[unitChoice].isAlive == false)
            {
                if (unitChoice < armySize)
                {
                   ++unitChoice;
                }
                else
                {
                    unitChoice = 0;
                }
            }
        }
    }


    //////////////////////////////////////////////////////////////
    //Function Name:moveUnit
    //Parameters:the armySize and the army array
    //This function picks a type of move at random and calls the 
    //appropriate move function.
    //////////////////////////////////////////////////////////////

    void army::moveUnit()
    {
        srand((unsigned int)time(NULL));
        int moveChoice = rand();
        moveChoice = moveChoice % 6;
        
        int unitChoice = chooseUnit();
        moveChoice = general.makeDecision(armyArr[unitChoice].numLosses, armyArr[unitChoice].numPins, unitsKilled);

        switch (moveChoice)
        {
        case -1:
            cout << "All of my units have moved! " << endl;
            break;
        case 0:
            //cout << "Down!" << endl;
            moveDown();
            break;
        case 1:
            //cout << "Rally!" << endl;
            moveRally(unitChoice);
            break;
        case 2:
            //cout << "Ambush!" << endl;
            moveAmbush(unitChoice);
            break;
        case 3:
            //cout << "Fire!" << endl;
            moveFire(unitChoice);
            break;
        case 4:
            //cout << "Advance!" << endl;
            moveAdvance(unitChoice);
            break;
        case 5:
            //cout << "Run!" << endl;
            moveRun(unitChoice);
            break;
        }

    }

    //////////////////////////////////////////////////////////////
    //Function Name:resetUnitBooleans
    //Parameters:none
    //This function resets the boolean values for the units in the array.
    //////////////////////////////////////////////////////////////

    void army::resetArmy()
    {
        for (int i = 0; i < armySize; ++i)
        {
           armyArr[i].moved = false;   
        }

        unitsMoved = 0;
    }



    //////////////////////////////////////////////////////////////
    //Function Name:intakeUnits
    //Parameters:army size, the army array
    //This function reads in the units from the user and stores them in
    //a dynamic array.
    //////////////////////////////////////////////////////////////

    void army::intakeUnits()
    {
        cout << "How many units do I command? " << endl;

        setArmySize();

        unit* newarmyArr = new unit[armySize];
        unit* oldArmyArr = armyArr;
        armyArr = newarmyArr;
        delete[] oldArmyArr;
        oldArmyArr = nullptr;

        cout << "Very Well! I will control " << armySize << " units from " << compTeam << endl;

        cout << "What units do I have under my command today?" << endl;

        cout << "Hint: If there are multiple units with the same name, " << endl 
             << "give them a number so you don't get them confused." << endl;

        for (int i = 0; i < armySize; ++i)
        {
            cout << "What is the name of unit " << i + 1 << "?" << endl;

            cin.get();
            getline(cin, armyArr[i].name);

            cout << "How many people are in the unit?: " << endl;
            
            
            cin >> armyArr[i].hp;
            
            
        }

        cout << "Very well! Read over my order of battle to make sure no egregious"
            << " errors have been made!" << endl;

        for (int i = 0; i < armySize; ++i)
        {
            cout << "unit " << i + 1 << ": " << armyArr[i].name << "/ strength: "
                << armyArr[i].hp << endl;
        }
    }

}


