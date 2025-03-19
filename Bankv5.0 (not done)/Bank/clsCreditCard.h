#pragma once
#include <iostream>
#include "clsCard.h"

using namespace std;

class clsCreditCard : public clsCard
{
	long long _RandomNumber(int From, int To)
	{
		//Function to generate a random number
		long long randNum = rand() % (To - From + 1) + From;
		return randNum;
	}

	int _MonthlyLimit = 0;

	public:

		clsCreditCard()
		{
			_CardNumber = _RandomNumber(10000000000000000, 999999999999999);

			_Cvc = _RandomNumber(100, 999);
			

			//cin >> _CardNumber >> _Cvc >> _CardHolderName >> _ExpiryDate >> _MonthlyLimit ;
			return;
		}

		clsCreditCard(int CardNumber , int Cvc , string CardHolderName , string ExpiryDate)
		{
			_CardNumber = CardNumber;
			_Cvc = Cvc;
			_CardHolderName = CardHolderName;
			_ExpiryDate = ExpiryDate;
		}

		int GetCardNumber()
		{
			return _CardNumber;
		}

		void SetCardNumber(int CardNumber)
		{
			_CardNumber = CardNumber;
			return;
		}

		short GetCVC()
		{
			return _Cvc;
		}

		void SetCVC(short number)
		{
			_Cvc = number;
			return;
		}

		string GetCardHolderName()
		{
			return _CardHolderName;
		}

		void SetCardHolderName(string Name)
		{
			_CardHolderName = Name;
			return;
		}

		string GetExpiryDate()
		{
			return _ExpiryDate;
		}

		void SetExpiryDate(string ExpiryDate)
		{
			_ExpiryDate = ExpiryDate;
		}

		void PrintCardType()
		{
			cout << "\nCredit Card";
		}
};

