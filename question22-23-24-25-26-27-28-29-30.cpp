#include <iostream>
#include <string>

using namespace std;

enum enWhatToCount { SmallLetters=0, CapitalLetters=1,All=3};
int fibbyrecursion(int  , int , int , int , int );
void PrintFibonacciUsingRecurssion(short , int , int );
void printfirstwordsinstring(string );
string readstring();
void PrintFirstLetterOfEachWord(string );
void checkupper(string &);
void printstring(string );
void checklower(string &);
string  LowerFirstLetterOfEachWord(string );
string  UpperFirstLetterOfEachWord(string );
string to_lower(string &);
string to_upper(string &);
char readchar();
char invertcase(char &);
string invertcaser(string &);
short CountString(string &);
short CountCaptial(string &);
short CountSmall(string &);
short CountChar(string & , char &);
short CountLetters(string S1, enWhatToCount WhatToCount=enWhatToCount::All)
{
    if (WhatToCount == enWhatToCount::All)
        {
            return S1.length();
        }
    short Counter = 0;
    for (short i = 0; i < S1.length(); i++)
        {
            if (WhatToCount==enWhatToCount::CapitalLetters && isupper(S1[i]))
                Counter++;
            if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i]))
                Counter++;
        }
    return Counter;
}
int main()
{
    string ss = readstring();
    char cc = readchar();
    cout << "Letter '" << cc <<"' count = " << CountChar(ss , cc) << endl;
    cout << "\n\nMethod 2\n";
    cout << "\nString Length = " << CountLetters(ss);
    cout << "\nCapital Letters Count= " << CountLetters(ss, enWhatToCount::CapitalLetters);
    cout << "\nSmall Letters Count= " << CountLetters(ss,enWhatToCount::SmallLetters ) << endl;
    cout << CountString(ss) << endl;
    cout << CountSmall(ss) << endl;
    cout << CountCaptial(ss) << endl;
    cout << "string before invert : \n" << ss << endl;
    cout << "String after invert : \n" << invertcaser(ss) << endl;
    char c = readchar();
    cout << "Char after conversion : \n"<< invertcase(c) << endl;
    string s = readstring();
    //checklower(s);
    cout << "string before conversion:\n" << s <<endl;
    cout << "string after lower:\n" << to_lower(s) << endl ;
    cout << "string after conversion:\n" << to_upper(s) << endl;
    printfirstwordsinstring(readstring());
    short n = 0 ;
    cin >> n ;
    cout << fibbyrecursion(0,n,0,1,0);
    return 0;
}
// my solution:
fibbyrecursion(int start , int stop , int prev1 , int prev2 , int fibnum)
{
    if ( start == stop)
        return  fibnum;
    cout << fibnum << endl;
    prev1 = prev2 ;
    prev2 = fibnum ;
    fibnum = prev1 + prev2 ;
    fibbyrecursion(start + 1 , stop , prev1 , prev2 , fibnum ) ;
}
//Abu solution:
void PrintFibonacciUsingRecurssion(short Number, int Prev1, int Prev2)
{
    int FebNumber = 0;
    if (Number > 0)
    {
        FebNumber     =     Prev2 + Prev1;
        Prev2 = Prev1;
        Prev1 = FebNumber;
        cout     <<     FebNumber     <<     "    ";
        PrintFibonacciUsingRecurssion(Number - 1, Prev1, Prev2);
    }
}
void printfirstwordsinstring(string s)
{
    cout << "First letters of this string :\n" ;
    for (int i = 0 ; s[i] != NULL ; i++)
    {
        if (i == 0)
            cout << s[i] << endl ;
        if (s[i - 1] == 32)
            cout << s[i] << endl ;
    }
}
string readstring()
{
    string s = " " ;
    cout << "Enter string: " ;
    getline(cin,s);
    return s ;
}
void PrintFirstLetterOfEachWord(string S1)
{
    bool isFirstLetter = true;
    cout << "\nFirst letters of this string: \n";
    for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && isFirstLetter)
                {
                    cout << S1[i] << endl;
                }
            isFirstLetter = (S1[i] == ' ' ? true : false);
        }
}
void checkupper(string &s)
{
    for (int i = 0 ; s[i] != NULL ; i++)
    {
        if (i == 0 && s[i] <= 122 && s[i] >= 96 )
            s[i]  -= 32 ;
        if (s[i - 1] == 32  &&  s[i] <= 122 && s[i] >= 96)
            s[i] -= 32 ;
    }
}
void checklower(string &s)
{
     for (int i = 0 ; s[i] != NULL ; i++)
    {
        if (i == 0 && s[i] <= 90 && s[i] >= 65 )
            s[i]  += 32 ;
        if (s[i - 1] == 32  &&  s[i] <= 90 && s[i] >= 65)
            s[i] += 32 ;
    }
}
void printstring(string s)
{
    for (int i = 0 ; s[i] != NULL ; i++)
        cout << s[i] ;
    cout << endl;
}
string  LowerFirstLetterOfEachWord(string S1)
{
    bool isFirstLetter = true;
    for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && isFirstLetter)
                {
                    S1[i] = tolower(S1[i]);
                }
            isFirstLetter = (S1[i] == ' ' ? true : false);
        }
    return S1;
}
string  UpperFirstLetterOfEachWord(string S1)
{
    bool isFirstLetter = true;
    for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = toupper(S1[i]);
            }
            isFirstLetter = (S1[i] == ' ' ? true : false);
        }
    return S1;
}
string to_lower(string &s)
{
    for (int i = 0 ; s[i] != NULL ; i++)
    {
        if (s[i] >= 65 && s[i] <= 90)
            s[i] += 32 ;
    }
    return s;
}
string to_upper(string &s)
{
    for (int i = 0 ; s[i] != NULL ; i++)
    {
        if (s[i] >= 97 && s[i] <= 122)
            s[i] -= 32 ;
    }
    return s;
}
char readchar()
{
    char c = ' ';
    cout << "Enter char: \n" ;
    cin >> c ;
    return c ;
}
char invertcase(char &c)
{
    if (c >= 97 && c <= 122)
        return c -= 32 ;
    else if (c >= 65 && c <= 90)
        return c += 32 ;
}
string invertcaser(string &s)
{
    for (int i = 0 ; s[i] != NULL ; i++)
    {
        if (s[i] >= 65 && s[i] <= 90)
            s[i] += 32 ;
        else if (s[i] >= 97 && s[i] <= 122)
            s[i] -= 32 ;
    }
    return s;
}
short CountString(string &s)
{
    short c = 0 ;
    for (int i = 0 ; s[i] != NULL ; i++)
        c++ ;
    return c ;
}
short CountCaptial(string &s)
{
    short c = 0 ;
    for (int i = 0 ; s[i] != NULL ; i++)
        if (s[i] >= 65 && s[i] <= 90)
            c++;
    return c ;
}
short CountSmall(string &s)
{
    short c = 0 ;
    for (int i = 0 ; s[i] != NULL ; i++)
        if (s[i] >= 97 && s[i] <= 122)
            c++;
    return c ;
}
short CountChar(string &s , char &c)
{
    short counter = 0 ;
    for (int i = 0 ; s[i] != NULL ; i++)
        if (s[i] == c)
            counter++;
    return counter ;
}

