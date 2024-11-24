#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsdate.h"
#include "clsLoanClient.h"
#include "clsBankClient.h"

using namespace std;

class clsTakeLoanScreen : public clsScreen
{
	private:
		double loan = 0;
		string AccountNumber = "";

		clsLoanClient _ReadLoanClientInfo(clsLoanClient& LoanClient)
		{
			LoanClient.AccountNumber = clsInputValidate::ReadString();
			/**cout << "\nEnter First Name:";
			string FirstName = clsInputValidate::ReadString();
			cout << "\nEnter Last Name:";
			string LastName = clsInputValidate::ReadString();
			cout << "\nEnter Loan Amount:";
			double Loan = clsInputValidate::ReadDblNumber();
			cout << "\nEnter Loan End Date:";
			string LoanEndDate = clsInputValidate::ReadString();
			while (!clsInputValidate::IsValideDate(clsDate(LoanEndDate)) || clsDate::CompareDates(clsDate(LoanEndDate),clsDate::GetSystemDate()) == clsDate::enDateCompare::Equal)
			{
				cout << "\nInvalid Date\n";
				cout << "\nEnter Loan End Date:";
				LoanEndDate = clsInputValidate::ReadString();
			}*/
			return clsLoanClient::GetAddNewClientObject(AccountNumber);
		}

	public:
		
		static void ShowTakeLoanScreen()
		{
			_DrawScreenHeader("\t  Add New Loan Client Screen");
			//_DrawDateScreen();
			//_DrawUserScreen();

			string AccountNumber = "";
			clsLoanClient LClient();
			cout << "\nPlease Enter UserName: ";
			AccountNumber = clsInputValidate::ReadString();
			/*if (clsBankClient::IsClientExist(AccountNumber))
			{
				clsBankClient BClient = clsBankClient::Find(AccountNumber);
				LClient = clsLoanClient::_ConvertLoanClientObjectToLine(BClient);
			}*/

		}

            
};
/*double _Loan;
double _LoanWithInterest;
string _LoanBeginDate;
string _LoanEndDate;
double _InterestRate = 1.14;
clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

			_ReadUserInfo(NewUser, Register);

			clsUser::enSaveResults SaveResult;

			SaveResult = NewUser.Save();

			switch (SaveResult)
			{
			case  clsUser::enSaveResults::svSucceeded:
			{
				cout << "\nUser Addeded Successfully :-)\n";
				_PrintUser(NewUser);
				break;
			}
			case clsUser::enSaveResults::svFaildEmptyObject:
			{
				cout << "\nError User was not saved because it's Empty";
				break;

			}
			case clsUser::enSaveResults::svFaildUserExists:
			{
				cout << "\nError User was not saved because UserName is used!\n";
				break;

			}
			}
		}
		}
		*/