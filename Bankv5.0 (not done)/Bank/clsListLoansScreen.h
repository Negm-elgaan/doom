#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsLoanClient.h"


using namespace std;

class clsListLoansScreen : protected clsScreen
{
    static void PrintLoanClientLine(clsLoanClient LoanClient)
    {

        cout << setw(8) << left << "" << "| " << setw(30) << left << LoanClient.AccountNumber;
        cout << "| " << setw(12) << left << LoanClient.FullName;
        cout << "| " << setw(40) << left << LoanClient.AccountNumber;
        cout << "| " << setw(40) << left << LoanClient.Phone;
        //cout << "| " << setw(20) << left << LoanClient
        cout << "| " << setw(20) << left << LoanClient.GetCreditScore(); 
    }
    public:
        static void ShowClientsList()
        {


            vector <clsLoanClient> vLoanClients = clsLoanClient::GetLoansList();
            string Title = "\t  Loan Client List Screen";
            string SubTitle = "\t    (" + to_string(vLoanClients.size()) + ") Client(s).";

            _DrawScreenHeader(Title, SubTitle);
            //_DrawDateScreen();
            //_DrawUserScreen();

            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;

            cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
            cout << "| " << left << setw(20) << "Client Name";
            cout << "| " << left << setw(12) << "Loan";
            cout << "| " << left << setw(12) << "Loan with interest";
            cout << "| " << left << setw(20) << "Loan Begin Date";
            cout << "| " << left << setw(10) << "Loan End Date";
            cout << "| " << left << setw(12) << "Interest Rate";
            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;

            if (vLoanClients.size() == 0)
                cout << "\t\t\t\tNo Clients Available In the System!";
            else

                for (clsLoanClient Client : vLoanClients)
                {

                    PrintLoanClientLine(Client);
                    cout << endl;
                }

            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;

        }

};

/*string _AccountNumber;
		string _FullName;
		double _Loan;
		string _LoanBeginDate;
		string _LoanEndDate;
        double _InterestRate;*/