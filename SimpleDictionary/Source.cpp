// Simple dictionary program using vector


import std;

using namespace std;

int main()

{

	vector<string> words;

	string temp;

	cout << "Enter words separated by space. Enter 'finishedlist' when finished." << endl;

	while (cin >> temp)

	{

		if (temp == "finishedlist")

			break;

		words.push_back(temp); // add word to vector

	}

	sort(words.begin(), words.end()); // sort the words alphabetically

	cout << "Words in sorted order:" << endl;

	for (int i = 0; i < words.size(); i++) {

		if (i == 0 || words[i] != words[i - 1]) { // check for duplicates since we sorted the words
			cout << words[i] << endl;
		}
		else
		{
			cout << "Duplicate word: " << words[i] << endl;
		}
	}
	return 0;


}