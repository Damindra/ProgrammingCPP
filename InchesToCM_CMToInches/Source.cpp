// Program that converts Inches to Centimeters AND Centimeters to Inches

import std;

using namespace std;

int main()
{
	constexpr double cm_per_inch = 2.54; // number of centimeters in an inch
	double length = 1; // length in inches or centimeters

	char unit = ' '; // a space is not a unit
	
	// Ask the user for a length and a unit
	cout << "This program converts inches to centimeters or centimeters to inches.\n";
	cout << "Please use C for centimeters or I for inches.\n";
	cout << "Please enter a length ";

	cin >> length ;

	cout << "Please enter a unit (C or I): ";

	cin >> unit;
	unit = toupper(unit); // make the unit uppercase

	switch (unit)
	{
	case 'C':
		cout << length << " cm == " << length / cm_per_inch << " in\n";
		break;
	case 'I':
		cout << length << " in == " << cm_per_inch * length << " cm\n";
		break;
	default:
		cout << "Sorry, I don't know a unit called '" << unit << "'\n";
		break;
	}

	
	//if (unit == 'C') // if the unit is centimeters
	//{
	//	cout << length << " cm == " << length / cm_per_inch << " in\n";
	//}
	//else if (unit == 'I' ) // if the unit is inches
	//{
	//	cout << length << " in == " << cm_per_inch * length  << " cm\n";
	//}
	//else
	//{
	//	cout << "Sorry, I don't know a unit called '" << unit << "'\n";
	//}
}