#include <bits/stdc++.h>
using namespace std;

// Estrategia: en la ronda r escapan exactamente las prisioneras cuyo color lo
// llevan r prisioneras en total (contando a ella misma).
//
// Razonamiento de la prisionera `id` en la ronda r (sigue presa):
//  - Los colores que ya "escaparon" (alguna otra prisionera con ese color ya
//    escapo) no pueden ser el suyo: si lo fueran, ella habria escapado junto con
//    ellas en esa misma ronda.
//  - Para los demas colores c sea q[c] = cuantas OTRAS prisioneras presas tienen
//    c. Si su color fuera c, entonces c tendria q[c]+1 prisioneras en total, y
//    como todavia no escapan, q[c]+1 >= r  (q[c] >= r-1). Ademas, cualquier otro
//    color c' que siga presente debe cumplir q[c'] >= r (si no, ya habria
//    escapado en una ronda anterior).
//  - Por lo tanto, si exactamente un color tiene q = r-1 (y el resto q >= r),
//    ese es su color: lo anuncia. Si todos tienen q >= r, no puede saberlo
//    todavia y se queda callada.
//  - En la ronda 1 esto incluye al color que no ve en nadie mas (q = 0): al
//    menos una prisionera lleva cada color, asi que ese es el suyo.
// Una prisionera cuyo color lo llevan t prisioneras escapa en la ronda t <= n.
int adivinar_sombrero(int n, int k, int r, vector<int> C, vector<int> E, int id) {
    vector<int> q(k + 1, 0);
    vector<bool> escapado(k + 1, false);
    for (int i = 0; i < n; i++) {
        if (i == id) continue;
        if (E[i] != 0) escapado[C[i]] = true;
        else q[C[i]]++;
    }
    int candidato = 0, cuantos = 0;
    for (int c = 1; c <= k; c++) {
        if (escapado[c]) continue;
        if (q[c] == r - 1) {
            candidato = c;
            cuantos++;
        }
    }
    if (cuantos == 1) return candidato;
    return 0;
}
