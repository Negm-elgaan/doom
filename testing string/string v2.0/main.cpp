#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
//this is string class version 2.0 :-)
//It has some improvements from the previous version but still it's mostly not very efficient in terms of time complexity
using namespace std;
class String
{
	int n = 0;
	char* ptr;
	public:
		String()
		{
		    cout << "Enter size (NOTE : Entering a number of characters more than the allocated size will lead to the extra characters outside of boundary of size to be lost!!)\n";
		    cin >> n ;

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
		bool IsStringUpper()
		{
		    for (int i = 0 ; i < n ; i++)
                if (!IsCharUpper(ptr[i]))
                    return false;
            return true ;
		}
		void clearstr()
		{
		    for (int i = 0 ; i < n ; i++)
                ptr[n] = NULL;
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
int main()
{
    String s1;
    s1.value();
    s1.print();
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
    s1.compare1(s2);
    return 0;
}
