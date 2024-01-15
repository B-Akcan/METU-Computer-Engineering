// this file is for you for testing purposes, it won't be included in evaluation.

#include <iostream>
#include <fstream>
#include "the2.cpp"

int main(){
    
    int size=5, c;
    std::string arr[5] = {"OGUZ", "UMAY", "ASLI", "EMRE", "EREN"};

    c = radix_string_sort(arr, size, true);  // returns the number of iterations

    std::cout << c << endl;
    for (int i=0; i<size; i++)
        cout << arr[i] << " ";
    std::cout << std::endl;

	return 0;
}
