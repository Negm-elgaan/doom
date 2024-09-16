#include <iostream>
#include <math.h>

using namespace std;
void DivisbilityProblem()
{
    long long num = 0 , *Counter , *Arr , j = 0 , x = 2;
    cin >> num;
    Counter = new long long [num];
    Arr = new long long [num + num];
    for (long long i = 0 ; i < num * 2 ; i++)
    {
        cin >> Arr[i];
    }
    for (long long i = 0 ; i < num * 2; i = i + 2)
    {
        if (Arr[i] >= Arr[i + 1] && Arr[i] % Arr[i + 1] == 0)
        {
            Counter[j] = 0 ;
            j++;
        }
        else if (Arr[i] < Arr[i + 1])
        {
            Counter[j] = Arr[i+1] - Arr[i];
            j++;
        }
        else
        {
            Counter[j] = 0 ;
            /*while(Arr[i + 1] * x < Arr[i])
            {
                x++;
            }
            */

            x = ceil(float(Arr[i]) / float(Arr[i+ 1]));
            Arr[i + 1] *= x;
            Counter[j] = Arr[i+1] - Arr[i];
            j++;
            x = 2 ;
        }
    }
    delete []Arr;
    for (long long i = 0 ; i < num ; i++)
        cout << Counter[i]<< endl;
    delete []Counter;
    return ;
}
int main()
{
    DivisbilityProblem();
    return 0;
}
