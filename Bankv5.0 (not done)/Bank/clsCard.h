#pragma once
#include <iostream>

using namespace std;

class clsCard
{
	protected:

		int _CardNumber = 0;
		short _Cvc = 0;
		string _CardHolderName;
		string _IssueDate;
		string _ExpiryDate;

		long long _RandomNumber(int From, int To)
		{
			//Function to generate a random number
			long long randNum = rand() % (To - From + 1) + From;
			return randNum;
		}

	public:

		virtual int GetCardNumber() = 0;
		virtual void SetCardNumber(int CardNumber) = 0;
		virtual void PrintCardType() = 0;
		virtual short GetCVC() = 0;
		virtual void SetCVC(short number) = 0;

};

