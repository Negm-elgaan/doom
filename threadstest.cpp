// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
#include <thread>
using namespace std;

int int_index(int *arr, int s, int (*cmp)(int))
{
    int i;
    for(i = 0 ; i < s ; i++)
    {
        if (cmp(arr[i]) != 0)
            return i;
    }
    return -1;
}
int is_98(int elem)
{
    return (98 == elem);
}
int is_strictly_positive(int elem)
{
    return (elem > 0);
}
int abs_is_98(int elem)
{
    return (elem == 98 || -elem == 98);
}

int main()
{
    int x,i;
    cin>>x;
    int arr[x];
    for (i = 0 ; i < x ; i++)
    {
        cin>>arr[i];
    }
    std::thread tt2(is_98,1);
    std::thread tt1(is_98,98);
    
    int index;
    index = int_index(arr, i, is_98);
    cout<<index<<endl;
    index = int_index(arr, i, abs_is_98);
    cout<<index<<endl;
    index = int_index(arr, i, is_strictly_positive);
    cout<<index<<endl;
    tt2.join();
    tt1.join();
    return 0;
}