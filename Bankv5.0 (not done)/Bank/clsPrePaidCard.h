#pragma once
#include <iostream>
#include "clsCard.h"

using namespace std;

class clsPrePaidCard : public clsCard
{
	int _CurrentBalance = 0;

	public:

		clsPrePaidCard()
		{

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

