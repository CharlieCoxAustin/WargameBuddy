//Wargame Buddy Version 1
//Created by Charlie Cox
//project started 7/10/2021
//The purpose of this program is to create an algorithm that can
//play tabletop war-games with a player so that they may play
//alone. This specific version works with Warlord Games' Bolt Action.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct unit {
   string name;
   int hp;
   bool moved = false;
   bool isAlive = true;
};
//////////////////////////////////////////////////////////////
//Function Name:checkForCasualties
//Parameters:the armySize, the unitsKilled, and the armyArray
//This function checks to see if any units have killed and adjusts
//the unit's isAlive and moved bools.
//////////////////////////////////////////////////////////////


void checkForCasualties(int armySize, int& unitsKilled, unit armyArr[])
{
    char deathChar;
    int deathNum;
    bool validEntry = false;

    while (validEntry == false)
    {
       cout << "Did I lose any units? y for yes and n for no." << endl;
       cin >> deathChar;
       if(deathChar == 'y' || deathChar == 'Y')
       {
          validEntry = true;
          cout << "Oh no! Who?! Pick from this list: " << endl;
          for(int i = 0; i < armySize; ++i)
          {
             cout << i << "." << " " << armyArr[i].name << endl;
          }
          cin >> deathNum;
          armyArr[deathNum].isAlive = false;
          armyArr[deathNum].moved = true;
          ++unitsKilled;
          cout << "We lost " << armyArr[deathNum].name << "? What a tragedy!" << endl
               << "We shall bravely carry on without them. I'll write the letters home."
               << endl;
       }
       else if (deathChar == 'n' || deathChar == 'N')
       {
          validEntry = true;
          cout <<"Phew, that was a close one! I was starting to think that"
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
//Function Name:moraleCheck
//Parameters:the unit number, and the army array
//This function checks to see if the unit has passed its morale
//check. If so, it returns true, if not, it returns false.
//////////////////////////////////////////////////////////////

bool moraleCheck(int unitNum, unit armyArr[])
{
    char moraleResult;
    bool validInput = false;

    while(validInput == false)
    {
       cout << "Did the unit pass their morale test? If no test needed, type y." << endl;
       cin >> moraleResult;
       if(moraleResult == 'y')
       {
           cout << "Glad to hear it! I knew they'd pass." << endl;
           return true;
       }
       else if(moraleResult == 'n')
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
//
//
//
/////////////////////////////////////////////////////////////

void moveAdvance(int armySize, int unitsKilled, int& unitsMoved, unit armyArr[])
{
   bool moveSuccess = false;
   srand((unsigned int)time(NULL));
   int unitNum = rand();
   unitNum = unitNum % armySize;

   while(moveSuccess == false)
   {
      if(unitsKilled + unitsMoved == armySize)
      {
         //cout << "out of units! " << endl; //debug statement
         moveSuccess = true;
      }
      else if(armyArr[unitNum].moved == false && armyArr[unitNum].isAlive == true)
      {
         cout << "I will move " << armyArr[unitNum].name << "." << endl;

         if(moraleCheck(unitNum, armyArr))
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
         if(unitNum < (armySize - 1))
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
//
//
//
/////////////////////////////////////////////////////////////

void moveFire(int armySize, int unitsKilled, int& unitsMoved, unit armyArr[])
{
   bool fireSuccess = false;
   srand((unsigned int)time(NULL));
   int unitNum = rand();
   unitNum = unitNum % armySize;

   while(fireSuccess == false)
   {
      if(unitsKilled + unitsMoved == armySize)
      {
         fireSuccess = true;
      }
      else if(armyArr[unitNum].moved == false && armyArr[unitNum].isAlive == true)
      {
         cout << armyArr[unitNum].name << " will fire!" << endl;

         if(moraleCheck(unitNum, armyArr))
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
         if(unitNum < (armySize - 1))
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
//
//
//
/////////////////////////////////////////////////////////////

void moveRun(int armySize, int unitsKilled, int& unitsMoved, unit armyArr[])
{
   bool runSuccess = false;
   srand((unsigned int)time(NULL));
   int unitNum = rand();
   unitNum = unitNum % armySize;

   while(runSuccess == false)
   {
      if(unitsKilled + unitsMoved == armySize)
      {
         runSuccess = true;
      }
      else if(armyArr[unitNum].moved == false && armyArr[unitNum].isAlive == true)
      {
         cout << armyArr[unitNum].name << " will run!" << endl;

         if(moraleCheck(unitNum, armyArr))
         {
            cout << armyArr[unitNum].name << " runs!" << endl;
         }
         armyArr[unitNum].moved = true;
         runSuccess = true;
         ++unitsMoved;
      }
      else
      {
         //cout << "rearranging unit choice." << endl; //debug statement
         if(unitNum < (armySize - 1))
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
//
//
//
/////////////////////////////////////////////////////////////

void moveRally(int armySize, int unitsKilled, int& unitsMoved, unit armyArr[])
{
   bool rallySuccess = false;
   srand((unsigned int)time(NULL));
   int unitNum = rand();
   unitNum = unitNum % armySize;

   while(rallySuccess == false)
   {
      if(unitsKilled + unitsMoved == armySize)
      {
         rallySuccess = true;
      }
      else if(armyArr[unitNum].moved == false && armyArr[unitNum].isAlive == true)
      {
         cout << armyArr[unitNum].name << " rallies!" << endl
              << "If unit has no hits, advance and shoot(if possible)." << endl;

         armyArr[unitNum].moved = true;
         rallySuccess = true;
         ++unitsMoved;
      }
      else
      {
         //cout << "rearranging unit choice." << endl; //debug statement
         if(unitNum < (armySize - 1))
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
//
//
//
/////////////////////////////////////////////////////////////

void moveAmbush(int armySize, int unitsKilled, int& unitsMoved, unit armyArr[])

{
   bool ambushSuccess = false;
   srand((unsigned int)time(NULL));
   int unitNum = rand();
   unitNum = unitNum % armySize;

   while(ambushSuccess == false)
   {
      if(unitsKilled + unitsMoved == armySize)
      {
         ambushSuccess = true;
      }
      else if(armyArr[unitNum].moved == false && armyArr[unitNum].isAlive == true)
      {
         cout << armyArr[unitNum].name << " will ambush!" << endl;

         if(moraleCheck(unitNum, armyArr))
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
         if(unitNum < (armySize - 1))
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
//
//
//
/////////////////////////////////////////////////////////////

void moveDown(int armySize, int unitsKilled, int& unitsMoved, unit armyArr[])

{
   bool downSuccess = false;
   srand((unsigned int)time(NULL));
   int unitNum = rand();
   unitNum = unitNum % armySize;

   while(downSuccess == false)
   {
      if(unitsKilled + unitsMoved == armySize)
      {
         downSuccess = true;
      }
      else if(armyArr[unitNum].moved == false && armyArr[unitNum].isAlive == true)
      {
         cout << armyArr[unitNum].name << " goes down!" << endl;
         armyArr[unitNum].moved = true;
         downSuccess = true;
         ++unitsMoved;
      }
      else
      {
         //cout << "rearranging unit choice." << endl; //debug statement
         if(unitNum < (armySize - 1))
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


//////////////////////////////////////////////////////////////
//Function Name:moveUnit
//Parameters:the armySize and the army array
//This function picks a unit at random and tells the user to
//move them.
//////////////////////////////////////////////////////////////

void moveUnit(int armySize, int unitsKilled, int& unitsMoved, unit armyArr[])
{
   srand((unsigned int)time(NULL));
   int moveChoice = rand();
   moveChoice = moveChoice % 6;

   switch(moveChoice)
   {
      case 0:
         cout << "Advance!" << endl;
         moveAdvance(armySize, unitsKilled, unitsMoved, armyArr);
         break;
      case 1:
         cout << "Fire!" << endl;
         moveFire(armySize, unitsKilled, unitsMoved, armyArr);
         break;
      case 2:
         cout << "Run!" << endl;
         moveRun(armySize, unitsKilled, unitsMoved, armyArr);
         break;
      case 3:
         cout << "Rally!" << endl;
         moveRally(armySize, unitsKilled, unitsMoved, armyArr);
         break;
      case 4:
         cout << "Ambush!" << endl;
         moveAmbush(armySize, unitsKilled, unitsMoved, armyArr);
         break;
      case 5:
         cout << "Down!" << endl;
         moveDown(armySize, unitsKilled, unitsMoved, armyArr);
         break;
   }

}

//////////////////////////////////////////////////////////////
//Function Name:intakeUnits
//Parameters:army size, the army array
//This function reads in the units from the user and stores them in
//an array.
//////////////////////////////////////////////////////////////

void intakeUnits(int armySize, unit armyArr[])
{
   cout << "What units do I have under my command today?" << endl;

   cout << "Hint: If there are multiple units with the same name, "
        << endl << "give them a number so you don't get them confused."
        << endl;

   for (int i = 0; i < armySize; ++i)
   {
       cout << "What is the name of unit " << i + 1 << "?" << endl;

       getline(cin,armyArr[i].name);

       cout << "How many people are in the unit?: " << endl;

       cin >> armyArr[i].hp;
       cin.ignore();
   }

   cout << "Very well! Read over my order of battle to make sure no egregious"
        << " errors have been made!" << endl;

   for (int i = 0; i < armySize; ++i)
   {
       cout << "unit " << i + 1 << ": " << armyArr[i].name << "/ strength: "
            << armyArr[i].hp << endl;
   }
}

//////////////////////////////////////////////////////////////
//Function Name:main
//Parameters:none
//This is the main function.
//////////////////////////////////////////////////////////////

int main (){

   int buddyNationality;
   string compTeam;
   int armySize;
   int unitsMoved = 0;
   int numTurns;
   int numExtraTurns;
   int currentTurn = 1;
   int unitsKilled = 0;
   bool slaughter = false;

   string US = "The United States";
   string UK = "The United Kingdom";
   string USSR = "The Soviet Union";
   string G = "Germany";
   string J = "Japan" ;

//the below will be made a function called "introduction."

   cout  << "Hello! Welcome to Bolt Action Wargame Buddy!" << endl
         << "Which army would you like me to control for you?" << endl
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
            case 1: compTeam = US;
               break;
            case 2: compTeam = UK;
               break;
            case 3: compTeam = USSR;
               break;
            case 4: compTeam = G;
               break;
            case 5: compTeam = J;
               break;
         }

   cout << "Very well! I shall control the army of " << compTeam << "!"
        << endl << "How many units shall I control?" << endl;

   cin >> armySize;
   cin.ignore();

   unit armyArr[armySize];

   cout << "Excellent! I will control " << armySize << " units from the "
        << "army of " << compTeam << "!" << endl;


   intakeUnits(armySize, armyArr);//this reads in the units into the army array.


   cout << "How many turns will this game be? " << endl;
   cin  >> numTurns;
   cout << "Very well! We shall play a game for " << numTurns << " turns." << endl;
   cout << "Let the game begin! " << endl;

   while(currentTurn <= numTurns)
   {
      while(unitsMoved + unitsKilled < armySize)
      {
         checkForCasualties(armySize, unitsKilled, armyArr);
         moveUnit(armySize, unitsKilled, unitsMoved, armyArr);
         char nextMove = 'n';

         while(nextMove != 'y')
         {
            cout << "Type y when you wish me to move again." << endl;
            cin >> nextMove;

            if(nextMove != 'y')
            {
               cout << "That key is invalid. Try again." << endl;
            }
         }
         //cout << "units Moved = " << unitsMoved << endl //debug statements
         //     << "armySize = " << armySize << endl;
      }
      if(unitsKilled == armySize)
      {
         cout << "All my units are dead! I have lost the game! What a terrible tragedy."
              << endl << endl;
         currentTurn = numTurns + 1;
         slaughter = true;
      }
      else
      {
         cout << "It looks like it's the end of turn number " << currentTurn << "."
              << endl;
         ++currentTurn;
         unitsMoved = 0;

         cout << "Here is my army at this point: " << endl;

         for(int i = 0; i < armySize; ++i)
         {
            if(armyArr[i].isAlive == true)
            {
               cout << armyArr[i].name << endl;
            }
            else
            {
               cout << armyArr[i].name << " (deceased)" << endl;
            }
         }

         for(int i = 0; i < armySize; ++i)
         {
            armyArr[i].moved = false;
         }
      }
   }

   if(slaughter == false)
   {
   cout << "How many extra turns will there be? If none, enter 0" << endl;
   cin >> numExtraTurns;

      if(numExtraTurns > 0)
      {
         currentTurn = 1;
         while(currentTurn <= numExtraTurns)
         {
            while(unitsMoved + unitsKilled < armySize)
            {
               moveUnit(armySize, unitsKilled, unitsMoved, armyArr);
               char nextMove = 'n';

               while(nextMove != 'y')
               {
                  cout << "Type y when you wish me to move again." << endl;
                  cin >> nextMove;

                  if(nextMove != 'y')
                  {
                     cout << "That key is invalid. Try again." << endl;
                  }
               }
            }
            cout << "It looks like it's the end of turn number " << currentTurn << "."
                 << endl;
            ++currentTurn;
            unitsMoved = 0;

            for(int i = 0; i < armySize; ++i)
            {
               if(armyArr[i].isAlive == true)
               {
                  armyArr[i].moved = false;
               }
            }
            cout << "Here is my army at this point: " << endl;

            for(int i = 0; i < armySize; ++i)
            {
               if(armyArr[i].isAlive == true)
               {
                  cout << armyArr[i].name << endl;
               }
               else
               {
                  cout << armyArr[i].name << " (deceased)" << endl;
               }
            }

         }

      }
   }

   cout << "It looks like that's the end of the Game! I hope it was fun!" << endl;

   cout << "Here's the list of the units in my army and their statuses at the end of the game."
        << endl << endl;

   for(int i = 0; i < armySize; ++i)
   {
      if(armyArr[i].isAlive == true)
      {
         cout << armyArr[i].name << endl;
      }
      else
      {
         cout << armyArr[i].name << " (deceased)" << endl;
      }
   }

}

