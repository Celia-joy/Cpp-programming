#include <bits/stdc++.h>
using namespace std;

// D = A - B. Una submatriz de D se puede llevar a 0 sumando constantes a filas y
// columnas  <=>  D[i][j] = u_i + v_j en la region  <=>  el arreglo de diferencias
//   d[i][j] = D[i][j] - D[i-1][j] - D[i][j-1] + D[i-1][j-1]
// vale 0 para toda i en (l1, l2] y j en (r1, r2].
// Sumar x a una submatriz de A solo cambia 4 entradas de d (las esquinas),
// asi que se mantiene un BIT 2D con la cantidad de entradas de d distintas de 0.

int n, m;
vector<long long> d;     // (n+2)*(m+2)
vector<int> bit;         // (n+1)*(m+1)

static inline int W() { return m + 2; }

void bitAdd(int i, int j, int v) {
    for (int x = i; x <= n; x += x & -x)
        for (int y = j; y <= m; y += y & -y)
            bit[x * (m + 1) + y] += v;
}
int bitSum(int i, int j) {
    int r = 0;
    for (int x = i; x > 0; x -= x & -x)
        for (int y = j; y > 0; y -= y & -y)
            r += bit[x * (m + 1) + y];
    return r;
}
int rectCount(int i1, int i2, int j1, int j2) {
    if (i1 > i2 || j1 > j2) return 0;
    return bitSum(i2, j2) - bitSum(i1 - 1, j2) - bitSum(i2, j1 - 1) + bitSum(i1 - 1, j1 - 1);
}
void pointAdd(int i, int j, long long x) {
    if (i < 1 || j < 1 || i > n || j > m) return;
    long long &v = d[i * W() + j];
    bool was = v != 0;
    v += x;
    bool now = v != 0;
    if (was != now) bitAdd(i, j, now ? 1 : -1);
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        scanf("%d %d", &n, &m);
        vector<long long> D((size_t)(n + 2) * (m + 2), 0);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                int v;
                scanf("%d", &v);
                D[i * W() + j] = v;
            }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                int v;
                scanf("%d", &v);
                D[i * W() + j] -= v;
            }
        d.assign((size_t)(n + 2) * (m + 2), 0);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                d[i * W() + j] = D[i * W() + j] - D[(i - 1) * W() + j] - D[i * W() + j - 1] + D[(i - 1) * W() + j - 1];
        // construccion lineal del BIT 2D
        bit.assign((size_t)(n + 1) * (m + 1), 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                bit[i * (m + 1) + j] += (d[i * W() + j] != 0);
                int j2 = j + (j & -j);
                if (j2 <= m) bit[i * (m + 1) + j2] += bit[i * (m + 1) + j];
            }
        }
        for (int i = 1; i <= n; i++) {
            int i2 = i + (i & -i);
            if (i2 <= n)
                for (int j = 1; j <= m; j++) bit[i2 * (m + 1) + j] += bit[i * (m + 1) + j];
        }
        int p;
        scanf("%d", &p);
        while (p--) {
            char c;
            scanf(" %c", &c);
            if (c == 'q') {
                int l1, l2, r1, r2;
                scanf("%d %d %d %d", &l1, &l2, &r1, &r2);
                puts(rectCount(l1 + 1, l2, r1 + 1, r2) == 0 ? "PupilFuerza" : "No");
            } else {
                int l1, l2, r1, r2, x;
                scanf("%d %d %d %d %d", &l1, &l2, &r1, &r2, &x);
                pointAdd(l1, r1, x);
                pointAdd(l1, r2 + 1, -x);
                pointAdd(l2 + 1, r1, -x);
                pointAdd(l2 + 1, r2 + 1, x);
            }
        }
    }
    return 0;
}
