//https://codeforces.com/contest/1101/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 31;

int sz = 0;
int basis[K];

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

int main() {
    IOS;
    int n;
    cin >> n;
    int pref = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        pref ^= a;
        insert_vector(a);
    }
    if (pref == 0) {
        cout << -1;
    } else {
        cout << sz;
    }

    return 0;
}
