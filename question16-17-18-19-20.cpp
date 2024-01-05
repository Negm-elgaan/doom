#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cstdio>
#include<iomanip>
#include <math.h>
#include <limits.h>
using namespace std;
int RandomNumber(int , int );
void FillMatrixWithRandomNumbers(int [3][3], short , short );
void printmatrix(int [3][3] , short , short );
bool CheckSparcity(int [3][3] , short , short );
bool Checknum(int [3][3] , int , short , short);
bool IsNumberInMatrix(int Matrix1[3][3], int Number, short Rows, short Cols)
{
    short NumberCount = 0;
    for (short i = 0; i < Rows; i++)
        {
        for (short j = 0; j < Cols; j++)
        {
            if (Matrix1[i][j] == Number)
            {
                 return true;
            };
        }
        }
        return false;
}
void PrintIntersectedNumbers(int Matrix1[3][3], int Matrix2[3][3], short Rows, short Cols)
{
    int Number;
    for (short i = 0; i < Rows; i++)
    {
        for (short j = 0; j < Cols; j++)
        {
            Number     =     Matrix1[i][j];
            if (IsNumberInMatrix(Matrix2, Number, Rows, Cols))
            {
                cout     <<     setw(3)     <<     Number     <<     "     ";    }
        }
    }
}
short CountNumberInMatrix(int Matrix1[3][3], int Number, short Rows, short Cols)
{
    short NumberCount = 0;
    for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols; j++)
                {
                    if (Matrix1[i][j] == Number)
                        {
                            NumberCount++;
                        };
                }
        }
    return NumberCount;
}
bool IsSparseMatrix(int Matrix1[3][3], short Rows, short Cols)
{
    short MatrixSize = Rows * Cols;
    return (CountNumberInMatrix(Matrix1, 0, 3, 3) >= ceil((float) MatrixSize / 2));
}
int Max(int arr[3][3] , short Rows , short Cols)
{
    int Max = INT_MIN ;
    for (int i = 0 ; i < Rows ; i++)
        for (int j = 0 ; j < Cols ; j++)
            if (arr[i][j] > Max)
                Max = arr[i][j];
    return Max ;
}
int Min(int arr[3][3] , short Rows , short Cols)
{
    int Min = INT_MAX ;
    for (int i = 0 ; i < Rows ; i++)
        for (int j = 0 ; j < Cols ; j++)
             if (arr[i][j] < Min)
                Min = arr[i][j];
    return Min;
}
void MaxandMin(int arr[3][3] , short Rows , short Cols)
{
    int Max = INT_MIN ;
    int Min = INT_MAX ;
    for (int i = 0 ; i < Rows ; i++)
        for (int j = 0 ; j < Cols ; j++)
        {
            if (arr[i][j] > Max)
                Max = arr[i][j];
            if (arr[i][j] < Min)
                Min = arr[i][j];
        }
        cout << "Max element is : " << Max << endl << "Min element is : " << Min << endl ;
}
bool CheckPalindrome1(int matrix[3][3] , short Rows , short Cols)
{
    // My solution is same as Abu-Hadhoud :) 
    for (int i = 0 ; i < Rows ; i++)
        for (int j = 0 ; j < Cols / 2 ; j++)
                if (matrix[i][j] != matrix[i][Cols - 1 - j])
                    return false ;
    return true ;
}
int main()
{
    srand((unsigned)time(NULL));
    int arr1[3][3],arr2[3][3],n = 0;
    for (int i = 0 ; i < 3 ; i++)
    {
        for (int j = 0 ; j < 3 ; j++)
            {
                cin >> arr1[i][j];
                //cin >> arr2[i][j];
            }
    }
    cout << "Matrix 1: \n";
    printmatrix(arr1,3,3);
    if (CheckPalindrome1(arr1,3,3))
        cout << "Yes matrix is palindrome\n";
    else
        cout << "No matrix is not palindrome\n";
    cout << "Min element is : " << Min(arr1,3,3) << endl << "Max element is : " << Max(arr1,3,3) << endl;
    MaxandMin(arr1,3,3);
    if (CheckSparcity(arr1,3,3))
        cout << "Yes, the matrix is sparse\n";
    else
        cout << "No, the matrix is not sparse\n";
    cin >> n ;
    if (Checknum(arr1,n,3,3))
        cout << "Yes it is there\n";
    else
        cout << "No it is not there \n";
    return 0;
}
int RandomNumber(int From, int To)
{
    //Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}
void FillMatrixWithRandomNumbers(int arr[3][3], short Rows, short Cols)
{
    for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols; j++)
                {
                    arr[i][j] = RandomNumber(1, 10);
                }
        }
}
void printmatrix(int arr[3][3] , short Rows , short Cols)
{
    for (int i = 0 ; i < Rows ; i++)
    {
        for (int j = 0 ; j < Cols ; j++)
            printf("%0*d    ",2,arr[i][j] );
        cout << endl ;
    }
}
bool CheckSparcity(int arr[3][3] , short Rows , short Cols)
{
    short zeros = 0,nonzeroes = 0;
    for (int i = 0 ; i < Rows ; i++)
        for (int j = 0 ; j < Cols ; j++)
            {
                if (arr[i][j] == 0)
                    zeros++;
                else
                    nonzeroes++;
            }
    return (zeros > nonzeroes);
}
bool Checknum(int arr[3][3] , int num , short Rows , short Cols)
{
    for (int i = 0 ; i < Rows ; i++)
        for (int j = 0 ; j < Cols ; j++)
            if (arr[i][j] == num)
                return true ;
    return false;
}

