// Stringv6.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <thread>
//this is string class version 5.0 :-)
//most of logical problems have been solved but not all of them unforunatly :-( but some functions are now faster and more effiecnt and ISA the remaining problems will be solved Trust Allah :-)
using namespace std;
class String
{
    int n = 0;
    int WordsCount = 1;
    int CapitalCount = 0;
    int SmallCount = 0;
    char* ptr;
public:
    String()
    {
        cout << "Enter size (NOTE : Entering a number of characters more than the allocated size will lead to the extra characters outside of boundary of size to be lost!!)\n";
        cin >> n;
        ptr = new char[n];
        //ptr[n] = '\0';
    }
    String(int num)
    {
        n = num;
        ptr = new char[n];
        //ptr[n] = '\0';
    }
    void value(char* ptrr, int s)
    {
        if (s > n)
        {
            char* temp = new char[s];
            for (int i = 0; i < s; i++)
            {
                temp[i] = ptrr[i];
            }
            delete[]ptr;
            n = s;
            ptr = temp;
        }
        //ptr[n] = '\0';
        return;
    }
    void value(char* ptrr)
    {
        for (int i = 0; ptrr[i] != NULL; i++)
        {
            n++;
        }
        for (int i = 0; ptrr[i] != NULL; i++)
        {
            ptr[i] = ptrr[i];
        }
        return;
    }
    void value()
    {
        cin.ignore();
        for (int i = 0; i < n; i++)
        {
            cin.get(ptr[i]);
        }
        return;
    }
    void append()
    {
        n++;
        char* temp = new char[n];
        for (int i = 0; ptr[i] != NULL; i++)
            temp[i] = ptr[i];
        delete[] ptr;
        ptr = temp;
        cin.ignore();
        cin.get(ptr[n - 1]);
        return;
    }
    void extend()
    {
        cout << "how many characters do you want to add?\n";
        int x = 0, i = n, j = 0;
        cin >> x;
        n += x;
        char* temp = new char[n];
        for (int j = 0; ptr[j] != NULL; j++)
            temp[j] = ptr[j];
        if (ptr != NULL) {
            while (ptr[j] != NULL) {
                temp[j] = ptr[j];
                j++;
            }
        }
        delete[] ptr;
        ptr = temp;
        cin.ignore();
        for (int j = n - x; j < n; j++)
            cin.get(ptr[j]);
        return;
    }
    int getlength()
    {
        return n;
    }
    void print()
    {
        for (short i = 0; i < n; i++)
            cout << *(ptr + i);
        cout << endl;
    }
    bool IsStringLower()
    {
        for (int i = 0; i < n; i++)
            if (!IsCharLower(ptr[i]))
                return false;
        return true;
    }
    static bool IsCharLower(char c)
    {
        return (c >= 97 && c <= 122);
    }
    static bool IsCharUpper(char c)
    {
        return (c >= 65 && c <= 90);
    }
   
