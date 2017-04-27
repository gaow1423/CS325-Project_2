/*****************
 * Problem_2_alg_2.cpp
 * Tyler Inberg
 * 4/26/2017
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
	

	while (total != 0){
		for(int i = 0; i<size_of_array; i++){
			if (coin_values[i]>max_value){
		    	max_value = coin_values[i];
				max_value_location = i;
			}
		}	
		coin_values[max_value_location]=0;

		while (total >= max_value){
			total = total - max_value;
			minimum_coin_count++;
	//		cout << max_value;
		}
		max_value = 0;
	}

	
	



    cout << "The minimum number of coins needed is " << minimum_coin_count << "!\n";
 //   cout << "The max array is { ";
   // for(int a = beginning_index;a<=end_index; a++){
	 // cout << array[a];
   	 // cout << " ";
	//}
    cout << "}\n";

    return 0;
}

