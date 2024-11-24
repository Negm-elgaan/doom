#pragma once
#include <iostream>
#include "clsLoanClient.h"
#include "clsScreen.h"

using namespace std;

class clsFindLoanClientScreen : public clsScreen
{
    private:
        static void _PrintLoanClientLine(clsLoanClient LoanClient)
        {

            cout << setw(8) << left << "" << "| " << setw(30) << left << LoanClient.AccountNumber;
            cout << "| " << setw(12) << left << LoanClient.FullName;
            cout << "| " << setw(40) << left << LoanClient.Loan;
            cout << "| " << setw(40) << left << LoanClient.GetCurrentLoan();
            cout << "| " << setw(20) << left << LoanClient.LoanBeginDate();
            cout << "| " << setw(20) << left << LoanClient.LoanEndDate();
        }

	public:

		static void ShowFindLoanClientScreen()
		{
            string Title = "\t Find Loan Client Screen";

            _DrawScreenHeader(Title);

            string AccountNumber;
            cout << "\nPlease Enter Account Number: ";
            AccountNumber = clsInputValidate::ReadString();
            while (!clsLoanClient::IsClientExist(AccountNumber))
            {
                cout << "\nAccount number is not found, choose another one: ";
                AccountNumber = clsInputValidate::ReadString();
            }

            clsLoanClient Client1 = clsLoanClient::Find(AccountNumber);

            if (!Client1.IsEmpty())
            {
                cout << "\nClient Found :-)\n";
            }
            else
            {
                cout << "\nClient Was not Found :-(\n";
            }

            _PrintLoanClientLine(Client1);

		}

};

