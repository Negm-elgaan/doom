#pragma once
#include <iostream>

using namespace std;

class VehicleFactory
{
	protected:

		string name;
		int NumberOfTires;
		int Seats;

	public:
		
		virtual string VehicleType() = 0;


};

