/* this is a simple replica of the string class in C++
it doesn't offer alot of capabilties of a normal and has a lot of limitations
and by the time you are reading this it will probably be outdated by a better version :-)*/
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
using namespace std;
class string1
{
	int n = 0;
	char* ptr;
	public:
		string1()
		{
		    cout << "Enter size\n";
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
    private :
        static bool compare(string1 s1 , string1 s2)
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
        void compare1(string1 s2)
        {
            cout << compare(*this,s2);
        }
        ~string1()
        {
            printf("\nobject destroyed\n");
            delete [] ptr;
        }

};
int main()
{
    char c = 'e';
    cout << string1::IsCharLower('a')<<endl;
    string1 s1;
    cout << s1.isempty();
    s1.value();
    s1.Search(c);
    s1.to_upper();
    cout << s1.IsStringUpper() << endl;
    s1.to_lower();
    cout << s1.IsStringLower()<<endl;
    s1.print();
    s1.append();
    s1.extend();
    s1.print();
    string1 s2;
    s2.value();
    s1.compare1(s2);
    return 0;
}
