#include <bits/stdc++.h>
using namespace std;

// Cada reflejo respecto a a es x -> 2a - x. La composicion de varios reflejos
// es una funcion x -> s*x + c con s = +-1.
// Sea f = reflejos de a1..ak (se aplica a 0 -> c1), g = reflejos de a(k+1)..an
// (g(y) = s2*y + c2 con s2 = (-1)^(n-k), c2 = g(0)).
// Se necesita g(2p - c1) = 0  =>  2p - c1 = -s2*c2  =>  p = (c1 - s2*c2)/2.
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, k;
        scanf("%d %d", &n, &k);
        vector<long long> a(n);
        for (auto &v : a) scanf("%lld", &v);
        long long c1 = 0;
        for (int i = 0; i < k; i++) c1 = 2 * a[i] - c1;
        long long c2 = 0;
        for (int i = k; i < n; i++) c2 = 2 * a[i] - c2;
        long long s2 = ((n - k) % 2 == 0) ? 1 : -1;
        long long p = (c1 - s2 * c2) / 2;
        printf("%lld\n", p);
    }
    return 0;
}
