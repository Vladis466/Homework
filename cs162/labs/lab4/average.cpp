/**
 * This function should output the average of an array 
 * (the array should have hard coded values)
 **/

#include <iostream>
#define SIZE 4

float average(int* valueArray, int size);

int main(){
	int array[SIZE] = {1, 2, 3, 4};
	float average_answer;
	average_answer = average(array, SIZE);
	std::cout << average_answer << std::endl;
}

/**
 * Function to calculate average of 
 * @param valueArray (populated array of values)
 * @param size (number of values inside array)
 * @return the average value of the array contents
 **/ 

float average(int* valueArray, int size){
  int i;
  float average = 0;
  float result;

  /* average calculation*/
  for(i = 0; i < size; i++){
    average = average + valueArray[i];
  }

  result = average / size;
  return result;
}

