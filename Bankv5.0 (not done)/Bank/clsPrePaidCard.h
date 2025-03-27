#pragma once
#include <iostream>
#include "clsdate.h"
#include "clsCard.h"

using namespace std;

class clsPrePaidCard : public clsCard
{
	int _CurrentBalance = 0;

	public:

		clsPrePaidCard()
		{
			_CardNumber = _RandomNumber(10000000000000000, 999999999999999);

			_Cvc = _RandomNumber(100, 999);

			clsDate date = clsDate::GetSystemDate();

			_IssueDate = date.DateToString();

			date.Year += 3;

			_ExpiryDate = date.DateToString();
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

