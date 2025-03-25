#pragma once
#include <iostream>
#include "clsCard.h"
#include "clsDebitCard.h"
#include "clsPrePaidCard.h"
#include "clsCreditCard.h"

using namespace std;

class clsCardFactory
{
	public:

		static enum enCardType { PrePaid = 1, Debit = 2, Credit = 3};

		static clsCard* CreateCard(enCardType CardType)
		{
            switch (CardType)
            {
            case enCardType::PrePaid:
                system("cls");
                return new clsPrePaidCard();
                break;
            case enCardType::Debit:
                system("cls");
                return new clsDebitCard();
                break;
            case enCardType::Credit:
                system("cls");
                return new clsCreditCard();
                
            default :
                system("cls");
                return nullptr;
            }
		}
};

