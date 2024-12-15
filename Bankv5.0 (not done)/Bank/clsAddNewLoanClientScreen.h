#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsdate.h"
#include "clsLoanClient.h"
#include "clsBankClient.h"

using namespace std;

class clsAddNewLoanClientScreen : public clsScreen
{
	private:

		static void _ReadLoanClientInfo(clsLoanClient& Client , bool BankClient = false)
		{
			
			if (!BankClient)
			{
				string FirstName, LastName;

				cout << "\nEnter FirstName: ";
				FirstName = clsInputValidate::ReadString();

				cout << "\nEnter LastName: ";
				LastName = clsInputValidate::ReadString();

				Client.FullName = FirstName + ' ' + LastName;

				cout << "\nEnter Phone: ";
				Client.Phone = clsInputValidate::ReadString();
			}
			
			cout << "\nEnter Loan: ";
			Client.Loan += clsInputValidate::ReadDblNumber();

			cout << "\nEnter Due Date: ";
			Client.EndDate = clsInputValidate::ReadString();

			cout << "\nEnter Interest Rate: ";
			Client.InterestRate = clsInputValidate::ReadFloatNumber();
			while (true)
			{
				try
				{
					if (Client.InterestRate <= 1 || Client.InterestRate > 1.15)
						throw Client.InterestRate;
					break;
				}
				catch (double InterestRate)
				{
					cout << "\nInterest Rate Cannot be more than 15% or 0!\a\n";
				}
				Client.InterestRate = clsInputValidate::ReadFloatNumber();
			}
		}

		static void _PrintClient(clsLoanClient LoanClient)
		{

			cout << setw(8) << left << "" << "| " << setw(30) << left << LoanClient.AccountNumber;
			cout << "| " << setw(12) << left << LoanClient.FullName;
			cout << "| " << setw(40) << left << LoanClient.Loan;
			cout << "| " << setw(40) << left << LoanClient.GetCurrentLoan();
			cout << "| " << setw(20) << left << LoanClient.LoanBeginDate();
			cout << "| " << setw(20) << left << LoanClient.LoanEndDate();
		}

	public:
		
		static void ShowTakeLoanScreen()
		{
			_DrawScreenHeader("\t  Add New Loan Client Screen");
			//_DrawDateScreen();
			//_DrawUserScreen();

			string AccountNumber = "";
			cout << "\nPlease Enter UserName: ";
			AccountNumber = clsInputValidate::ReadString();
			while (clsLoanClient::IsClientExist(AccountNumber))
			{
				cout << "\nAccount Number Is Already Used, Choose another one: ";
				AccountNumber = clsInputValidate::ReadString();
			}

			clsLoanClient LClient = clsLoanClient::GetAddNewClientObject(AccountNumber);

			if (clsBankClient::IsClientExist(AccountNumber))
			{
				clsBankClient BClient = clsBankClient::Find(AccountNumber);
				LClient = clsLoanClient::BankClientToLoanClient(BClient);
				_ReadLoanClientInfo(LClient,true);
			}

			else
			{
				_ReadLoanClientInfo(LClient);
			}

			clsLoanClient::enSaveResults SaveResult = LClient.Save();

			switch (SaveResult)
			{
			case  clsLoanClient::enSaveResults::svSucceeded:
			{
				cout << "\nAccount Addeded Successfully :-)\n";
				_PrintClient(LClient);
				break;
			}
			case clsLoanClient::enSaveResults::svFaildEmptyObject:
			{
				cout << "\nError account was not saved because it's Empty";
				break;

			}
			case clsLoanClient::enSaveResults::svFaildAccountNumberExists:
			{
				cout << "\nError account was not saved because account number is used!\n";
				break;

			}
			}
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