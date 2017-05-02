/*
*FileName:Project2_CompleteBGF.cpp
*Author: Benjamin Fields
*Date:5/1/2017
*Description:Program that runs through all functionality required of project2.
Focus is on implementation of coin change problem in three algorithms.
Takes a command line file as test Input and generates a log file with the results of each algorithm.
Program then collects experimental data about algorithms with differnt A and generates an excel file with data
Program also tests the runtime of each algorithm under different A and generates an excel sheet with data.
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>

std::ofstream outPutFile;

enum {
	SLOW,
	GREEDY,
	DP
};

int ChangeSlow(std::vector<int> coins, int m, int V, int *coinsUsed)
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
			int sub_res = ChangeSlow(coins, m, V - coins[i], coinsUsed);


			if (sub_res != INT_MAX && sub_res + 1 < res)
			{
				res = sub_res + 1;

				coinsUsed[V] = i;//This is the key to track the coins used
			}
		}
	}

	return res;
}

int changeGreedy(std::vector<int> coins, int m, int V, int counts[])
{
	int total = V;
	int count = 0;
	for (int i = m - 1; i >-1; i--)
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

int changeDP(std::vector<int> coins, int m, int V, int coinsUsed[])
{
	int *table = new int[V + 1];
	table[0] = 0;

	for (int i = 1; i <= V; i++)
	{
		table[i] = INT_MAX;
	}

	for (int i = 1; i <= V; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (coins[j] <= i)
			{
				int sub_res = table[i - coins[j]];
				if (sub_res != INT_MAX && sub_res + 1 < table[i])
				{
					table[i] = sub_res + 1;
					coinsUsed[i] = j;
				}
			}
		}
	}

	return table[V];
}

void printCoinsUsed(std::vector<int> values, int *coinsUsed, int v, int count,int algorithm, int *GRDCounts)
{
	int *counts = 0;
	if (algorithm == SLOW||algorithm==DP)
	{
		int V = v;
		counts = new int[values.size()];
		for (int i = 0; i < values.size(); i++)
		{
			counts[i] = 0;
		}
		while (V>0)
		{
			int index = coinsUsed[V];
			counts[index]++;
			V = V - values[index];
		}
	}
	

	outPutFile << "Coin Values: ";
	std::cout << "Coin Values: ";
	for (int i = 0; i < values.size(); i++)
	{
		outPutFile << values[i] << " ";
		std::cout << values[i] << " ";
	}
	outPutFile << "\n";
	outPutFile << "Coin Counts: ";
	std::cout << "\n";
	std::cout << "Coin Counts: ";
	for (int i = 0; i < values.size(); i++)
	{
		if (algorithm == SLOW||algorithm==DP)
		{
			outPutFile << counts[i] << " ";
			std::cout << counts[i] << " ";
		}
		else
		{
			outPutFile << GRDCounts[i] << " ";
			std::cout << GRDCounts[i] << " ";
		}
		
	}
	outPutFile << "\n";
	outPutFile << "Total Coins: " << count << "\n";
	std::cout << "\n";
	std::cout << "Total Coins: " << count << "\n";

}

int InputOutputData(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "FILE INPUT ERROR:No input filename specified\n";
		return 0;
	}
	std::string inFileName = argv[1];
	std::cout << "FileName: " << inFileName <<".txt"<< std::endl;
	std::ifstream inputFile;
	inputFile.open(inFileName+".txt");
	if (!inputFile.is_open())
	{
		std::cout << "OPEN ERROR: Could not find file named: "<<inFileName<<" or failure to open file\n";
		return 0;
	}
	
	outPutFile.open(inFileName + "change.txt",std::ios::app);
	if (!outPutFile.is_open())
	{
		std::cout << "OPEN ERROR: Could not open output file named: " << inFileName+"change.txt" << " or failure to open file\n";
		return 0;
	}
	outPutFile.width(4);
	std::string V;
	std::string A;
	int count = 0;
	while (std::getline(inputFile,V))
	{
		
		count++;
		std::cout << "**********Case " << count << "**********\n";
		std::getline(inputFile, A);
		std::cout << "Values are: " << V << "\n";
		std::cout << "Amount is: " << A << "\n";

		char *str = _strdup(V.c_str());
		std::vector<int> Values;
		int Amount;

		char *subStr;
		subStr = strtok(str, " ");
		while (subStr != NULL)
		{
			Values.push_back(atoi(subStr));
			subStr = strtok(NULL, " ");
		}
		Amount = atoi(A.c_str());
		std::cout << "Values in vector: ";
		for (int i = 0; i < Values.size(); i++)
		{
			std::cout << Values[i] << " ";
		}
		std::cout << "\n";
		std::cout << "Amount to be Tested: " << Amount << "\n";

		outPutFile << "Case " << count << "\n";
		int *coinsUsed = new int[Amount + 1];
		memset(coinsUsed, -1, sizeof(coinsUsed));


		int numAlg1 = ChangeSlow(Values, Values.size(), Amount, coinsUsed);
		std::cout << "Algorithm 1 case " << count << " COMPLETE\n";
		outPutFile << "Algorithm ChangeSlow (Divide and Conquer)\n";
		int *counts = new int[Values.size()];
		for (int i = 0; i < Values.size(); i++)
		{
			counts[i] = 0;
		}
		printCoinsUsed(Values, coinsUsed, Amount, numAlg1,SLOW,counts);

		int numAlgGreedy = changeGreedy(Values, Values.size(), Amount, counts);
		std::cout << "Algorithm 2 case " << count << " COMPLETE\n";
		outPutFile << "Algorithm ChangeGreedy\n";
		printCoinsUsed(Values, coinsUsed, Amount, numAlgGreedy, GREEDY, counts);

		memset(coinsUsed, -1, sizeof(coinsUsed));
		int numAlgDP = changeDP(Values, Values.size(), Amount, coinsUsed);
		std::cout << "Algorithm 3 case " << count << " COMPLETE\n";
		outPutFile << "Algorithm ChangeDP(Dynamic Programming)\n";
		printCoinsUsed(Values, coinsUsed, Amount, numAlgDP, DP, counts);

	}

	
	inputFile.close();
	outPutFile.close();
	return 1;
}

int ExperimentalData()
{
	std::vector<int> V1 = { 1,2,6,12,24,48,60 };
	std::vector<int> V2 = { 1,5,10,25,50};
	std::vector<int> V3 = { 1,6,13,37,150};
	int counts[10] = { 0,0,0,0,0,0,0,0,0,0 };//place filler dont actually need
	int coinsUsed[3000];//place filler dont actually need but needed to pass to function
	memset(coinsUsed, -1, sizeof(coinsUsed));
	int A[50];
	int numX = 30;
	std::ofstream dataFile1;
	dataFile1.open("testSet1.csv");
	dataFile1 << "ChangeSlow V1\n";
	int n = 1;
	for (int i = 0; i < numX; i++)
	{
		dataFile1 << n<<",";
		dataFile1 << ChangeSlow(V1, V1.size(), n, coinsUsed) << "\n";
		std::cout << "Complete Changeslow V1 A: " << n << std::endl;
		n++;
	}
	
	dataFile1 << "ChangeSlow V2\n";
	n = 1;
	for (int i = 0; i < numX; i++)
	{
		dataFile1 << n << ",";
		dataFile1 << ChangeSlow(V2, V2.size(), n, coinsUsed) << "\n";
		std::cout << "Complete Changeslow V2 A: " << n << std::endl;
		n++;

	}
	dataFile1 << "ChangeSlow V3\n";
	n = 1;
	for (int i = 0; i < numX; i++)
	{
		dataFile1 << n << ",";
		dataFile1 << ChangeSlow(V3, V3.size(), n, coinsUsed) << "\n";
		std::cout << "Complete Changeslow V3 A: " << n << std::endl;
		n++;

	}
	dataFile1 << "ChangeGreedy V1\n";
	n = 1;
	for (int i = 0; i < numX; i++)
	{
		dataFile1 << n << ",";
		dataFile1 << changeGreedy(V1, V1.size(), n, counts) << "\n";
		std::cout << "Complete Greedy V1 A: " << n << std::endl;
		n++;

	}
	dataFile1 << "ChangeGreedy V2\n";
	n = 1;
	for (int i = 0; i < numX; i++)
	{
		dataFile1 << n << ",";
		dataFile1 << changeGreedy(V2, V2.size(), n, counts) << "\n";
		std::cout << "Complete Greedy V2 A: " << n << std::endl;
		n++;
	}
	dataFile1 << "ChangeGreedy V3\n";
	n = 1;
	for (int i = 0; i < numX; i++)
	{
		dataFile1 << n << ",";
		dataFile1 << changeGreedy(V3, V3.size(), n, counts) << "\n";
		std::cout << "Complete Greedy V3 A: " << n << std::endl;
		n++;
	}

	dataFile1 << "ChangeDP V1\n";
	n = 1;
	for (int i = 0; i < numX; i++)
	{
		dataFile1 << n << ",";
		dataFile1 << changeDP(V1, V1.size(), n, coinsUsed) << "\n";
		std::cout << "Complete DP V1 A: " << n << std::endl;
		n++;
	}
	dataFile1 << "ChangeDP V2\n";
	n = 1;
	for (int i = 0; i < numX; i++)
	{
		dataFile1 << n << ",";
		dataFile1 << changeDP(V2, V2.size(), n, coinsUsed) << "\n";
		std::cout << "Complete DP V2 A: " << n << std::endl;
		n++;
	}
	dataFile1 << "ChangeDP V3\n";
	n = 1;
	for (int i = 0; i < numX; i++)
	{
		dataFile1 << n << ",";
		dataFile1 << changeDP(V3, V3.size(), n, coinsUsed) << "\n";
		std::cout << "Complete DP V3 A: " << n << std::endl;
		n++;
	}
	std::cout << "\n\n***********Second Set***************\n";
	std::ofstream outfile2;
	outfile2.open("testSet2.csv");
	
	n = 2000;
	outfile2 << "Greedy V1\n";
	for (int i = 0; i < 201; i++)
	{
		outfile2 << n << ",";
		outfile2 << changeGreedy(V1, V1.size(), n, counts) << "\n";
		std::cout << "Complete Greedy V1 A: " << n << std::endl;
		n++;
	}
	n = 2000;
	outfile2 << "Greedy V2\n";
	for (int i = 0; i < 201; i++)
	{
		outfile2 << n << ",";
		outfile2 << changeGreedy(V2, V2.size(), n, counts) << "\n";
		std::cout << "Complete Greedy V2 A: " << n << std::endl;
		n++;
	}
	n = 2000;
	outfile2 << "Greedy V3\n";
	for (int i = 0; i < 201; i++)
	{
		outfile2 << n << ",";
		outfile2 << changeGreedy(V3, V3.size(), n, counts) << "\n";
		std::cout << "Complete Greedy V3 A: " << n << std::endl;
		n++;
	}
	n = 2000;
	outfile2 << "ChangeDP V1\n";
	for (int i = 0; i < 201; i++)
	{
		outfile2 << n << ",";
		outfile2 << changeDP(V1, V1.size(), n, coinsUsed) << "\n";
		std::cout << "Complete DP V1 A: " << n << std::endl;
		n++;
	}
	n = 2000;
	outfile2 << "ChangeDP V2\n";
	for (int i = 0; i < 201; i++)
	{
		outfile2 << n << ",";
		outfile2 << changeDP(V2, V2.size(), n, coinsUsed) << "\n";
		std::cout << "Complete DP V2 A: " << n << std::endl;
		n++;
	}
	n = 2000;
	outfile2 << "ChangeDP V3\n";
	for (int i = 0; i < 201; i++)
	{
		outfile2 << n << ",";
		outfile2 << changeDP(V3, V3.size(), n, coinsUsed) << "\n";
		std::cout << "Complete DP V3 A: " << n << std::endl;
		n++;
	}
	outfile2.close();
	dataFile1.close();
	return 1;
}

int RuntimeData()
{
	std::cout << "\n\n******RUNTIME DATA*******\n";
	clock_t t1, t2;
	std::vector<int> coins = { 1,5,10,25 };
	int testA1[] = { 5,10,20,30,40,50 };
	int testA2[] = { 100,1000,5000,10000,15000,20000 };
	int counts[10] = { 0,0,0,0,0,0,0,0,0,0 };//place filler dont actually need
	int coinsUsed[22000];//place filler dont actually need
	std::ofstream timeFile;
	timeFile.open("Runtimes.csv");
	timeFile << "Changeslow\n";
	for (int i = 0; i < 6; i++)
	{
		timeFile << testA1[i] << ",";
		t1 = clock();
		int ans = ChangeSlow(coins, coins.size(), testA1[i], coinsUsed);
		t2 = clock();
		float diff((float)t2 - (float)t1);
		float seconds = diff / CLOCKS_PER_SEC;
		timeFile << seconds << "\n";
		std::cout << "Complete Changeslow with A: " << testA1[i] << "\n";
	}
	timeFile << "ChangeGreedy\n";
	for (int i = 0; i < 6; i++)
	{
		timeFile << testA2[i] << ",";
		t1 = clock();
		int ans = changeGreedy(coins, coins.size(), testA2[i], counts);
		t2 = clock();
		float diff((float)t2 - (float)t1);
		float seconds = diff / CLOCKS_PER_SEC;
		timeFile << seconds << "\n";
		std::cout << "Complete Greedy with A: " << testA2[i] << "\n";
	}
	timeFile << "ChangeDP\n";
	for (int i = 0; i < 6; i++)
	{
		timeFile << testA2[i] << ",";
		t1 = clock();
		int ans = changeDP(coins, coins.size(), testA2[i], coinsUsed);
		t2 = clock();
		float diff((float)t2 - (float)t1);
		float seconds = diff / CLOCKS_PER_SEC;
		timeFile << seconds << "\n";
		std::cout << "Complete Changeslow with A: " << testA2[i] << "\n";
	}
	timeFile.close();
	return 1;
}

int main(int argc, char **argv)
{
	int success;
	success = InputOutputData(argc, argv);
	if (!success)
	{
		std::cout << "PROGRAM FAILURE\n";
	}
	success = ExperimentalData();
	if (!success)
	{
		std::cout << "PROGRAM FAILURE\n";
	}

	success = RuntimeData();
	if (!success)
	{
		std::cout << "PROGRAM FAILURE\n";
	}
	std::cout << "************************************Press ENTER to exit program***********************\n";
	std::cin.get();
	return 0;
}