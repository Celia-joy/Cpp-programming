#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------------------
// Idea general
//  * La ronda 0 no tiene informacion: es una jugada fija (a0, b0).
//  * Despues de cada ronda sabemos s = min(|x-a|,|x-b|), asi que x solo puede
//    ser uno de {a-s, a+s, b-s, b+s} (como mucho 4 candidatos, 2 si k = 1).
//    Se filtran con TODO el historial y con 1 <= x <= n.
//  * Con pocos candidatos se resuelve el juego restante de forma exacta con una
//    busqueda (minimax) sobre un conjunto pequeno de jugadas interesantes:
//    los candidatos, los puntos medios de pares de candidatos y sus vecinos.
//      - Con k = 2, si quedan 2 candidatos se juegan ambos: costo 0.
//      - Dos candidatos que quedan a la misma distancia de una jugada (su punto
//        medio) forman un grupo de 2 que luego cuesta 0.
//  * La primera jugada se escoge para equilibrar el peor caso:
//      k = 1 : a0 ~ n/3         (peor caso ~ 2n/3)
//      k = 2 : a0 ~ 0.1 n, b0 ~ 0.7 n (peor caso ~ 0.3 n)
// ---------------------------------------------------------------------------

static const int TOTAL_ROUNDS = 10;

namespace {

int N_, K_;

struct Res { int cost; int a, b; };

Res solveSet(const vector<int>& S, int R);

// Evalua una jugada (a,b) sobre el conjunto S. Devuelve costo peor caso o INF si
// no aporta informacion ni avance.
int evalMove(const vector<int>& S, int R, int a, int b, int bound) {
    // agrupar por perdida
    map<int, vector<int>> g;
    for (int x : S) g[min(abs(x - a), abs(x - b))].push_back(x);
    if (g.size() == 1 && g.begin()->second.size() == S.size()) return INT_MAX;
    int worst = 0;
    for (auto& kv : g) {
        int s = kv.first;
        if (s >= bound) return INT_MAX;
        int sub = (kv.second.size() <= 1) ? 0 : solveSet(kv.second, R - 1).cost;
        worst = max(worst, s + sub);
        if (worst >= bound) return INT_MAX;
    }
    return worst;
}

Res solveSet(const vector<int>& S, int R) {
    if (S.size() <= 1 || R <= 0) return {0, S.empty() ? 1 : S[0], S.empty() ? 1 : S[0]};
    if (K_ == 2 && S.size() == 2) return {0, S[0], S[1]};
    // jugadas candidatas
    set<int> P;
    auto add = [&](int v) { if (v >= 1 && v <= N_) P.insert(v); };
    for (int x : S) { add(x); add(x - 1); add(x + 1); }
    for (size_t i = 0; i < S.size(); i++)
        for (size_t j = i + 1; j < S.size(); j++) {
            int lo = (S[i] + S[j]) / 2;
            for (int d = -1; d <= 2; d++) add(lo + d);
        }
    vector<int> pos(P.begin(), P.end());
    Res best = {INT_MAX, pos[0], pos[0]};
    for (size_t i = 0; i < pos.size(); i++) {
        for (size_t j = i; j < pos.size(); j++) {
            if (K_ == 1 && j != i) break;
            int c = evalMove(S, R, pos[i], pos[j], best.cost);
            if (c < best.cost) best = {c, pos[i], pos[j]};
        }
    }
    if (best.cost == INT_MAX) best = {0, S[0], S.back()};
    return best;
}

// primera jugada
pair<int, int> primeraJugada(int n, int k) {
    if (k == 1) {
        // minimiza max(2L+1, R) con L = a0-1 (margen corto) y R = n-a0
        int bestA = 1, bestC = INT_MAX;
        for (int a = 1; a <= n; a++) {
            int L = a - 1, R = n - a;
            int lo = min(L, R), hi = max(L, R);
            int c = max(2 * lo + 1, hi);
            if (c < bestC) { bestC = c; bestA = a; }
        }
        return {bestA, bestA};
    }
    if (n == 10000) {
        return {1001, 7000};
    }
    double T = 0.3 * (n - 1);
    int L = (int)llround(T / 3.0), R = (int)llround(T);
    int a0 = min(n, max(1, L + 1)), b0 = min(n, max(1, n - R));
    return {a0, b0};
}

} // namespace

pair<int, int> batalla_de_aura(int n, int k, int r, vector<array<int, 3>> H) {
    N_ = n; K_ = k;
    if (r == 0 || H.empty()) return primeraJugada(n, k);

    // candidatos consistentes con todo el historial
    int a0 = H[0][0], b0 = (k == 1 ? H[0][0] : H[0][1]), s0 = H[0][2];
    set<int> cand;
    for (int x : {a0 - s0, a0 + s0, b0 - s0, b0 + s0}) {
        if (x < 1 || x > n) continue;
        bool ok = true;
        for (auto& h : H) {
            int a = h[0], b = (k == 1 ? h[0] : h[1]);
            if (min(abs(x - a), abs(x - b)) != h[2]) { ok = false; break; }
        }
        if (ok) cand.insert(x);
    }
    if (cand.empty()) return {1, 1};
    vector<int> S(cand.begin(), cand.end());
    if (S.size() == 1) return {S[0], S[0]};
    int remaining = TOTAL_ROUNDS - r;
    Res res = solveSet(S, min(remaining, 3));
    return {res.a, res.b};
}
