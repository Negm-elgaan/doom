#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include "clsdate.h"
#include <vector>
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <fstream>
#include "clsListLoansScreen.h"
#include "clsFindLoanClientScreen.h"

using namespace std;

class clsLoanScreen: protected clsScreen
{
	enum enLoanScreenMenueOption 
	{
		eLoanList = 1 ,
		eFindLoan = 2 ,
		eTakeLoan = 3 ,
		eRepayLoan = 4 ,
		eUpdateInterestRate = 5 ,
		eTotalBalanceInBank = 6 ,
		eLoanLogRecord = 7 ,
		eShowMainMenue = 8
	};
    static short ReadLoanMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 8]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 8, "Enter Number between 1 to 8 ");
        return Choice;
    }


    static void _ShowListLoansScreen()
    {
        clsListLoansScreen::ShowClientsList();       
    }

    static void _ShowFindLoanClientScreen()
    {
        clsFindLoanClientScreen::ShowFindLoanClientScreen();
    }

    static void _ShowTakeLoanScreen()
    {
        //cout << "\n Currency Calculator Screen will be here.\n";

    }
    
    static void _ShowRepayLoanScreen()
    {
        //cout << "\n Currency Calculator Screen will be here.\n";

    }

    static void _ShowUpdateInterestRateScreen()
    {
        //cout << "\n Update Rate Screen will be here.\n";
        
    }

    static void _ShowTotalBalancesScreen()
    {
        //cout << "\n Currency Calculator Screen will be here.\n";

    }

    static void _ShowLoanLogScreen()
    {
        //cout << "\n Currency Calculator Screen will be here.\n";

    }

    static void _GoBackToLoanMenue()
    {
        cout << "\n\nPress any key to go back to Currency Exchange Menue...";
        system("pause>0");
        ShowLoanMainMenue();

    }

    static void _PerformLoanMenueOption(enLoanScreenMenueOption CurrencyExchangeMenueOption)
    {
        switch (CurrencyExchangeMenueOption)
        {
        case enLoanScreenMenueOption::eLoanList:
        {
            system("cls");
            _ShowListLoansScreen();
            _GoBackToLoanMenue();
            break;
        }

        case enLoanScreenMenueOption::eFindLoan:
        {
            system("cls");
            _ShowFindLoanClientScreen();
            _GoBackToLoanMenue();
            break;
        }

        case enLoanScreenMenueOption::eTakeLoan:
        {
            system("cls");
            _ShowTakeLoanScreen();
            _GoBackToLoanMenue();
            break;
        }

        case enLoanScreenMenueOption::eRepayLoan:
        {
            system("cls");
            _ShowRepayLoanScreen();
            _GoBackToLoanMenue();
            break;
        }

        case enLoanScreenMenueOption::eUpdateInterestRate:
        {
            system("cls");
            _ShowUpdateInterestRateScreen();
            _GoBackToLoanMenue();
        }

        case enLoanScreenMenueOption::eTotalBalanceInBank:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToLoanMenue();
            break;
        }

        case enLoanScreenMenueOption::eLoanLogRecord:
        {
            system("cls");
            _ShowLoanLogScreen();
            _GoBackToLoanMenue();
            break;
        }

        case enLoanScreenMenueOption::eShowMainMenue:
        {
            //do nothing here the main screen will handle it :-) ;
        }
        }


    }


	public:
		static void ShowLoanMainMenue()
		{
			system("cls");
			_DrawScreenHeader("\t  Loan Main Screen");
			//_DrawDateScreen();
			//_DrawUserScreen();

			cout << setw(37) << left << "" << "===========================================\n";
			cout << setw(37) << left << "" << "\t\t  Loan Menue\n";
			cout << setw(37) << left << "" << "===========================================\n";
			cout << setw(37) << left << "" << "\t[1] List Loans.\n";
			cout << setw(37) << left << "" << "\t[2] Find Loan By Client.\n";
			cout << setw(37) << left << "" << "\t[3] Take Loan.\n";
			cout << setw(37) << left << "" << "\t[4] Repay Loan.\n";
			cout << setw(37) << left << "" << "\t[5] Update Interest Rate.\n";
			cout << setw(37) << left << "" << "\t[6] Total Balances.\n";
			cout << setw(37) << left << "" << "\t[7] Loan Log.\n";
			cout << setw(37) << left << "" << "\t[8] Main Menue.\n";
			cout << setw(37) << left << "" << "===========================================\n";

			_PerformLoanMenueOption((enLoanScreenMenueOption)ReadLoanMenueOption());
		}
		
};

