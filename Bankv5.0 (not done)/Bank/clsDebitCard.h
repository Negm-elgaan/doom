#pragma once
#include <iostream>
#include "clsCard.h"

using namespace std;

class clsDebitCard : public clsCard
{
	int _CurrentBalance = 0;

	public:

		clsDebitCard()
		{
			_CardNumber = _RandomNumber(10000000000000000, 999999999999999);

			_Cvc = _RandomNumber(100, 999);
		}

		int GetCardNumber()
		{
			return _CardNumber;
		};

		void SetCardNumber(int CardNumber)
		{
			_CardNumber = CardNumber;
		};

		void PrintCardType()
		{
			cout << "\nDebit Card\n";
		};

		short GetCVC()
		{
			return _Cvc;
		};

		void SetCVC(short number)
		{
			_Cvc = number;
		};

		void SetBalance(int CurrentBalance)
		{
			_CurrentBalance = CurrentBalance;
		}

		int CurrentBalance()
		{
			return _CurrentBalance;
		}
};

