/*****************
 * Problem_2_alg_1.cpp
 * Tyler Inberg
 * 4/26/2017
 * Program used to find minimum coins to equal cange 
 * Input: None
 * Output: Min coin count
 * ****************/

#include <iostream>
#include <string> //c++ strings
#include <cstdlib>

using namespace std;

int MinimumCoinCount (int* array, int total, int size_of_array);

int main () {	
	int total = 35;
	int size_of_array = 4;
	int coin_values[4] = {1,5,10,25};
	
	int result = MinimumCoinCount (coin_values,total,size_of_array);



    cout << "The minimum number of coins needed is " << result << "!\n";
 //   cout << "The max array is { ";
   // for(int a = beginning_index;a<=end_index; a++){
	 // cout << array[a];
   	 // cout << " ";
	//}
    cout << "}\n";

    return 0;
}

int MinimumCoinCount (int array[], int total, int size_of_array){
    
   int minimum_coin_count=100000;

   if (total == 0)
	   return 0;
   
   else if (total < 0)
	   return 0;
   
   else{   
   	for (int i = 0; i<size_of_array; i++){
   		if(array[i]<=total){
			int coin_count = MinimumCoinCount(array,total-array[i], size_of_array);
			if (coin_count + 1 < minimum_coin_count)
			   minimum_coin_count = coin_count + 1;
		}
   	}
   return minimum_coin_count;
   }
}
