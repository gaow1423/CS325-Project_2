/*
*FileName:CoinsProject1BGF.cpp
*Author: Benjamin Fields
*Date:4/27/2017
*Description:Program that tests out multiple versions of the min change algorithm
*/

#include<iostream>
#include<fstream>


int ChangeSlow1(int coins[], int m, int V, int coinsUsed[])
{
	// base case
	if (V == 0)
	{
		return 0;
	}
		

	// Initialize result
	int res = INT_MAX;

	// Try every coin that has smaller value than V
	for (int i = 0; i<m; i++)
	{
		if (coins[i] <= V)
		{
			int sub_res = ChangeSlow1(coins, m, V - coins[i],coinsUsed);
			

			if (sub_res != INT_MAX && sub_res + 1 < res)
			{
				res = sub_res + 1;

				coinsUsed[V] = i;//This is the key to track the coins used
			}
		}
	}
	
	return res;
}

int changeGreedy(int coins[], int m, int V, int counts[])
{
	int total = V;
	int count = 0;
	for (int i = m-1; i >-1; i--)
	{
		if (coins[i] == total)
		{
			counts[i] += 1;
			count++;
			break;
		}
		if (coins[i] < total)
		{
			int numD = total / coins[i];
			total = total - numD*coins[i];
			count += numD;
			counts[i] += numD;
		}
	}
	return count;
}

void printCoinsUsed(int values[], int coinsUsed[], int v)
{
	int V = v;
	int counts[] = { 0,0,0,0 };
	while (V>0)
	{
		int index = coinsUsed[V];
		counts[index]++;
		V = V - values[index];
	}
	std::cout << "Count of coins used: ";
	for (int i = 0; i < 4; i++)
	{
		std::cout << counts[i] << " ";
	}
	std::cout << "\n";
}

void unitTest1()
{
	std::cout << "\n****Testing with values [1 3 7 12] and V = 31. Should get 0,0,1,2 for both with m=3\n";
	int coins[] = { 1,3,7,12 };
	int counts2[] = { 0,0,0,0 };
	int coinsUsed[32];
	for (int i = 0; i < 32; i++)
	{
		coinsUsed[i] = -1;
	}
	int numAlg1 = ChangeSlow1(coins, 4, 31, coinsUsed);
	std::cout << "Number of coins needed for divide and conquer: " << numAlg1 << "\n";
	std::cout << "Coins for each V: ";
	for (int i = 0; i < 31; i++)
	{
		std::cout << coinsUsed[i] << " ";
	}
	std::cout << "\n";
	printCoinsUsed(coins, coinsUsed, 31);
	std::cout << "\n";
	int numAlg2 = changeGreedy(coins, 4, 31, counts2);
	std::cout << "Number of coins needed for greedy algorithm: " << numAlg2 << "\n";
	std::cout << "Number of coins: ";
	for (int i = 0; i < 4; i++)
	{
		std::cout << counts2[i] << " ";
	}
	std::cout << "\n*****DONE\n";
}

void unitTest2()
{
	std::cout << "\n****Testing with values [1 3 7 12] and V = 29. Should get 0,1,2,1 and m = 4 for changeslow amd  2,1,0,2 with m=5 for greedy\n";
	int coins[] = { 1,3,7,12 };
	int counts2[] = { 0,0,0,0 };
	int coinsUsed[30];
	for (int i = 0; i < 30; i++)
	{
		coinsUsed[i] = -1;
	}
	int numAlg1 = ChangeSlow1(coins, 4, 29, coinsUsed);
	std::cout << "Number of coins needed for divide and conquer: " << numAlg1 << "\n";
	std::cout << "Coins for each V: ";
	for (int i = 0; i < 30; i++)
	{
		std::cout << coinsUsed[i] << " ";
	}
	std::cout << "\n";
	printCoinsUsed(coins, coinsUsed, 29);
	std::cout << "\n";
	int numAlg2 = changeGreedy(coins, 4, 29, counts2);
	std::cout << "Number of coins needed for greedy algorithm: " << numAlg2 << "\n";
	std::cout << "Number of coins: ";
	for (int i = 0; i < 4; i++)
	{
		std::cout << counts2[i] << " ";
	}
	std::cout << "\n*****DONE\n";
}

void unitTest3()
{
	std::cout << "\n*****Testing with values [1 2 4 8] and V = 15. Should get 1,1,1,1 with m=4 for both\n";
	int coins[] = { 1,2,4,8 };
	int counts2[] = { 0,0,0,0 };
	int coinsUsed[16];
	for (int i = 0; i < 16; i++)
	{
		coinsUsed[i] = -1;
	}
	int numAlg1 = ChangeSlow1(coins, 4, 15, coinsUsed);
	std::cout << "Number of coins needed for divide and conquer: " << numAlg1 << "\n";
	std::cout << "Coins for each V: ";
	for (int i = 0; i < 16; i++)
	{
		std::cout << coinsUsed[i] << " ";
	}
	std::cout << "\n";
	printCoinsUsed(coins, coinsUsed, 15);
	std::cout << "\n";
	int numAlg2 = changeGreedy(coins, 4, 15, counts2);
	std::cout << "Number of coins needed for greedy algorithm: " << numAlg2 << "\n";
	std::cout << "Number of coins: ";
	for (int i = 0; i < 4; i++)
	{
		std::cout << counts2[i] << " ";
	}
	std::cout << "\n*****DONE\n";
}

int main(int argc, char **argv)
{
	unitTest1();
	unitTest2();
	unitTest3();
	std::cout << "************************************Press ENTER to exit program***********************\n";
	std::cin.get();
	return 0;
}