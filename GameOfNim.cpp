#include <iostream>
#include <ctime>
#include <windows.h> /*system() , Beep() , Sleep()*/
using namespace std;

#include "GameOfNim.h"

const int SINGLE_PLAYER = 1;
const int MULTIPLAYER = 2;
const int CUSTOM_GAME = 3;
const int HELP = 4;
const int QUIT_GAME = 5;

const int DEFAULT_STICKS_PILE = 51;
const int MAXTAKESTICKS = 4; // Maximum number of sticks that can be taken in a turn

void welcome(void)
{
    cout << "\nLet's play the Game of Nim!" << endl;
}

void menu(void)
{
    int menuChoice;
    do
    {
        cout << endl;
        cout << "Menu:" << endl;
        cout << " 1) Single Player" << endl;
        cout << " 2) Multiplayer" << endl;
        cout << " 3) Custom Game" << endl;
        cout << " 4) Help" << endl;
        cout << " 5) Quit" << endl;
        cout << "Select: ";
        cin >> menuChoice;

        switch(menuChoice)
        {

        case SINGLE_PLAYER:
            {
                Game_Of_Nim(SINGLE_PLAYER);
                break;
            }

        case MULTIPLAYER:
            {
                Game_Of_Nim(MULTIPLAYER);
                break;
            }

        case CUSTOM_GAME:
            {
                Game_Of_Nim(CUSTOM_GAME);
                break;
            }

        case HELP:
            {
                help();
                break;
            }

        case QUIT_GAME:
            {
                menuChoice = QUIT_GAME;
                break;
            }

        default:
            {
                int shutdownJoke = 3;
                cout << "Input invalid! Shutting down computer! in ";

                for(; shutdownJoke >= 0; shutdownJoke--)
                {
                    cout << " "<<shutdownJoke;

                    Beep(550, 300);
                    Sleep(1000);

                }
                menuChoice = QUIT_GAME;
                break;
            }
        }

    }while(menuChoice != QUIT_GAME);
}

void Game_Of_Nim(int gameMode)
{
    bool withAI = false; //false: Play without computer
    int players(0);
    int sticksInStack(0);
    int stickBuffer(0); // Temporarily store the number of sticks to be taken
                        // to see if the input is within the bounds of rules


    //Randomly Choose the player
    srand(time(NULL));
    players = rand()%2;

    switch(gameMode)
    {
        case SINGLE_PLAYER:
            {
                // Set game using the default number of sticks
                sticksInStack = DEFAULT_STICKS_PILE;
                //Play with AI in single Player
                withAI = true;

                checkRemainingStick(sticksInStack);

                // Set game using the default settings
                // Execute game core
                gameOfNimCore(players, sticksInStack, stickBuffer, withAI);

                break;
            }

        case MULTIPLAYER:
            {
                // Set game using the default number of sticks
                sticksInStack = DEFAULT_STICKS_PILE;

                checkRemainingStick(sticksInStack);

                // Set game using the default settings
                // Execute game core
                gameOfNimCore(players, sticksInStack, stickBuffer, withAI);

                break;
            }

        case CUSTOM_GAME:
            {
                cout << "Indicate the number of sticks used in this game: ";
                cin  >> sticksInStack;

                cout << endl;

                int withAIbuff = 0;
                cout << "Play with A.I? Yes = 0; No = 1 :> ";
                cin  >> withAIbuff;

                if(withAIbuff > 0)
                {
                    withAI = false;
                }
                else
                {
                    withAI = true;
                }

                checkRemainingStick(sticksInStack);

                // Set game using the default settings
                // Execute game core
                gameOfNimCore(players, sticksInStack, stickBuffer,withAI );

                systemPause();
                clearScreenConsole();
                break;
            }

        default: //Wrong Game Mode
            {
                int shutdownJoke = 3;
                cout << "Game Mode invalid! Shutting down computer! in ";

                for(; shutdownJoke >= 0; shutdownJoke--)
                {
                    cout << " "<<shutdownJoke;

                    Beep(550, 300);
                    Sleep(1000);

                }
                break;
            }
    }

}

