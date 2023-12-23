#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>

using namespace std;
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum rockpapersissor {rock = 1 , paper = 2 , sissor = 3};
enum enWinner {Player1 = 1 , Computer = 2 , Draw = 3};
int RandomNumber(int From, int To)
{
    //Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}
struct stRoundInfo
{
    short RoundNumber = 0 ;
    enGameChoice Player1Choice ;
    enGameChoice ComputerChoice ;
    enWinner Winner ;
    string WinnerName;
};
struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short Computer2WinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};
string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1","Computer","No Winner"};
    return arrWinnerName[Winner - 1];
}
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }
    switch (RoundInfo.Player1Choice)
    {
        case enGameChoice::Stone:
            if (RoundInfo.ComputerChoice == enGameChoice::Paper)
            {
                return enWinner::Computer;
            }
            break;
        case enGameChoice::Paper:
                 if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
                    {
                        return enWinner::Computer;
                    }
                break;
        case enGameChoice::Scissors:
             if (RoundInfo.ComputerChoice == enGameChoice::Stone)
                {
                    return enWinner::Computer;
                }
            break;
    }
                //if you reach here then player1 is the winner.
    return enWinner::Player1;
}
string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Stone","Paper","Scissors" };
    return arrGameChoices[Choice - 1];
}
void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
            case enWinner::Player1:
                system("color 2F");
            //turn screen to Greenbreak;
            case enWinner::Computer:
                system("color 4F");
                 //turn screen to Red
                cout << "\a"; break;
            default:
                system("color 6F");
                //turn screen to Yellowbreak;
    }
}
void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1  Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "] \n";
    cout << "__________________________________\n" << endl;
    SetWinnerScreenColor(RoundInfo.Winner);
}
enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes)
        return enWinner::Computer;
    else return enWinner::Draw;
}
stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;
    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.Computer2WinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);
    return GameResults;
}
enGameChoice ReadPlayer1Choice()
{
    short Choice = 1;
    do
        {
            cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
            cin >> Choice;
        }
    while (Choice < 1 || Choice >3);
return (enGameChoice)Choice;
}
enGameChoice GetComputerChoice()
{
    return  (enGameChoice) RandomNumber(1, 3);
}
stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
        {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);
        //Increase win/Draw counters
        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
                ComputerWinTimes++;
        else
            DrawTimes++;
            PrintRoundResults(RoundInfo);
        }
        return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}
