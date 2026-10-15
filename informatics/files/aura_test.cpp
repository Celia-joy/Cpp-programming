#include <iostream>
#include <vector>
#include <array>
using namespace std;

#include "aura1.cpp"

int main() {
    vector<array<int, 3>> H;

    auto test1 = batalla_de_aura(10, 1, 0, H);
    cout << "Test 1: " << test1.first << " "
         << test1.second << '\n';

    auto test2 = batalla_de_aura(12, 2, 0, H);
    cout << "Test 2: " << test2.first << " "
         << test2.second << '\n';

    H.push_back({5, 5, 0});
    auto test3 = batalla_de_aura(10, 1, 1, H);
    cout << "Test 3: " << test3.first << " "
         << test3.second << '\n';

    return 0;
}