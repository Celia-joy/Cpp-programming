#include <iostream>
using namespace std;

bool isSorted(int arr[], int size){
    if (size == 0 || size == 1){
        return true;
    }

    if (arr[size -2] <= arr[size - 1]){
        return isSorted(arr, size - 1);
    }

    return false;
}