string  Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i < NumberOfTabs; i++)
        {
        t = t + "\t";
        cout << t;
        }
    return t;
}
void ShowGameOverScreen()
{
    cout << Tabs(2) << "__________________________________________________________\n\n";
    cout << Tabs(2) << "                 +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "__________________________________________________________\n\n";
}
void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
    cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 won times  : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer won times : " << GameResults.Computer2WinTimes << endl;
    cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "___________________________________________________________\n";
    SetWinnerScreenColor(GameResults.GameWinner);
}
short ReadHowManyRounds()
{
    short GameRounds = 1;
    do
    {
        cout << "How Many Rounds 1 to 10 ? \n";
        cin >> GameRounds;
    }
    while (GameRounds < 1 || GameRounds >10);
    return GameRounds;
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}
void StartGame()
{
    char PlayAgain = 'Y';
    do
        {
            ResetScreen();
            stGameResults
            GameResults = PlayGame(ReadHowManyRounds());
            ShowGameOverScreen();
            ShowFinalGameResults(GameResults);
            cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
            cin >> PlayAgain;
        }
    while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int readpositivenum(string message)
{
    int num = 0 ;
    do
    {
        cout << message << endl ;
        cin >> num ;
    }
    while (num < 0 && num > 3);
    return num;
}
rockpapersissor checknumber(int number)
{
        switch (number)
        {
            case 1 :
                return rockpapersissor :: rock ;
            case 2 :
                return rockpapersissor :: paper ;
            case 3 :
                return rockpapersissor :: sissor ;
        }
}
string tabs(int number)
{
    string t = "" ;
    for (int i = 0 ; i < number ; i++)
        t += "\t" ;
    return t ;
}
void game()
{
    cout << "\t\t|| ROCK || PAPER || SCISSOR ||\n\n\n";
    cout << "Rock = 1 , Paper = 2 , Scissor = 3\n";
    bool c = NULL ;
    do
    {
        int numberofrounds = readpositivenum("How many rounds do you want to play ?"),playercounter = 0 ,computercounter = 0;
        for (int i = 1 ; i <= numberofrounds ; i++)
        {
            cout << "Round[" << i << "] begins : \n\n";
            int player = readpositivenum("Enter a number from 1 to 3"),computer = RandomNumber(1,3) ;
            checknumber(player);
            checknumber(computer);
            if (player == rock)
            {
                if (computer == sissor)
                {
                    cout << " __________Round[" << i << "]__________ \n" ;
                    playercounter++ ;
                    cout << "You: Rock\nComputer: Scissor\n" << "You : " << playercounter << "\nComputer : " << computercounter << "\n";
                    system("Color 2f") ;
                    cout << " ____________________________ \n" ;
                }
                else if (computer == paper)
                {
                    cout << " __________Round[" << i << "]__________ \n" ;
                    computercounter++ ;
                    cout << "\a" << "You: Rock\nComputer: Paper\n" << "You : " << playercounter << "\nComputer : " << computercounter << "\n";;
                    system("Color 4f");
                    cout << " ____________________________ \n" ;
                }
                else
                {
                    cout << " __________Round[" << i << "]__________ \n" ;
                    cout << "You: Rock\nComputer: Rock\n" << "Draw!\n" << "You : " << playercounter << "\nComputer : " << computercounter << "\n";
                    system("Color 6f");
                    cout << " ____________________________ \n" ;
                }
            }
            else if (player == paper)
            {
                if (computer == rock)
                {
                    cout << " __________Round[" << i << "]__________ \n" ;
                    playercounter++ ;
                    cout << "You: Paper\nComputer: Rock\n" << "You : " << playercounter << "\nComputer : " << computercounter << "\n";
                    system("Color 2f") ;
                    cout << " ____________________________ \n" ;
                }
                else if (computer == sissor)
                {
                    cout << " __________Round[" << i << "]__________ \n" ;
                    computercounter++ ;
                    cout << "\aYou: Paper\nComputer: Scissor\n" << "You : " << playercounter << "\nComputer : " << computercounter << "\n";
                    system("Color 4f") ;
                    cout << " ____________________________ \n" ;
                }
                else
                {
                    cout << " __________Round[" << i << "]__________ \n" ;
                    cout << "You: Paper\nComputer: Scissor\n" << "Draw\n" << "You : " << playercounter << "\nComputer : " << computercounter << "\n";
                    system("Color 6f") ;
                    cout << " ____________________________ \n" ;
                }
            }
            else
            {
                if (computer == paper)
                {
                    cout << " __________Round[" << i << "]__________ \n" ;
                    playercounter++ ;
                    cout << "You: Scissor\nComputer: Paper\n" << "You : " << playercounter << "\nComputer : " << computercounter << "\n";
                    system("Color 2f") ;
                    cout << " ____________________________ \n" ;
                }
                else if (computer == rock)
                {
                    cout << " __________Round[" << i << "]__________ \n" ;
                    computercounter++ ;
                    cout << "\a" << "You: Scissor\nComputer: Rock\n" << "You : " << playercounter << "\nComputer : " << computercounter << "\n";
                    system("Color 4f") ;
                    cout << " ____________________________ \n" ;
                }
                else
                {
                    cout << " __________Round[" << i << "]__________ \n" ;
                    cout << "You: Scissor\nComputer: Sissor\n" << " Draw! " << "You : " << playercounter << "\nComputer : " << computercounter << "\n";
                    system("Color 6f") ;
                    cout << " ____________________________ \n" ;
                }
            }
        }
        cout << " \t\t\t________________________________________\n\n\n ";
        cout << " \t\t\t          *** G a m e O v e r *** \n\n\n " ;
        cout << " \t\t\t________________________________________\n\n " ;
        cout << " \t\t\t______________[Game results]____________\n\n";
        cout << "Game rounds : " << numberofrounds << endl ;
        cout << "You : " << playercounter << endl;
        cout << "Computer : " << computercounter << endl;
        cout << "Final winner : ";
        if (playercounter > computercounter)
            cout << " You!\n" << system("Color 2f");
        else if (computercounter > playercounter)
            cout << "Computer!\n" << system("Color 4f");
        else
            cout << "Draw!\n" << system("Color 6f");
        cout << "do you want to play again? \n Yes: 1 , No : 0 \n";
        cin >> c ;
    }
    while (c == true);
}
int main()
{
    srand((unsigned)time(NULL));
    game();
    StartGame();
    return 0;
}

