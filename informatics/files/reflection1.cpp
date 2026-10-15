#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n, k;
    if (!(cin >> n >> k)) {
        return;
    }

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    long long L = 0;
    for (int i = 0; i < k; ++i) {
        L = 2 * a[i] - L;
    }

    long long R = 0;
    for (int i = n - 1; i >= k; --i) {
        R = 2 * a[i] - R;
    }

    long long p = (L + R) / 2;

    cout << p << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}