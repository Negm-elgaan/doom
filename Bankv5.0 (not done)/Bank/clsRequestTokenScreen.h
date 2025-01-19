#pragma once
#include <iostream>
#include "clsScreen.h"
using namespace std;

class clsRequestTokenScreen : protected clsScreen
{
	public:

		static void ShowRequestTokenScreen()
		{
			if (!CheckAccessRights(clsUser::enPermissions::pRequestToken))
			{
				return;
			}

			_DrawScreenHeader("\t  Request Token Screen");
		}
};

