//https://dmoj.ca/problem/dmopc21c5p5hard
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 15;

bool is_prime[N];
int dp[K][1 << K];
int prv[K][1 << K];

int g;

bool good(int s) {
    return is_prime[g + 2 * s];
}

vector<int> solve(int t) {
    vector<int> path;
    if (good(t - 1) && good(t)) {
        for (int i = 0; i < t; i++) {
            path.push_back(i);
            path.push_back(-(t - i));
        }
        return path;
    }
    for (int k = 1; k < t; k++) {
        if (!good(k + t - 1) || (k + 1 < t && !good(k + t))) {
            continue;
        }
        vector<int> sub = solve(k);
        for (int i = 0; i + 1 < sub.size(); i++) {
            int u = max(sub[i], sub[i + 1]), v = -min(sub[i], sub[i + 1]) - 1;
            if (!good(u + k) || !good(v + k)) {
                continue;
            }
            vector<int> V;
            for (int j = k; j < t; j++) {
                V.push_back(j);
                V.push_back(-(k + t - j));
            }
            if (sub[i] >= 0) {
                reverse(V.begin(), V.end());
            }
            path.insert(path.end(), sub.begin(), sub.begin() + i + 1);
            path.insert(path.end(), V.begin(), V.end());
            path.insert(path.end(), sub.begin() + i + 1, sub.end());
            return path;
        }
    }
    return path;
}

void add(vector<int> &p, vector<int> &path, int x, int y) {
    for (int z : path) {
        if (z >= 0) {
            p.push_back(x - 2 * z);
        } else {
            p.push_back(y - 2 * z - 2);
        }
    }
    return;
}

int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    int n;
    cin >> n;
    vector<int> p;
    if (n < K) {
        for (int mask = 1; mask < 1 << n; mask++) {
            for (int j = 0; j < n; j++) {
                dp[j][mask] = -1;
            }
        }
        for (int j = 0; j < n; j++) {
            dp[j][1 << j] = 0;
        }
        for (int mask = 1; mask < 1 << n; mask++) {
            for (int j = 0; j < n; j++) {
                if (dp[j][mask] == -1) {
                    continue;
                }
                for (int k = 0; k < n; k++) {
                    int c = mask & (1 << k);
                    if (c) {
                        continue;
                    }
                    int d = dp[j][mask] + (is_prime[abs(j - k)] ? abs(j - k) : 0);
                    if (d > dp[k][mask | (1 << k)]) {
                        dp[k][mask | (1 << k)] = d;
                        prv[k][mask | (1 << k)] = j;
                    }
                }
            }
        }
        int mask = (1 << n) - 1, j = 0;
        for (int k = 0; k < n; k++) {
            if (dp[k][mask] > dp[j][mask]) {
                j = k;
            }
        }
        while (mask != (1 << j)) {
            p.push_back(j + 1);
            int k = prv[j][mask];
            mask ^= 1 << j;
            j = k;
        }
        p.push_back(j + 1);
    } else if (n % 2 == 0) {
        int m = n / 2;
        g = 1;
        vector<int> path = solve((m + 1) / 2);
        add(p, path, m, m + 1);
        g = 3;
        path = solve(m / 2);
        add(p, path, m - 1, m + 2);
    } else {
        int m = n / 2;
        if (m % 2 == 0) {
            g = 3;
            vector<int> path = solve(m / 2);
            p.push_back(m + 1);
            add(p, path, m - 1, m + 2);
            add(p, path, m, m + 3);
        } else {
            g = 1;
            vector<int> path = solve((m + 1) / 2);
            add(p, path, m, m + 1);
            p.pop_back();
            add(p, path, m + 1, m + 2);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << p[i];
        if (i != n - 1) {
            cout << " ";
        }
    }
    cout << endl;
    return 0;
}
