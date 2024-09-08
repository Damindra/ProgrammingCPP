// Calculate average and median of tempature readings

#include <iostream>
#include <vector>

#include <algorithm>

using namespace std;

int main()
{
	vector<double> temps; // temperatures read stored in vector
	double temp;	// individual temperature reading
	cout << "Enter temperature readings: (enter q to end readings)" << endl;
	while (cin >> temp)
	{
		temps.push_back(temp); // add temperature to vector
	}

	double sum = 0;
	for (int i = 0; i < temps.size(); i++)	// loop through all temperatures, 
											//temps.size() returns the number of elements in the vector
	{
		sum += temps[i]; // sum of all temperatures
	}

	cout << "Average temperature: " << sum / temps.size() << endl;

	sort(temps.begin(), temps.end()); // sort the temperatures in ascending order
	double median;
	if (temps.size() % 2 == 0)
	{
		median = (temps[temps.size() / 2] + temps[temps.size() / 2 - 1]) / 2; // if number of temperatures is even, median is average of two middle values
	}
	else
	{
		median = temps[temps.size() / 2]; // if number of temperatures is odd, median is the middle value
	}

	cout << "Median temperature: " << median << endl;

	return 0;
}