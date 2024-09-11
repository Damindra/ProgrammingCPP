// CalcV23.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;

using namespace std;

// error() simply disguises throws:
void error(string s)
{
	throw runtime_error(s);
}

int main()
{
	cout << "Please enter expression (we can handle + , -, * and /)\n";
	cout << "Add an x to end expression (e.g., 1+2*3x): ";
	int lval = 0;	// left value
	int rval = 0;	// right value
	cin >> lval;	// read left most operand
	if (!cin)
		error("no first operand");

	for (char op; cin >> op;) { // read operator and right hand repeatedly
		if (op != 'x') cin >> rval; // read right most operand if not equal to x
		if (!cin) error("no second operand"); // check for right operand, so not a '+ - * /' operator

		switch (op) {
		case '+':
			lval += rval; // add: lval = lval + rval
			break;
		case '-':
			lval -= rval; // subtract: lval = lval - rval
			break;
		case '*':
			lval *= rval; // multiply: lval = lval * rval
			break;
		case '/':
			lval /= rval; // divide: lval = lval / rval
			break;
		default: // if not a '+ - * /' operator print result
			cout << "Result: " << lval << '\n';
			return 0;
		}
	}
	error("bad expression");
}