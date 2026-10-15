#include <vector>
using namespace std;

int adivinar_sombrero(int n, int k, int r, vector<int> C, vector<int> E, int id)
{
    vector<int> seen(k + 1, 0);
    vector<bool> color_left(k + 1, false);

    for (int i = 0; i < n; i++)
    {
        if (i == id)
            continue;
        seen[C[i]]++;
        if (E[i] > 0)
        {
            color_left[C[i]] = true;
        }
    }

    for (int color = 1; color <= k; color++)
    {
        if (color_left[color])
            continue;
        if (seen[color] == r - 1)
        {
            return color;
        }
    }

    return 0;
}