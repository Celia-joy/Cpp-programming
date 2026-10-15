
#include <bits/stdc++.h>
using namespace std;

struct Fenwick2D {
    int n, m;
    vector<vector<int>> bit;

    Fenwick2D(int n, int m) : n(n), m(m),
        bit(n + 1, vector<int>(m + 1, 0)) {}

    void add(int x, int y, int value) {
        if (x < 1 || x > n || y < 1 || y > m)
            return;

        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= m; j += j & -j) {
                bit[i][j] += value;
            }
        }
    }

    int sum(int x, int y) const {
        int result = 0;

        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                result += bit[i][j];
            }
        }

        return result;
    }

    int query(int x1, int y1, int x2, int y2) const {
        if (x1 > x2 || y1 > y2)
            return 0;

        return sum(x2, y2)
             - sum(x1 - 1, y2)
             - sum(x2, y1 - 1)
             + sum(x1 - 1, y1 - 1);
    }

    void build(const vector<vector<int>>& values) {
        bit = values;

        // Build the two-dimensional Fenwick tree in O(n*m).
        for (int i = 1; i <= n; ++i) {
            int p = i + (i & -i);
            if (p <= n) {
                for (int j = 1; j <= m; ++j)
                    bit[p][j] += bit[i][j];
            }
        }

        for (int j = 1; j <= m; ++j) {
            int p = j + (j & -j);
            if (p <= m) {
                for (int i = 1; i <= n; ++i)
                    bit[i][p] += bit[i][j];
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<vector<long long>> d(
            n + 1, vector<long long>(m + 1, 0)
        );

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j)
                cin >> d[i][j];
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                long long b;
                cin >> b;
                d[i][j] -= b;
            }
        }

        vector<vector<long long>> delta(
            n + 1, vector<long long>(m + 1, 0)
        );

        vector<vector<int>> nonzero(
            n + 1, vector<int>(m + 1, 0)
        );

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                delta[i][j] =
                    d[i][j] - d[i - 1][j]
                    - d[i][j - 1] + d[i - 1][j - 1];

                nonzero[i][j] = (delta[i][j] != 0);
            }
        }

        Fenwick2D fw(n, m);
        fw.build(nonzero);


        auto modify = [&](int x, int y, long long value) {
            if (x < 1 || x > n || y < 1 || y > m)
                return;

            int before = (delta[x][y] != 0);
            delta[x][y] += value;
            int after = (delta[x][y] != 0);

            if (before != after)
                fw.add(x, y, after - before);
        };

        int p;
        cin >> p;

        while (p--) {
            char type;
            int l1, l2, r1, r2;
            cin >> type >> l1 >> l2 >> r1 >> r2;

            if (type == 'u') {
                long long x;
                cin >> x;

                modify(l1, r1, x);
                modify(l1, r2 + 1, -x);
                modify(l2 + 1, r1, -x);
                modify(l2 + 1, r2 + 1, x);
            } else {

                int bad = fw.query(
                    l1 + 1, r1 + 1, l2, r2
                );

                cout << (bad == 0
                    ? "PUPILFUERZA"
                    : "NO") << '\n';
            }
        }
    }

    return 0;
}
