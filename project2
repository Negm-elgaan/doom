#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;
enum enOperationtype {add = 1 , subtract = 2 , division = 3 , multiply = 4 , mix = 5};
enum level {easy = 1 , med = 2 , hard = 3 , mix1 = 4};
enum enAnswer {Correct = 1 , Notcorrect = 2};
struct stmathround
{
    enOperationtype type ;
    level enlevel ;
    int optype = 0 ;
    int quizlvl = 0;
    int playeranswer = 0 ;
    int rightanswer = 0 ;
    int numberofrounds = 0 ;
    int correctanswer = 0 ;
    int wronganswer = 0 ;
};
int RandomNumber(int From, int To)
{
    //Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}
int readpositivenum(string message)
{
    int num = 0 ;
    do
    {
        cout << message << endl ;
        cin >> num ;
    }
    while (num < 0);
    return num;
}
level checklevel(int number)
{
    switch (number)
    {
        case 1:
            return level :: easy;
        case 2:
            return level :: med;
        case 3:
            return level :: hard;
        case 4:
            return level :: mix1;
    }
}
int leveltype(level enlevel,int &x , int &y)
{
    if (enlevel == level :: mix1)
    {
        int z = RandomNumber(1,3) ;
        enlevel = checklevel(z) ;
    }
    switch (enlevel)
    {
        case level :: easy :
            x = RandomNumber(1,10);
            y = RandomNumber(1,10);
            break;
        case level :: med :
            x = RandomNumber(1,100);
            y = RandomNumber(1,10);
            break;
        case level :: hard :
            x = RandomNumber(1,100);
            y = RandomNumber(1,100);
            break;
    }
}
enOperationtype checknumber(int number)
{
        switch (number)
        {
            case 1 :
                return enOperationtype :: add ;
            case 2 :
                return enOperationtype :: subtract ;
            case 3 :
                return enOperationtype :: division ;
            case 4 :
                return enOperationtype :: multiply ;
            case 5 :
                return enOperationtype :: mix ;
        }
}
int easylevel(int &x,int &y,enOperationtype type)
{
    if (type == enOperationtype :: mix)
    {
        int z = RandomNumber(1,4);
        type = checknumber(z);
    }
    switch(type)
    {
        case enOperationtype :: add :
            cout << x << endl << y << "  +\n\n" << "_______\n";
            return x + y ;
        case enOperationtype :: subtract :
            cout << x << endl << y << "  -\n\n" << "_______\n";
            return x - y ;
        case enOperationtype :: division :
            cout << x << endl << y << "  /\n\n" << "_______\n";
            return x / y ;
        case enOperationtype :: multiply :
            cout << x << endl << y << "  *\n\n" << "_______\n";
            return x * y ;
    }
}
enAnswer checkanswer(stmathround s1)
{
    if (s1.rightanswer == s1.playeranswer)
        return enAnswer :: Correct ;
    return enAnswer :: Notcorrect ;
}
void mathgame()
{
    bool c = NULL ;
    do
    {
        system("cls") ;
        system("color 0f") ;
        stmathround s1;
        s1.numberofrounds = readpositivenum("How many rounds do you want to play");
        cout << "select difficulty [1] easy , [2] medium , [3] hard , [4] mix : " ;
        cin >> s1.quizlvl ;
        cout << "\n select type of op [1] add , [2] subtract , [3] division , [4] multiply , [5] mix : " ;
        cin >> s1.optype ;
        s1.enlevel = checklevel(s1.quizlvl);
        s1.type = checknumber(s1.optype);
        for (int i = 1 ; i <= s1.numberofrounds ; i++)
        {
            cout << "Question [" << i << "/" << s1.numberofrounds << "]\n\n" ;
            int x = 0 , y = 0 ;
            leveltype(s1.enlevel,x,y);
            s1.rightanswer = easylevel(x,y,s1.type);
            cin >> s1.playeranswer ;
            if(checkanswer(s1) == enAnswer :: Correct )
            {
                cout << " your answer is correct :-) \n";
                system ("color 2f");
                s1.correctanswer++ ;
            }
            else
            {
                cout << " your answer is not correct :-(\n";
                cout << " the correct answer is : " << s1.rightanswer << endl ;
                system ("color 4f");
                s1.wronganswer++ ;
            }
        }
        if (s1.correctanswer > s1.wronganswer)
        {
            cout << "Final result is pass :-) \n\n";
            system("color 2f");
        }
        else
        {
            cout << "Final result is fail :-( \n\n";
            system("color 4f");
        }
        cout << "_____________________________\n\n";
        cout << "Number of questions: " << s1.numberofrounds << endl;
        cout << "Questions level : " << s1.enlevel << endl;
        cout << "optype : " << s1.type << endl;
        cout << "_____________________________\n\n";
        cout << "do you want to play again ? [1] yes , [0] no \n" ;
        cin >> c ;
    }
    while (c == true);
}
int main()
{
    srand((unsigned)time(NULL));
    mathgame() ;
    return 0;
}

