//https://codeforces.com/contest/959/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 21;
const long long M = 1e9 + 7;

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

class Basis {
public:
    vector<int> basis;
    int sz;

    Basis() : basis(vector<int>(K, 0)), sz(0) {}

    vector<int> get_basis() {
        return basis;
    }

    int get_sz() {
        return sz;
    }

    void insert_vector(int a) {
        for (int i = K - 1; i >= 0; i--) {
            int c = a & (1 << i);
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

    bool exists(int a) {
        for (int i = K - 1; i >= 0; i--) {
            int c = a & (1 << i);
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
};

Basis pref[N];


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (i != 0) {
            pref[i] = pref[i - 1];
        }
        pref[i].insert_vector(a);
    }
    for (int i = 0; i < q; i++) {
        int j, x;
        cin >> j >> x;
        j--;
        if (!pref[j].exists(x)) {
            cout << 0 << endl;
        } else {
            cout << modPow(2, j + 1 - pref[j].get_sz()) << endl;
        }
    }
    return 0;
}
