#include <string>
#include <iostream>
using namespace std;
// do not add extra libraries here
/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    ascending : true for ascending, false for descending 
    size      : number of elements in the array
*/
int countingSort(std::string* arr, int size, int index, bool ascending);

int radix_string_sort(std::string* arr, int size, bool ascending)
{
    int cnt = 0;

    // Finding longest element
    std::string s = arr[0];
    for (int i=1; i<size; i++)
    {
        if (arr[i].length() > s.length())
            s = arr[i];
    }
    
    int len = s.length();
    for (int i=0; i<len; i++)
        cnt += countingSort(arr, size, len-i-1, ascending);
    
    return cnt;
}

int countingSort(std::string* arr, int size, int index, bool ascending)
{
    int *temp = new int[91], c=1;
    std::string *res = new std::string[size];

    for (int i=0; i<91; i++)
        temp[i] = 0;
    
    for (int i=0; i<size; i++)
    {
        temp[arr[i][index]]++;
        c++;
    }
    
    if (ascending)
    {
        for (int i=1; i<91; i++)
        {
            temp[i] += temp[i-1];
            if (i >= 66) c++;
        }
    }
    else
    {
        for (int i=89; i>=0; i--)
        {
            temp[i] += temp[i+1];
            if (i >= 65) c++;
        }
    }
    
    for (int i=size-1; i>=0; i--)
    {
        res[temp[arr[i][index]]-1] = arr[i];
        temp[arr[i][index]]--;
        c++;
    }
    
    //Copy array back
    for (int i=0; i<size; i++)
    {
        c++;
        arr[i] = res[i];
    }


    return c;
}

void swap(std::string& s1, std::string& s2)
{
    std::string tmp = s1;
    s1 = s2;
    s2 = tmp;
}
