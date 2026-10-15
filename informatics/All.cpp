//1.

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> tags(n);
    for (int i = 0; i < n; i++)
        cin >> tags[i];

    int count = 0;

    for (int i = 0; i + 1 < n; i += 2) {
        if (abs(tags[i] - tags[i + 1]) == 1)
            count++;
    }

    cout << count << '\n';
    return 0;
}

//2.
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> A(n), B(n);

    for (auto &x : A) cin >> x;
    for (auto &x : B) cin >> x;

    long long total = 0;

    for (int i = 0; i < n; i++) {
        long long common = (A[i] / gcd(A[i], B[i])) * B[i];
        total += A[i] * B[i] - common;
    }

    cout << total << '\n';
    return 0;
}
//3.

#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long sum = 0;

    for (int i = 0; i < n; i++) {
        long long contribution;
        cin >> contribution;

        sum += contribution;
        cout << sum;

        if (i < n - 1) cout << ' ';
    }

    cout << '\n';
    return 0;
}

//4.
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> weights(n);
    int total = 0;

    for (int &w : weights) {
        cin >> w;
        total += w;
    }

    int best = total;
    int subsets = 1 << n;

    for (int mask = 0; mask < subsets; mask++) {
        int first = 0;

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i))
                first += weights[i];
        }

        int second = total - first;
        best = min(best, abs(first - second));
    }

    cout << best << '\n';
    return 0;
}

//5.

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> prices(n);
    for (int &p : prices) cin >> p;

    long long profit = 0;

    for (int i = 1; i < n; i++) {
        if (prices[i] > prices[i - 1])
            profit += prices[i] - prices[i - 1];
    }

    cout << profit << '\n';
    return 0;
}

//6.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Patient {
    int id, arrival, departure;
};

bool comparePatients(const Patient& a, const Patient& b) {
    if (a.arrival != b.arrival)
        return a.arrival < b.arrival;
    return a.id < b.id;
}

int main() {
    int n;
    cin >> n;

    vector<Patient> patients(n);

    for (int i = 0; i < n; i++) {
        patients[i].id = i;
        cin >> patients[i].arrival;
    }

    for (int i = 0; i < n; i++)
        cin >> patients[i].departure;

    sort(patients.begin(), patients.end(), comparePatients);

    vector<int> bedFreeDay;
    vector<int> assigned(n);

    for (const auto& p : patients) {
        int bed = -1;

        for (int b = 0; b < (int)bedFreeDay.size(); b++) {
            if (bedFreeDay[b] < p.arrival) {
                bed = b;
                break;
            }
        }

        if (bed == -1) {
            bed = bedFreeDay.size();
            bedFreeDay.push_back(p.departure);
        } else {
            bedFreeDay[bed] = p.departure;
        }

        assigned[p.id] = bed + 1;
    }

    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ' ';
        cout << assigned[i];
    }

    cout << '\n';
    return 0;
}