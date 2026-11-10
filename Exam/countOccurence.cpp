#include <iostream>
using namespace std;

int occurenceCount(int arr[], int size, int target){
    if (size == 0){
        return 0;
    }

    int match = 0

    if(arr[size - 1] == target){
        match = 1;
    }

    return match + occurenceCount(arr, size - 1,  target );  
}