//https://codeforces.com/contest/1336/problem/E1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 36;
const long long M = 998244353;

long long ans[K];

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}


void print(int a) {
    for (int i = K - 1; i >= 0; i--) {
        long long c = a & (1ll << i);
        if (!c) {
            cout << 0;
        } else {
            cout << 1;
        }
    }
    cout << endl;
}

class Basis {
public:
    vector<long long> basis;
    int sz;

    Basis() : basis(vector<long long>(K, 0)), sz(0) {}

    vector<long long> get_basis() {
        return basis;
    }

    int get_sz() {
        return sz;
    }

    void insert_vector(long long a) {
        for (int i = K - 1; i >= 0; i--) {
            long long c = a & (1ll << i);
            if (!c) {
                continue;
            }
            if (!basis[i]) {
                basis[i] = a;
                sz++;
                return;
            }
            a ^= basis[i];
        }
    }

    bool exists(long long a) {
        for (int i = K - 1; i >= 0; i--) {
            long long c = a & (1ll << i);
            if (!c) {
                continue;
            }
            if (!basis[i]) {
                return false;
            }
            a ^= basis[i];
        }
        return true;
    }

    void gauss() {
        for (int i = K - 1; i >= 0; i--) {
            if (basis[i]) {
                for (int j = i + 1; j < K; j++) {
                    long long c = basis[j] & (1ll << i);
                    if (c) {
                        basis[j] ^= basis[i];
                    }
                }
            }
        }
    }

    void calc() {
        vector<long long> masks;
        for (int i = 0; i < K; i++) {
            if (basis[i]) {
                masks.push_back(basis[i]);
            }
        }
        int n = masks.size();
        for (int i = 0; i < 1 << n; i++) {
            long long cur = 0;
            for (int j = 0; j < n; j++) {
                long long c = i & (1ll << j);
                if (c) {
                    cur ^= masks[j];
                }
            }
            ans[__builtin_popcountll(cur)]++;
        }
    }

    void calc_complement() {
        map<long long, long long> dp[K];
        dp[0][0] = 1;
        for (int i = 0; i < K; i++) {
            if (basis[i]) {
                long long x = basis[i] - (1ll << i);
                for (int j = K - 2; j >= 0; j--) {
                    for (auto it = dp[j].begin(); it != dp[j].end(); ++it) {
                        dp[j + 1][x ^ it->first] += it->second;
                    }
                }
            }
        }
        for (int j = K - 1; j >= 0; j--) {
            for (auto it = dp[j].begin(); it != dp[j].end(); ++it) {
                ans[j + __builtin_popcountll(it->first)] += it->second;
            }
        }
        return;
    }

    void printb() {
        for (int i = 0; i < K; i++) {
            if (basis[i]) {
                print(basis[i]);
            }
        }
    }
};

Basis b;


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        b.insert_vector(a);
    }
    b.gauss();

    if (b.get_sz() <= 20) {
        b.calc();
    } else {
        b.calc_complement();
    }

    for (int i = 0; i <= m; i++) {
        cout << ans[i] % M * modPow(2, n - b.get_sz()) % M << " ";
    }
    //b.printb();


    return 0;
}
