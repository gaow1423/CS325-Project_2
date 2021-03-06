#include <iostream>
#include <string>
#include <cstdlib>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

struct change
{
	vector<int> coins;
	int minimum;
};

struct change changeslow(vector<int> v, int amount)
{
	struct change myChange, tempChange1, tempChange2;
	int length = v.size();
	int tempMin;
	int sum1 = 0; 
	int sum2 = 0;

	//Initialize myChange.minimum and myChange.coins.
	myChange.minimum = INT_MAX;
	for(int i =0; i< (int) v.size(); i++)
		myChange.coins.push_back(0);


	for (int i=0; i<v.size(); i++)
	{
		if (v[i] == amount)
		{
			//myChange.minimum = 1;
			//myChange.coins[i]++;
			myChange.coins[i] = 1;
		    return myChange;
		}
	}
	/*if no single coin equals amount, recursively call changeslow on each possible pair i and amount - i and determine their sum. Take the value i that minimizes that sum and return value with corresponding coin vector.
*/

	for (int i = amount - 1; i >= amount/2; i--)
	{
		tempChange1 = changeslow(v,i);
		tempChange2 = changeslow(v,amount-i);
		
		for (int a=0; a<tempChange1.coins.size();a++)
		   sum1 = sum1 + tempChange1.coins[a];
		
		for (int b=0; b<tempChange2.coins.size();b++)
		   sum2 = sum2 + tempChange2.coins[b];
		
		tempMin = sum1 + sum2;
		//tempMin = tempChange1.minimum + tempChange2.minimum;
		if( myChange.minimum > tempMin)
		{
			myChange.minimum = tempMin;
			for (int j =0; j< tempChange2.coins.size(); j++)
			//for (int j = 0; j<length; j++)
				myChange.coins[j] = tempChange1.coins[j] + tempChange2.coins[j];
		}
	}
	//cout << myChange.minimum << endl;
	return myChange;
}


int main()
{
	//static const int arr[] = {1,3,7,12};
	//vector<int> v (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	vector<int> v;
	v.push_back(1);
	v.push_back(3);
	v.push_back(7);
	v.push_back(12);
	//cout << v[2] << endl;	
	//vector<int> v = {1,3,7,12};
	//cout << "1"<<endl;
	int amount = 29;
	
	struct change c = changeslow(v, amount);
	cout << "1" << endl;
	for (int i=0; i<v.size(); i++)
	{
		cout << c.coins[i] << endl;
	}
	return 0;
			
}






