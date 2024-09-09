// CalcV23.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;

using namespace std;



int main()
{
	cout << "Please enter expression (we can handle + and -):";
	int lval = 0;	// left value
	int rval = 0;	// right value
	char op = 0;	// operator
	int res = 0;	// result
	cin >> lval >> op >> rval; // read something like 1 + 3

	if (op == '+')
		res = lval + rval; // addition
	else if (op == '-')
		res = lval - rval; // subtraction
	cout << "Result: " << res << '\n';
}