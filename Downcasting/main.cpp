#include <iostream>

using namespace std;
class Person
{
    protected:
        string Name;
        string Number;
    public:
        Person()
        {
            cin >> Name >> Number;
            return;
        }

        Person(string Name , string Number)
        {
            this->Name = Name;
            this->Number = Number;
            return;
        }

        virtual void print()
        {
            cout << Name << endl << Number << endl;
        }
};

class Employee : public Person
{
    private:
        double ID;
    public:
        Employee():Person(/*Name,Number*/)
        {
            cin >> ID;
            return;
        }

        Employee(double ID , string Name , string Number):Person(Name,Number)
        {
            this->ID = ID;
            return;
        }

        void print() override
        {
            Person::print();
            cout << ID << endl;
        }
};
int main()
{
    Employee Em;
    //Em.print();
    //Employee EMM = &Person1;
    Person *P = &Em;
    P->print();
    cout << "Hello world!" << endl;
    return 0;
}
