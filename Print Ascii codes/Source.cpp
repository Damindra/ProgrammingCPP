// This program prints the ascii value of characters a-z and A-Z

import std;

using namespace std;

int main()
{
	char lowercaseLetters;
	char uppercaseLetters;

	cout << "ASCII values of lowercase and uppercase letters are as follows: " << endl;
	cout << "--------------------------------------------------------------" << endl;
	for (lowercaseLetters = 'a'; lowercaseLetters <= 'z'; lowercaseLetters++)
	{
		cout << lowercaseLetters << " = " << int(lowercaseLetters) << endl;
	}
	for (uppercaseLetters = 'A'; uppercaseLetters <= 'Z'; uppercaseLetters++)
	{
		cout << uppercaseLetters << " = " << int(uppercaseLetters) << endl;
	}
	return 0;
}





