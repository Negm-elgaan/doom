#include <iostream>

using namespace std;

class TicTacToe
{
    private:

        int Arr1[3][3] = {1,2,3,4,5,6,7,8,9};
        char Arr2[3][3];
        char Symbol = 'O';
        enum Mode{Computer , TwoPlayers};

    public:

        TicTacToe()
        {
            cin >> Symbol;
        }

};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