//Switch turns:
//0 = Player 1
//1 = Player 2
void nextPlayer(int& players)
{
    players = (players + 1) % 2;
    cout << "Player# " << players << endl;
}

//Show remaining Sticks in the pile
void checkRemainingStick(const int& sticksInStack)
{
    cout << "There are " << sticksInStack << " sticks the pile" << endl;
}

int takeStick(const int& sticksInStack)
{
    int removeSticks(0);

    cout << "How many sticks do you want to remove (1-4)? ";
    cin >> removeSticks;

    while((removeSticks > 4) || (removeSticks > sticksInStack) || (removeSticks <= 0) )
    {
        cout << "Input invalid! Try another number: " ;
        cin >> removeSticks;

    }

    cout << endl;

    return removeSticks;
}

bool checkInputValid(int takeNSticks, const int& sticksInStack)
{
    bool isValid = false;

    //const int MAXTAKESTICKS = 4;
    //Maximum number of sticks that can be taken in a turn

    //Check if the number of sticks taken is between 1 and 4
    if( (MAXTAKESTICKS >= takeNSticks) && (sticksInStack >= takeNSticks) )
    {
        isValid = true;
        return isValid;
    }
    else
    {
        isValid = false;
        return isValid;
    }
}

void clearScreenConsole()
{
    system("cls");
}

void systemPause()
{
    system("pause");
}

//Missing code for AI
void gameOfNimCore(int& players, int& sticksInStack,int& stickBuffer, bool withAI)
{
    //srand(time(NULL));//Needs to know if this piece of code is redundant
    players = (int)withAI;

    if(withAI)
    {
        while(sticksInStack > 0)//Requires some debugging
        {
            nextPlayer(players); //Get Next Player

            // Temporarily store the number of sticks to be taken
            // to see if the input is within the bounds of rules
            if(players == withAI)
            {
                //Optimal oppening strategy
                stickBuffer = sticksInStack % (MAXTAKESTICKS+1);

                //Check if computer removes at least 1 stick
                if(stickBuffer == 0)
                    stickBuffer = 1;

                cout << "How many sticks do you want to remove (1-4)?(Comp) " << stickBuffer << endl << endl;
            }
            //Human Player's turn
            else
                stickBuffer = takeStick(sticksInStack);

            //Check if Input is valid.
            if(checkInputValid(stickBuffer , sticksInStack))
            {
                //Take the N sticks from the pile; N refers to stickBuffer
                sticksInStack -= stickBuffer;

                //reset buffer to zero
                stickBuffer = 0;
            }
            //Display number of sticks in the stack
            checkRemainingStick(sticksInStack);

            //Check if sticks in the stack is Zero and declare the winner
            if(sticksInStack == 0)
            {
                cout << "Player#" << players << " WINS!" << endl;
            }
        }
    }
    //Without AI
    else
    {
        while(sticksInStack > 0)//Requires some debugging
        {
            nextPlayer(players); //Get Next Player

            // Temporarily store the number of sticks to be taken
            // to see if the input is within the bounds of rules
            stickBuffer = takeStick(sticksInStack);

            if(checkInputValid(stickBuffer , sticksInStack))
            {
                //Take the N sticks from the pile; N refers to stickBuffer
                sticksInStack -= stickBuffer;

                //reset buffer to zero
                stickBuffer = 0;
            }
            //Display number of remaining sticks in the stack
            checkRemainingStick(sticksInStack);

            //Check if sticks in the stack is Zero and declare the winner
            if(sticksInStack == 0)
            {
                cout << "Player#" << players << " WINS!" << endl;
            }
        }
    }

    systemPause();
    clearScreenConsole();
}
void help(void)
{
    cout << "The goal of Nim is to be the player who removes" << endl
         << "the last of 51 sticks from the stack." << endl
         << "A player must remove between 1 - 4 sticks during their turn." << endl
         << "The player who removes the last stick/s wins." << endl;

    systemPause();
    clearScreenConsole();
}
