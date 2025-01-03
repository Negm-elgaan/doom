#include <iostream>

using namespace std;

double _stod(string word)
{
    double num = 0;
    short dot = 0;
    int decimal = 10;

    for (int i = 0; word[i] != '\0'; i++)
    {
        if (dot == 0)  // Before the decimal point
        {
            if (word[i] == '0')
            {
                num = num * 10 + 0;
            }
            else if (word[i] == '1')
            {
                num = num * 10 + 1;
            }
            else if (word[i] == '2')
            {
                num = num * 10 + 2;
            }
            else if (word[i] == '3')
            {
                num = num * 10 + 3;
            }
            else if (word[i] == '4')
            {
                num = num * 10 + 4;
            }
            else if (word[i] == '5')
            {
                num = num * 10 + 5;
            }
            else if (word[i] == '6')
            {
                num = num * 10 + 6;
            }
            else if (word[i] == '7')
            {
                num = num * 10 + 7;
            }
            else if (word[i] == '8')
            {
                num = num * 10 + 8;
            }
            else if (word[i] == '9')
            {
                num = num * 10 + 9;
            }
            else if (word[i] == '.')
            {
                dot = 1;
            }
            else
            {
                cout << "Cannot convert characters to double! Enter another string:\n";
                return 0;
            }
        }
        else if (dot == 1)  // After the decimal point
        {
            if (word[i] == '0')
            {
                num = num + 0.0 / decimal;  // Adding the fractional part
                decimal *= 10;  // Move to the next decimal place
            }
            else if (word[i] == '1')
            {
                num = num + 1.0 / decimal;  // Adding the fractional part
                decimal *= 10;
            }
            else if (word[i] == '2')
            {
                num = num + 2.0 / decimal;  // Adding the fractional part
                decimal *= 10;
            }
            else if (word[i] == '3')
            {
                num = num + 3.0 / decimal;  // Adding the fractional part
                decimal *= 10;
            }
            else if (word[i] == '4')
            {
                num = num + 4.0 / decimal;  // Adding the fractional part
                decimal *= 10;
            }
            else if (word[i] == '5')
            {
                num = num + 5.0 / decimal;  // Adding the fractional part
                decimal *= 10;
            }
            else if (word[i] == '6')
            {
                num = num + 6.0 / decimal;  // Adding the fractional part
                decimal *= 10;
            }

            else if (word[i] == '7')
            {
                num = num + 7.0 / decimal;  // Adding the fractional part
                decimal *= 10;
            }
            else if (word[i] == '8')
            {
                num = num + 8.0 / decimal;  // Adding the fractional part
                decimal *= 10;
            }
            else if (word[i] == '9')
            {
                num = num + 9.0 / decimal;  // Adding the fractional part
                decimal *= 10;
            }
            else
            {
                cout << "Cannot convert characters to double! Enter another string:\n";
                return 0;  // Early exit on invalid character
            }
        }
    }
    return num;
}

int main()
{
    string s = "192.022";
    double d = _stod(s);
    cout << d << endl;
    return 0;
}
