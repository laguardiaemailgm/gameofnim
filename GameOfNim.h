#ifndef GAME_OF_NIM
#define GAME_OF_NIM

void welcome(void);
void menu(void);
void help(void);

void Game_Of_Nim(int); //Set-ups the game settings
void gameOfNimCore(int&,int&,int&,bool);// Core of the Game

void nextPlayer(int&); // Switch player
int takeStick(const int&);    //Take stick from the stack of sticks

bool checkInputValid(int ,const int& ); //Check if user input is valid
void checkRemainingStick(const int&);  //Displays Number of Remaining Sticks

void clearScreenConsole(void);
void systemPause(void);

#endif // GAME_OF_NIM
