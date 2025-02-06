#pragma once
#include <iostream>

using namespace std;

class clsCreditCard
{
	private:

		int _CardNumber = 0;
		int _Cvc = 0;
		string _CardHolderName;
		string _ExpiryDate;

	public:

		clsCreditCard()
		{
			cin >> _CardNumber >> _Cvc >> _CardHolderName >> _ExpiryDate;
			return;
		}

};

