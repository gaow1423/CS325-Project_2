/*****************
 * Problem_2_alg_3.cpp
 * Tyler Inberg
 * 4/27/2017
 * Program used to find minimum coins to equal cange 
 * Input: None
 * Output: Min coin count
 * ****************/

#include <iostream>
#include <string> //c++ strings
#include <cstdlib>
#include <algorithm>

using namespace std;


int main () {	
	int total = 35;
	int size_of_array = 4;
	int coin_values[4] = {1,5,10,25};
	int max_value, max_value_location;
	int minimum_coin_count = 0;
	int t[total+1];

	t[0] = 0;

	for(int i =1; i<=total; i++){
		t[i] = 10000;
	}

	for(int i=1;i<=total;i++){
		for(int j=0;j<size_of_array;j++){
			if(coin_values[j]<=i){
				minimum_coin_count = t[i-coin_values[j]];
				if (minimum_coin_count+1<t[i]){
					t[i]=minimum_coin_count + 1;
				}
			}
		}
	}

    cout << "The minimum number of coins needed is " << t[total] << "!\n";
 //   cout << "The max array is { ";
   // for(int a = beginning_index;a<=end_index; a++){
	 // cout << array[a];
   	 // cout << " ";
	//}
    cout << "}\n";

    return 0;
}

