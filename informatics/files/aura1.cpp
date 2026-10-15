
#include <bits/stdc++.h>
using namespace std;

pair<int, int> batalla_de_aura(
    int n, int k, int r, vector<array<int, 3>> H
) {
    if (r == 0) {
        if (k == 1) {
            int a = (n + 1) / 2;
            return {a, a};
        }

        int a = max(1, n / 3);
        int b = max(a + 1, (2 * n) / 3);
        b = min(n, b);
        return {a, b};
    }

    vector<int> candidates;
    vector<long long> pastLoss(n + 1, 0);

    for (int x = 1; x <= n; ++x) {
        bool possible = true;
        long long total = 0;

        for (auto h : H) {
            int a = h[0], b = h[1], s = h[2];
            int loss = abs(x - a);

            if (k == 2)
                loss = min(loss, abs(x - b));

            if (loss != s) {
                possible = false;
                break;
            }
            total += loss;
        }

        if (possible) {
            candidates.push_back(x);
            pastLoss[x] = total;
        }
    }

    if (candidates.empty())
        return {1, 1};

    if (k == 1) {
        int bestA = 1;
        long long bestWorst = LLONG_MAX;

        for (int a = 1; a <= n; ++a) {
            long long worst = 0;

            for (int x : candidates) {
                worst = max(worst, pastLoss[x] + abs(x - a));
            }

            if (worst < bestWorst) {
                bestWorst = worst;
                bestA = a;
            }
        }

        return {bestA, bestA};
    }

    int bestA = candidates[0], bestB = candidates[0];
    long long bestWorst = LLONG_MAX;

    for (int a : candidates) {
        for (int b : candidates) {
            long long worst = 0;

            for (int x : candidates) {
                int loss = min(abs(x - a), abs(x - b));
                worst = max(worst, pastLoss[x] + loss);
            }

            if (worst < bestWorst) {
                bestWorst = worst;
                bestA = a;
                bestB = b;
            }
        }
    }

    return {bestA, bestB};
}
