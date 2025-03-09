#pragma once
#include <iostream>
#include "clsCard.h"

using namespace std;

class clsCreditCard : public clsCard
{
	public:

		clsCreditCard()
		{
			cin >> _CardNumber >> _Cvc >> _CardHolderName >> _ExpiryDate;
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
};

