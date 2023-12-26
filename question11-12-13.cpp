#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cstdio>
using namespace std;
int RandomNumber(int , int );
void FillMatrixWithRandomNumbers(int [3][3], short , short );
void printmatrix(int [3][3] , short , short );
void printmiddlerow(int [3][3] , short , short);
void printmiddlecol(int [3][3] , short , short);
int matrixsum(int [3][3] , short , short);
bool checkmatrixequality(int [3][3] , int [3][3] , short , short );
void printequilty(int [3][3] , int [3][3] , short , short );
bool AreEqualMatrices(int [3][3] , int [3][3] , short , short );
bool CheckidentityMatrix(int [3][3] , short , short);
void printidentity(int [3][3] , short , short);
int main()
{
    srand((unsigned)time(NULL));
    int arr1[3][3],arr2[3][3];
    for (int i = 0 ; i < 3 ; i++)
    {
        for (int j = 0 ; j < 3 ; j++)
            {
                cin >> arr1[i][j];
                cin >> arr2[i][j];
            }
    }

    //FillMatrixWithRandomNumbers(arr1,3,3);
    //FillMatrixWithRandomNumbers(arr2,3,3);
    cout << "Matrix 1: \n";
    printmatrix(arr1,3,3);
    cout << "Matrix 2: \n";
    printmatrix(arr2,3,3);
    //printequilty(arr1,arr2,3,3);
    printidentity(arr1,3,3);
    printidentity(arr2,3,3);
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
void printmiddlerow(int arr[3][3] , short Rows , short Cols)
{
    for (int i = 0 ; i <  Cols ; i++)
        printf("%0*d    ",2,arr[Rows/2][i]);
    cout << endl;
}
void printmiddlecol(int arr[3][3] , short Rows , short Cols)
{
    for (int i = 0 ; i <  Rows ; i++)
        printf("%0*d    ",2,arr[i][Cols/2]);
    cout << endl ;
}
int matrixsum(int arr[3][3] , short Rows , short Cols)
{
    int sum = 0 ;
    for (int i = 0 ; i < Rows ; i++)
        for (int j = 0 ; j < Cols ; j++)
            sum += arr[i][j] ;
    return sum ;
}
bool checkmatrixequality(int arr1[3][3] , int arr2[3][3] , short Cols , short Rows)
{
    for (int i = 0 ; i < Rows ; i++)
        for (int j = 0 ; j < Cols ; j++)
        {
            if (arr1[i][j] != arr2[i][j])
                return false ;
        }
    return true ;
}
void printequilty(int arr1[3][3] , int arr2[3][3] , short Cols , short Rows)
{
    if (checkmatrixequality(arr1,arr2,Cols,Rows))
        cout << "Yes : matrices are equal \n" ;
    else
        cout << "No : matrices are not equal \n" ;
}
bool AreEqualMatrices(int Matrix1[3][3] , int Matrix2[3][3] , short Rows , short Cols)
{
    return (matrixsum(Matrix1, Rows, Cols) == matrixsum(Matrix2, Rows, Cols));
}
bool CheckidentityMatrix(int Matrix1[3][3] , short Rows , short Cols)
{
    for (int i = 0 ; i < Rows ; i++)
        for (int j = 0 ; j < Cols ; j++)
        {
                if (j == i)
                    if (Matrix1[i][j] != 1)
                        return false;
                else if (j != i)
                    if (Matrix1[i][j] != 0)
                        return false ;
        }
    return true;

}
void printidentity(int Matrix1[3][3] , short Rows , short Cols)
{
    if (CheckidentityMatrix(Matrix1,Rows,Cols))
        cout << "YES : Matrix is identity\n";
    else
        cout << "NO : Matrix is not identity\n";
}


