#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <bits/stdc++.h>


using namespace std;

struct cc
{
	int *array;
	int cnum;
	int value;
};
struct change_1
{
	vector<int> change;
	int mincoins;
};
struct change_1 changeslow_algorithm_1(vector<int> v, int value)
{
	struct change_1 minchange, c_1, c_2;
	int tempMin;
	int length = v.size();
	minchange.mincoins = INT_MAX;
	//minchange.change = (int *)malloc(cnum*sizeof(int));

	for(int i =0; i< (int)v.size(); i++)
		minchange.change.push_back(0);

	for (int i=0; i<length; i++)//length
	{
		if (v[i] == value)
		{
			minchange.mincoins = 1;
			minchange.change[i]++;
			return minchange;
		}
	}

	for (int i = 1; i <= value/2; i++)
	{
		c_1 = changeslow_algorithm_1(v, i);
		c_2 = changeslow_algorithm_1(v, value-i);
		tempMin = c_1.mincoins + c_2.mincoins;
		if(tempMin < minchange.mincoins)
		{
			minchange.mincoins = tempMin;
			for (int j = 0; j< length; j++)//length
			{
				minchange.change[j] = c_1.change[j] + c_2.change[j];
			}
		}
	}
	return minchange;
}

struct change_1 changeslow_algorithm(struct cc data)
{
	vector<int> v;
	for (int i=0; i<data.cnum; i++)
	{
		v.push_back(data.array[i]);
	}
	return changeslow_algorithm_1(v, data.value);

}

int *greedy_algorithm(struct cc input)
{
	int j;
	int *change = (int *) malloc(input.cnum*sizeof(int));
	//	cout << change[2] << endl;
	for (int i=0; i<input.cnum; i++)
	{
		j = input.cnum - i - 1;	
		while (input.array[j] <= input.value)
		{
			input.value = input.value - input.array[j];
			change[j]++;
		}
	}
	return change;
}

int * DP_algorithm(struct cc input)
{
	int table[input.cnum][input.value+1];//include base 0;
	int* change = (int*) malloc (input.cnum*sizeof(int));
	for(int i=0; i<input.cnum; i++)//the first roll are all zero
		table[i][0] = 0;
	for(int i=0; i<input.value+1; i++)//the first column is up to value increase by 1
		table[0][i] = i;
	
	for(int i=1; i<input.cnum;i++)
	{
		for(int j = 1; j < input.value+1; j++)
		{
			if (j >= input.array[i] && 1+table[i][j-input.array[i]] < table[i-1][j])
				table[i][j] = 1+table[i][j-input.array[i]];
			else
				table[i][j] = table[i-1][j];
		}
	}
	int i,j;
	i = input.cnum-1;
	j = input.value;
	
	while(j > 0)
	{
		if(i == 0 || table[i][j] < table[i-1][j])
		{
			change[i]++;
			j -= input.array[i];
		}
		else
		{
			i--;
		}
	}
	return change;
}
void Print(FILE * q, int w, int c, struct cc *data)
{
	if (w==1)
	{
		fprintf(q, "Algorithm changeslow \n");
		printf("Algorithm changeslow \n");
	}
	if (w==2)
	{
		fprintf(q, "Algorithm greedy \n");
		printf("Algorithm greedy \n");
	}
	if (w==3)
	{
		fprintf(q, "Algorithm DP \n");
		printf("Algorithm DP \n");
	}
	for (int i=0; i<=c; i++)
	{
		int * a;
	/*	vector<int> b;
		if (w == 1)
		{
			struct change_1 q = changeslow_algorithm(data[i]);
			b  = q.change;
		}*/
		if (w == 2)
			a = greedy_algorithm(data[i]);
		else
			a = DP_algorithm(data[i]);
		int num_c = 0;
		for (int j = 0; j<data[i].cnum; j++)
		{
			fprintf(q, "%d ",data[i].array[j]);
			printf("%d ",data[i].array[j]);
		}
		fprintf(q, "\n");
		printf("\n");
		if ((w == 2)||(w == 3))
		{
			for (int p = 0; p<data[i].cnum; p++)
			{
				fprintf(q,"%d ", a[p]);
				printf("%d ", a[p]);
				num_c = num_c + a[p];
			}
		}
	/*	else
		{
			for (int p = 0; p<data[i].cnum; p++)
			{
				fprintf(q,"%d ", b[p]);
				printf("%d ", b[p]);
				num_c = num_c + b[p];
			}
		}*/
		fprintf(q,"\n");
		printf("\n");
		fprintf(q,"%d\n", num_c);
		printf("%d\n", num_c);
	}
}
int Get_data_and_test(FILE *pFile)
{
	struct cc *data = (struct cc*) malloc(10000);

	for(int i = 0; i < 10; i++)
	{
		data[i].array = (int *)malloc(10000);
	}
	int arra_1[100];
	int l = -1;
	int c;//the number of data sets;
	int buffer;
	char str[200];
	//FILE * pFile;
	//pFile = fopen(argv[1], "r");
	while(fgets(str, 200, pFile))
	{
		int  i=0;//the number of coins
		l++;
		c = l/2;
		char *pch;
		pch = strtok (str," ");
		while (pch != NULL)
		{
			buffer = atoi(pch);
			pch = strtok(NULL," ");

			if ((pch!=NULL)||((pch == NULL)&&(buffer!=0)))
			{

				if (l%2 == 0)
				{
					data[c].array[i] = buffer;

					i++;
					data[c].cnum = i;
				}

				else if (l%2 == 1)
					data[c].value = buffer;

			}
		}
	}
	FILE * p_1;
	p_1 = fopen("Coinchange.txt", "w");
	for(int i=3; i>=2; i--)
	{
		Print(p_1, i, c, data);
	}
	fprintf(p_1, "Algorithm changeslow \n");
        printf("Algorithm changeslow \n");
	for (int i=0; i<=c; i++)
        {
		struct change_1 cs = changeslow_algorithm(data[i]);
		vector<int>b = cs.change;
		for (int j = 0; j<data[i].cnum; j++)
                {
                        fprintf(p_1, "%d ",data[i].array[j]);
                        printf("%d ",data[i].array[j]);
                }
		fprintf(p_1, "\n");
                printf("\n");
		for (int p = 0; p<data[i].cnum; p++)
                        {
                                fprintf(p_1,"%d ", b[p]);
                                printf("%d ", b[p]);
                                //num_c = num_c + b[p];
                        }
		fprintf(p_1,"\n");
                printf("\n");
                fprintf(p_1,"%d\n", cs.mincoins);
                printf("%d\n", cs.mincoins);
		
	}
	fclose(p_1);	

}
int main(int argc, char *argv[])
{
	FILE * pFile;
	pFile = fopen(argv[1], "r");
	//string filename(argv[1]);
	//const char * c = filename.c_str();
	//cout << filename; 
	Get_data_and_test(pFile);
	return 0;
}