    void to_lower()
    {
        for (int i = 0; i < n; i++)
        {
            if (ptr[i] >= 65 && ptr[i] <= 90)
                ptr[i] += 32;
        }
    }
    void to_upper()
    {
        for (int i = 0; i < n; i++)
        {
            if (ptr[i] >= 97 && ptr[i] <= 122)
                ptr[i] -= 32;
        }
    }
    bool isempty()
    {
        for (int i = 0; i < n; i++)
            if (ptr[i] != NULL)
                return true;
        return false;
    }
    void Search(char c)
    {
        for (int i = 0; i < n; i++)
            if (c == ptr[i])
            {
                cout << "Character exists\n";
                return;
            }
        cout << "Character doesn't exist\n";
        return;
    }
    void ThreeCharSearch(char a, char b, char c)
    {
        thread T1(&String::Search,this,a);
        thread T2(&String::Search,this, b);
        thread T3(&String::Search,this, c);
        T1.join();
        T2.join();
        T3.join();
    }
    char AT(int index)
    {
        for (int i = 0; i < n; i++)
            if (i == index)
                return ptr[i];
        return '\0';
    }
    bool IsStringUpper()
    {
        for (int i = 0; i < n; i++)
            if (!IsCharUpper(ptr[i]))
                return false;
        return true;
    }
    void clearstr()
    {
        delete[] ptr;
        ptr = new char[n];
    }
    void Replace(char c, char d)
    {
        for (int i = 0; i < n; i++)
        {
            if (ptr[i] == c)
                ptr[i] = d;
        }
        return;
    }
    char* DeleteChar(char c)
    {
        int x = 0, j = 0;
        char* temp;
        for (int i = 0; i < n; i++)
            if (ptr[i] == c)
                x++;
        n -= x;
        temp = new char[n];
        for (int i = 0; i < n + x; i++)
        {
            if (ptr[i] != c && j < n)
            {
                temp[j] = ptr[i];
                j++;
            }
        }
        delete[]ptr;
        ptr = temp;
        return ptr;
    }
    void trim()
    {
        ptr = DeleteChar(32);
        ptr = DeleteChar(9);
        ptr = DeleteChar(10);
        ptr = DeleteChar(13);
        ptr = DeleteChar(12);
        ptr = DeleteChar(11);
    }
    void StringReverse()
    {
        char temp = NULL;
        for (int i = 0; i < n / 2; i++)
        {
            temp = ptr[i];
            ptr[i] = ptr[n - i - 1];
            ptr[n - i - 1] = temp;
        }
    }
    int ToInteger()
    {
        int x = 0, f = 0, y = 0;
        for (int i = 0; i < n; i++)
        {
            switch (ptr[i])
            {
            case '-':
                y = 1;
                break;
            case '0':
                f = 0;
                break;
            case '1':
                f = 1;
                break;
            case '2':
                f = 2;
                break;
            case '3':
                f = 3;
                break;
            case '4':
                f = 4;
                break;
            case '5':
                f = 5;
                break;
            case '6':
                f = 6;
                break;
            case '7':
                f = 7;
                break;
            case '8':
                f = 8;
                break;
            case '9':
                f = 9;
                break;
            default:
                throw runtime_error("Cannot convert char to int!");
            }
            x = x * 10 + f;
        }
        if (y > 0)
            x *= -1;
        return x;
    }
    friend String ToString(int num);
    void Insert(char c, int loc)
    {
        n++;
        if (loc > n || loc < 0)
            return;
        char* temp = new char[n];
        for (int i = 0; i < n - 1; i++)
            temp[i] = ptr[i];
        delete[] ptr;
        ptr = temp;
        for (int i = n - 1; i >= 0; i--)
        {
            ptr[i] = ptr[i - 1];
            if (loc == i)
            {
                ptr[i] = c;
                return;
            }
        }
    }
    void Insert(char* ptr3, int loc, int ss)
    {
        int x = 0, y = 0, z = n;
        for (int i = 0; i < ss; i++)
        {
            x++;
            n++;
        }
        if (loc > n || loc < 0)
            return;
        char* temp = new char[n];
        for (int i = 0; i < z; i++)
            temp[i] = ptr[i];
        delete[] ptr;
        ptr = temp;
        for (int i = n - 1; i >= 0; i--)
        {
            ptr[i] = ptr[i - x];
            if (loc == i)
            {
                for (int j = i; j < (i + x); j++)
                {
                    ptr[j] = ptr3[y];
                    y++;
                }
                return;
            }
        }
    }
    int CountWords(char delimeter)
    {
        int Counter = 1;
        for (int i = 0; i < n; i++)
        {
            if (ptr[i] == delimeter)
            {
                WordsCount++;
                Counter++;
            }
        }
        return Counter;
    }
    int CountCapital()
    {
        int c = 0;
        for (int i = 0; i < n; i++)
            if (ptr[i] >= 65 && ptr[i] <= 90)
            {
                CapitalCount++;
                c++;
            }
        return c;
    }
    int CountSmall()
    {
        int c = 0;
        for (int i = 0; i < n; i++)
            if (ptr[i] >= 97 && ptr[i] <= 122)
            {
                c++;
                SmallCount++;
            }
        return c;
    }
    void CountAll(char delimeter = ' ')
    {
        thread T1(&String::CountWords, this, delimeter);
        thread T2(&String::CountCapital, this);
        thread T3(&String::CountSmall, this);
        T1.join();
        T2.join();
        T3.join();
        cout << "Words Count: " << WordsCount << endl;
        cout << "Captial Count:" << CapitalCount << endl;
        cout << "Small Count: " << SmallCount << endl;
       
        return;
    }
    void Strcat(char* ptr1, char* ptr2, int size1, int size2)
    {
        int x = 0, y = 0, z = n;
        for (int i = 0; i < size1; i++)
        {
            x++;
            n++;
        }
        for (int i = 0; i < size2; i++)
        {
            y++;
            n++;
        }
        char* temp = new char[n];
        for (int i = 0; i < z; i++)
            temp[i] = ptr[i];
        delete[] ptr;
        ptr = temp;
        if (n == size1 + size2)
        {
            for (int i = 0; i < size1; i++)
            {
                ptr[i] = ptr1[i];
            }
            for (int i = 0; i < size2; i++)
            {
                ptr[x + i] = ptr2[i];
            }
            return;
        }
        cout << n << endl;
        for (int i = 0; i < size1; i++)
        {
            ptr[n - x - y + i] = ptr1[i];
        }
        for (int i = 0; i < size2; i++)
        {
            ptr[n - y + i] = ptr2[i];
        }
        return;
    }
    char* getstr()
    {
        return ptr;
    }
    char* SubStr(int index, int Size)
    {
        int j = 0;
        char* temp = new char[Size];
        for (int i = 0; i < n; i++)
        {
            if (i >= index && j < Size)
            {
                temp[j] = ptr[i];
                cout << temp[j] << endl;
                j++;
            }
            if (j == Size)
                break;
        }
        temp[Size] = '\0';
        return temp;
    }
private:
    static bool compare(String s1, String s2)
    {
        char* ptr1 = s1.getstr();
        char* ptr2 = s2.getstr();
        int strlen1 = s1.getlength();
        int strlen2 = s2.getlength();
        if (strlen1 != strlen2)
        {
            delete[]ptr1;
            delete[]ptr2;
            return false;
        }
        for (int i = 0; i < strlen1; i++)
            if (*(ptr1 + i) != *(ptr2 + i))
            {
                delete[]ptr1;
                delete[]ptr2;
                return false;
            }
        delete[]ptr1;
        delete[]ptr2;
        return true;
    }
public:
    void compare1(String s2)
    {
        cout << compare(*this, s2);
    }
    ~String()
    {
        printf("\nobject destroyed\n");
        delete[] ptr;
    }
};
String ToString(int num)
{
    String s1(0);
    int x = 0, y = 0, c = 0, i = 0;
    if (num < 0)
    {
        c++;
        num *= -1;
    }
    while (num != 0)
    {
        x = x * 10 + num % 10;
        num /= 10;
        y++;
    }
    s1.n = y;
    if (c > 0)
    {
        s1.ptr[0] = '-';
        i++;
        s1.n++;
    }
    while (x != 0)
    {
        switch (x % 10)
        {
        case 0:
            s1.ptr[i] = '0';
            break;
        case 1:
            s1.ptr[i] = '1';
            break;
        case 2:
            s1.ptr[i] = '2';
            break;
        case 3:
            s1.ptr[i] = '3';
            break;
        case 4:
            s1.ptr[i] = '4';
            break;
        case 5:
            s1.ptr[i] = '5';
            break;
        case 6:
            s1.ptr[i] = '6';
            break;
        case 7:
            s1.ptr[i] = '7';
            break;
        case 8:
            s1.ptr[i] = '8';
            break;
        case 9:
            s1.ptr[i] = '9';
            break;
        }
        i++;
        x /= 10;
    }
    return s1;
}
int main()
{
    /*char* ptr1 = new char[5];
    char* ptr2 = new char[5];
    for (int i = 0; i < 5; i++)
        cin >> ptr1[i];
    for (int i = 0; i < 5; i++)
        cin >> ptr2[i];*/
    String s1;
    s1.value();
    s1.ThreeCharSearch('O', 'M', 'A');
    s1.CountAll();
    //cout << s1.CountWords(' ') <<endl;
    s1.to_lower();
    s1.print();
    s1.to_upper();
    s1.print();
    //s1.Insert(ptr1, 3, 5);
    //s1.Strcat(ptr1, ptr2, 5, 5);
    /*String s2;
    s2.value();
    cout << compare(s1,s2);*/
    s1.print();
    //String s2;
    //s2.value(s1.SubStr(3, 4));
    //s2.print();
    cout << s1.AT(3) << endl;
    s1.Insert('3', 6);
    s1.append();
    s1.print();
    s1.extend();
    s1.print();
    s1.DeleteChar('3');
    s1.print();
    s1.clearstr();
    cout << s1.isempty() << endl;
    s1.value();
    cout << s1.getlength() << endl;
    s1.StringReverse();
    s1.print();
    s1.Replace('c', 'd');
    s1.print();
    s1.trim();
    s1.value();
    s1.print();
    s1.Insert('f', 5);
    s1.print();
    /*n = s1.ToInteger();
    cout <<"after turning to int "<< n << endl;
    String s4(0);
    s4 = ToString(n);
    s4.print();
    s4.append();
    s4.print();*/
    /*s1.print();
    s1.StringReverse();
    s1.print();
    s1.trim();
    s1.print();
    s1.DeleteChar('d');
    s1.print();
    s1.Replace('C','D');
    s1.print();
    s1.print();
    char c = 'e';
    cout << String::IsCharLower('a')<<endl;
    cout << s1.isempty();
    s1.Search(c);
    s1.to_upper();
    cout << s1.IsStringUpper() << endl;
    s1.to_lower();
    cout << s1.IsStringLower()<<endl;
    s1.print();
    s1.append();
    s1.extend();
    s1.print();
    String s2;
    s2.value();
    s1.compare1(s2);*/
    //delete []ptr;
   // delete[]ptr1;
   // delete[]ptr2;
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
