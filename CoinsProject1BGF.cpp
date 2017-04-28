/*
*FileName:CoinsProject1BGF.cpp
*Author: Benjamin Fields
*Date:4/27/2017
*Description:Program that tests out multiple versions of the min change algorithm
*/

#include<iostream>
#include<fstream>

typedef struct {
	int *coins;
	int Total;
	int *numCoins;
	int count;
	int size;
}Solution;

Solution createSolution()
{
	Solution ans1;
	ans1.coins = new int[4];
	ans1.coins[0] = 1;
	ans1.coins[1] = 2;
	ans1.coins[2] = 4;
	ans1.coins[3] = 8;

	ans1.numCoins = new int[4];
	ans1.numCoins[0] = 1;
	ans1.numCoins[1] = 1;
	ans1.numCoins[2] = 1;
	ans1.numCoins[3] = 1;

	ans1.count = 4;
	ans1.Total = 15;
	ans1.size = 4;

	return ans1;
}


int ChangeSlow1(int coins[], int m, int V)
{
	// base case
	if (V == 0) return 0;

	// Initialize result
	int res = INT_MAX;

	// Try every coin that has smaller value than V
	for (int i = 0; i<m; i++)
	{
		if (coins[i] <= V)
		{
			int sub_res = ChangeSlow1(coins, m, V - coins[i]);

			// Check for INT_MAX to avoid overflow and see if
			// result can minimized
			if (sub_res != INT_MAX && sub_res + 1 < res)
				res = sub_res + 1;
		}
	}
	return res;
}

int changeGreedy(int coins[], int m, int V)
{
	int total = V;
	int count = 0;
	for (int i = m-1; i >-1; i--)
	{
		if (coins[i] == total)
		{
			count++;
			break;
		}
		if (coins[i] < total)
		{
			int numD = total / coins[i];
			total = total - numD*coins[i];
			count += numD;
		}
	}
	return count;
}

void printSolution(Solution ans)
{
	std::cout << "Solution Info:\n";
	std::cout << "   Coin Values: ";
	for (int i = 0; i < ans.size; i++)
	{
		std::cout << ans.coins[i] << " ";
	}
	std::cout << "\n   Coin Counts: ";
	for (int i = 0; i < ans.size; i++)
	{
		std::cout << ans.numCoins[i] << " ";
	}
	std::cout << "\n   Number of coins: " << ans.count << "\n";
	std::cout << "   Total: " << ans.Total << "\n";
}

int main(int argc, char **argv)
{
	Solution ans1;
	ans1 = createSolution();
	printSolution(ans1);

	int alg1 = ChangeSlow1(ans1.coins, ans1.size, ans1.Total);
	std::cout << "\nTesting Algorithm 1\n";
	std::cout << "Count of coins needed: " << alg1 << "\n";
	int alg2 = changeGreedy(ans1.coins, ans1.size, ans1.Total);
	std::cout << "\nTesting Algorithm 2\n";
	std::cout << "Count of coins needed: " << alg2 << "\n";

	delete[] ans1.coins;
	delete[] ans1.numCoins;

	std::cout << "************************************Press ENTER to exit program***********************\n";
	std::cin.get();
	return 0;
}