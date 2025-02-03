#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "Global.h"
using namespace std;

class clsRequestTokenScreen : protected clsScreen
{
	private:

		static void _PrintUser(clsUser User)
		{
			cout << "\nUser Card:";
			cout << "\n___________________";
			cout << "\nFirstName   : " << User.FirstName;
			cout << "\nLastName    : " << User.LastName;
			cout << "\nFull Name   : " << User.FullName();
			cout << "\nEmail       : " << User.Email;
			cout << "\nPhone       : " << User.Phone;
			cout << "\nUser Name   : " << User.UserName;
			cout << "\nPassword    : " << User.Password;
			cout << "\nPermissions : " << User.Permissions;
			cout << "\n___________________\n";

		}

	public:

		static void ShowRequestTokenScreen()
		{
			if (!CheckAccessRights(clsUser::enPermissions::pRequestToken))
			{
				return;
			}

			_DrawScreenHeader("\t  Request Token Screen");

			cout << "User you want to generate token to ?";
			string UserName = "";
			cin >> UserName;
			while (!clsUser::IsUserExist(UserName))
			{
				cout << "\n\nInvalid UserName! Please Try Again:";
				cin >> UserName;
			}
			clsUser User1 = clsUser::Find(UserName);
			User1.Print();
			cout << "\n\nAre you sure you want to generate a token for this User?[y/n]";
			char choice = '\0';
			cin >> choice;
			if (choice == 'Y' || choice == 'y')
			{
				CurrentUser.RequestToken();
			}

			return;
		}
};

