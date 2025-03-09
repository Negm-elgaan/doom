#pragma once
#include <iostream>

using namespace std;

class clsCard
{
	protected:

		int _CardNumber = 0;
		short _Cvc = 0;
		string _CardHolderName;
		// Add Issue Date;
		string _IssueDate;
		string _ExpiryDate;

	public:

		virtual int GetCardNumber() = 0;
		virtual void SetCardNumber(int CardNumber) = 0;
		virtual void PrintCardType() = 0;
		virtual short GetCVC() = 0;
		virtual void SetCVC(short number) = 0;

};

