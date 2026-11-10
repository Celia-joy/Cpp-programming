#include <iostream>
using namespace std;

void countDown(int n){
    if(n<=0){
        return;
    }
    cout<< n << " ";
    countDown(n - 1 );
} 