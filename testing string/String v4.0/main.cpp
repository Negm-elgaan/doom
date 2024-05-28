#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
//this is string class version 4.0 :-)
//It has some improvements from the older versions but it is still mostly not very efficient in terms of time complexity
using namespace std;
class String
{
	int n = 0 ;
	char* ptr;
	public:
		String()
		{
		    cout << "Enter size (NOTE : Entering a number of characters more than the allocated size will lead to the extra characters outside of boundary of size to be lost!!)\n";
		    cin >> n ;

		}
		String(int num)
		{
		    n = num ;
		}
		void value(char* ptrr , int s)
		{
		    n = s ;
		    ptr = new char [n];
		    for (int i = 0 ; ptrr[i] != '\0' ; i++)
            {
                ptr[i] = ptrr[i];
            }
		}
		void value()
		{
		    ptr = new char[n];
		    cin.ignore();
		    for (int i = 0 ; i < n ; i++)
            {
                cin.get(ptr[i]);
            }
		}
		void append()
		{
		    cin.ignore();
            n++;
            cin.get(ptr[n-1]);
        }
        void extend()
        {
            cout << "how many characters do you want to add?\n";
            int x = 0 , i = n ;
            cin >> x ;
            n += x ;
            cin.ignore();
            for (i ; i < n ; i++)
                cin.get(ptr[i]);
        }
        char* getstr()
        {
            return ptr;
        }
        int getlength()
        {
            return n;
        }
		void print()
		{
		    for (short i = 0 ; i < n ; i++)
                cout << *(ptr + i);
            cout << endl;
		}
		bool IsStringLower()
		{
		    for (int i = 0 ; i < n ; i++)
                if (!IsCharLower(ptr[i]))
                    return false;
            return true ;
		}
		static bool IsCharLower(char c)
		{
            return (c >= 97 && c <= 122);
		}
		static bool IsCharUpper(char c)
		{
            return (c >= 65 && c <= 90) ;
		}
		void to_lower()
        {
            for (int i = 0 ; ptr[i] != NULL ; i++)
            {
                if (ptr[i] >= 65 && ptr[i] <= 90)
                    ptr[i] += 32 ;
            }
        }
        void to_upper()
        {
            for (int i = 0 ; ptr[i] != NULL ; i++)
            {
                if (ptr[i] >= 97 && ptr[i] <= 122)
                    ptr[i] -= 32 ;
            }
        }
        bool isempty()
        {
            for (int i = 0 ; i < n ; i++)
                if (ptr[i] != NULL)
                    return true ;
            return false ;
        }
        void Search(char c)
        {
            for (int i = 0 ; i < n ; i++)
                if (c == ptr[i])
                {
                    cout << "Character exists\n";
                    return;
                }
            cout << "Character doesn't exist\n";
            return ;
        }
        char AT(int index)
        {
            for (int i = 0 ; ptr[i] != NULL ; i++)
                if (i == index)
                    return ptr[i];
            return '\0';
        }
		bool IsStringUpper()
		{
		    for (int i = 0 ; i < n ; i++)
                if (!IsCharUpper(ptr[i]))
                    return false;
            return true ;
		}
		void clearstr()
		{
		    delete [] ptr ;
            ptr = new char[n];
		}
		void Replace(char c , char d)
		{
		    for (int i = 0 ; i < n ; i++)
            {
                if (ptr[i] == c)
                    ptr[i] = d ;
            }
            return ;
		}
		char* DeleteChar(char c)
		{
		    int j = 0 , m = n , x = 0;
		    for (int i = 0 ; i < n ; i++)
            {
                if (ptr[i] == c)
                {
                    ptr[i] = NULL;
                    j = i ;
                    while(j < m)
                    {
                        ptr[j] = ptr[j+1];
                        j++;
                    }
                    m--;
                    x++;
                    i = 0 ;
                }
            }
            n -= x ;
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
		    for (int i = 0 ; i < n/2 ; i++)
            {
                temp = ptr[i];
                ptr[i] = ptr[n - i - 1];
                ptr[n - i - 1] = temp;
            }
		}
		int ToInteger()
		{
		    int x = 0 , f = 0 , y = 0;
		    for (int i = 0 ; i < n ; i++)
            {
                switch(ptr[i])
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
		void Insert(char c , int loc)
		{
		    n++;
		    for (int i = n - 1 ; i >= 0 ; i--)
                {
                    ptr[i] = ptr[i - 1];
                    if (loc == i)
                    {
                        ptr[i] = c ;
                        return ;
                    }
                }
		}
		void Insert(char *ptr3 , int loc)
		{
		    int x = 0 , y = 0;
		    for (int i = 0 ; ptr3[i] != NULL  ; i++)
            {
                x++;
                n++;
            }
            for (int i = n - 1 ; i >= 0 ; i--)
            {
                ptr[i] = ptr[i - x];
                if (loc == i)
                {
                    for(int j = i ; j < (i + x) ; j++)
                    {
                        ptr[j] = ptr3[y];
                        y++;
                    }
                    return ;
                }
            }
		}
		void Strcat(char* ptr1 , char* ptr2)
		{
		    for (int i = 0 ; ptr1[i] != '\0' ; i++)
            {
                n++ ;
                ptr[n - 1] = ptr1[i] ;
            }
            for (int i = 0 ; ptr2[i] != '\0' ; i++)
            {
                n++ ;
                ptr[n - 1] = ptr2[i] ;
            }
		}
    private :
        static bool compare(String s1 , String s2)
        {
            char *ptr1  = s1.getstr();
            char *ptr2 = s2.getstr();
            int strlen1 = s1.getlength();
            int strlen2 = s1.getlength();
            if (strlen1 != strlen2)
            {
                delete []ptr1;
                delete []ptr2;
                return false;
            }
            for (int i = 0 ; i < strlen1 ; i++)
                if (*(ptr1 + i) != *(ptr2 +i))
                {
                    delete []ptr1;
                    delete []ptr2;
                    return false;
                }
            delete []ptr1;
            delete []ptr2;
            return true;
        }
    public :
        void compare1(String s2)
        {
            cout << compare(*this,s2);
        }
        ~String()
        {
            printf("\nobject destroyed\n");
            delete [] ptr;
        }
};
String ToString(int num)
{
    String s1(0);
    int x = 0 , y = 0 , c = 0 , i = 0;
    if (num < 0)
    {
        c++;
        num *= -1;
    }
    while (num != 0)
    {
        x = x * 10 + num % 10 ;
        num /= 10 ;
        y++;
    }
    s1.n = y ;
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
    char* ptr1 = new char [5] ;
    char* ptr2 = new char [5] ;
    for (int i = 0 ; i < 5 ; i++)
        cin >> ptr1[i];
    for (int i = 0 ; i < 5 ; i++)
        cin >> ptr2[i];
    String s1;
    s1.value();
    s1.print();
    s1.Strcat(ptr1,ptr2);
    s1.print();
    cout << s1.AT(3);
    /*s1.value();
    //s1.Insert(ptr,5);
    s1.print();
    s1.clearstr();
    s1.print();
    s1.value();
    s1.print();
    //s1.Insert('f',5);
    n = s1.ToInteger();
    cout <<"after turning to int "<< n << endl;
    String s4(0);
    s4 = ToString(n);
    s4.print();
    s4.append();
    s4.print();
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
    delete []ptr1;
    delete []ptr2;
    return 0;
}
