#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, k;
        cin >> n >> k;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        // Simulate reflections across first k points
        long long pos = 0;
        for (int i = 0; i < k; i++) {
            pos = 2LL * a[i] - pos;
        }
        
        // Work backwards from 0 through remaining points
        long long need = 0;
        for (int i = n - 1; i >= k; i--) {
            need = 2LL * a[i] - need;
        }
        
        // Find p such that reflecting pos across p gives need
        // 2p - pos = need, so p = (pos + need) / 2
        long long p = (pos + need) / 2;
        
        cout << p << "\n";
    }
    
    return 0;
}
