#include <iostream>
using namespace std;

int countDigits(int n){
    if(n >= 0 && n <= 9){
        return 1;
    }
    return 1 + countDigits(n / 10);
}

int main(){
    cout << countDigits(2000) << endl;
    cout << countDigits(7) << endl;
    cout << countDigits(42) << endl;
    cout << countDigits(90000) << endl;
    return 0;
}

