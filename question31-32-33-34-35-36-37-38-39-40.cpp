#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

string readstring();
char readchar();
short CountChar1(string & , char &);
short CountChar2(string & , char &);
string to_lower(string &);
string to_upper(string &);
bool is_upper(char &);
bool is_lower(char &);
char invertcase(char &);
short  CountLetter(string S1, char Letter, bool MatchCase = true)
{
    short Counter = 0;
    for (short i = 0; i < S1.length(); i++)
        {
            if (MatchCase)
                {
                    if (S1[i] == Letter)
                        Counter++;
                }
            else
                {
                    if (tolower(S1[i]) == tolower(Letter))
                        Counter++;
                }
            }
    return Counter;
}
short PrintEachWordInString(string S1)
{
    short counter = 0 ;
    string delim = " "; // delimiter
    cout <<"\nYour string words are: \n\n";
    short pos = 0;
    string sWord; // define a string variable
    // use find() function to get the position of the delimiters
    while ((pos = S1.find(delim)) != std::string::npos)
    {
        counter++;
        sWord =S1.substr(0, pos);// store the word
        if (sWord !="")
        {
            cout << sWord << endl;
        }
        S1.erase(0, pos + delim.length());  // erase() until positon and move to next word.
    }
    if (S1!="")
    {
        cout <<S1<< endl; // it print last word of the string.
        counter++;
    }
    return counter ;
}
char  InvertLetterCase(char );
bool checkvowel(char );
short CountVowels(string );
void printvowels(string );
short printeachWord(string );
vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable
    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord =S1.substr(0, pos); // store the word
        if (sWord !="")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }
    if (S1!="")
    {
        vString.push_back(S1); // it adds last word of the string.
    }
    return vString;
}
void trimleft(string &s)
{
    short i = 0 ;
    while (s[i] == ' ')
        i++;
    if (s[i] != ' ')
        s.erase(0,i);
}
void trimright(string &s)
{
    short i = s.length();
    while (s[i] == ' ')
        i--;
    s.erase(i,s.length());
}
void trim(string &s)
{
    short i = 0 ;
    while (s[i] == ' ')
        i++;
    if (s[i] != ' ')
        s.erase(0,i);
    short j = s.length();
    while (s[j] == ' ')
        j--;
    s.erase(j,s.length());
}
string TrimLeft(string S1)
{
    for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(i, S1.length() - i);
            }
        }
    return"";
}
string TrimRight(string S1)
{
    for (short i = S1.length() - 1; i >= 0; i--)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(0, i + 1);
            }
        }
    return"";
}
string Trim(string S1)
{
    return (TrimLeft(TrimRight(S1)));
}
string Join(vector <string> vString , string delim)
{
    string s1 = "" ;
    for (int i = 0 ; i < vString.size() ; i++)
    {
        if (i == vString.size() - 1)
            s1 += vString[i];
        else
            s1 += vString[i] + delim ;
    }
    return s1;
}
string JoinString(vector<string> vString, string Delim)
{
    string S1="";
    for (string& s : vString)
        {
            S1 = S1 + s +Delim;
        }
    return S1.substr(0,S1.length()-Delim.length());
}
string Join(short n , string arr[] , string delim)
{
    for (short i = 0 ; i < n ; i++)
        cin >> arr[i];
    string s = "";
    for (short i = 0 ; i < n ; i++)
    {
            s +=  arr[i] + delim ;
    }
    return s.substr(0,s.length()-delim.length());
}
int main()
{
    //string f = readstring();
    //trimleft(f);
    //trimright(f);
    //trim(f);
    //cout << f << endl;
    vector<string> vString;
    vString = SplitString(readstring(), " ");
    cout <<"\nTokens = "<< vString.size() << endl;
    for (string& s : vString)
        cout << s << endl;
    string s = Join(vString,":");
    short n = 0 ;
    cout << "enter size of array: " ;
    cin >> n ;
    string arr[n];
    cout << "Vector after join: \n" << s << endl;
    //for (short i = 0 ; i < n ; i++)
        //cout << arr[i] << endl;
    string Ns = Join(n,arr,"***");
    cout << "Array of string after join: \n" << Ns << endl;
    /*cout <<  "\nNumber of vowels is : " << CountVowels(s) << endl ;
    char c = readchar();
    if (checkvowel(c))
        cout << "YES Letter '" << c << "' is vowel\n";
    else
        cout << "NO Letter '" << c << "' isn't vowel\n";
    cout << "\nLetter \'" << c << "\' Count = " << CountLetter(s, c);
    cout << "\nLetter \'" << c << "\' ";
    cout << "Or \'" << InvertLetterCase(c) << "\' ";
    cout << " Count = " << CountLetter(s, c, false);
    cout << "\nLetter \'" << c << "\' Count = " << CountChar1(s, c);
    cout << "\nLetter \'" << c << "\' ";
    cout << "Or \'" << InvertLetterCase(c) << "\' ";
    cout << " Count = " << CountChar2(s, c);*/
    return 0;
}
string readstring()
{
    string s = " " ;
    cout << "Enter string: " ;
    getline(cin,s);
    return s ;
}
char readchar()
{
    char c = ' ';
    cout << "Enter char: \n" ;
    cin >> c ;
    return c ;
}
short CountChar1(string &s , char &c)
{
    short counter = 0 ;
    for (int i = 0 ; s[i] != NULL ; i++)
        if (s[i] == c)
            counter++;
    return counter ;
}
short CountChar2(string &s , char &c)
{
    short counter = 0 ;
    if (is_lower(c))
    {
        for (int i = 0 ; s[i] != NULL ; i++)
            if (s[i] == c || s[i] == c - 32)
                counter++;
    }
    else
    {
        for (int i = 0 ; s[i] != NULL ; i++)
            if (s[i] == c || s[i] == c + 32)
                counter ++;
    }
    return counter ;
}
bool is_lower(char &c)
{
    return (c >= 97 && c <= 122) ;
}
bool is_upper(char &c)
{
    return (c >= 65 && c <= 90) ;
}
char invertcase(char &c)
{
    if (c >= 97 && c <= 122)
        return c -= 32 ;
    else if (c >= 65 && c <= 90)
        return c += 32 ;
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
char  InvertLetterCase(char char1)
{
     return isupper(char1) ? tolower(char1) : toupper(char1);
}
bool checkvowel(char c)
{
    c = tolower(c);
    return (c == 'a' || c == 'i' || c == 'e' || c == 'u' || c == 'o');
}
short CountVowels(string s)
{
    short counter = 0 ;
    for (int i = 0 ; s[i] != NULL ; i++)
        if(checkvowel(s[i]))
            counter++;
    return counter;
}
void printvowels(string s)
{
    cout << "Vowels in string are : " ;
    for (int i = 0 ; s[i] != NULL ; i++)
        if(checkvowel(s[i]))
            cout << s[i] << setw(4) ;
}
short printeachWord(string s)
{
    short counter = 1 ;
    for (int i = 0 ; s[i] != NULL ; i++)
    {
        if (s[i] == 32)
        {
            counter++ ;
            cout << endl ;
        }
        else
            cout << s[i] ;
    }
    cout << endl;
    return counter ;
}

