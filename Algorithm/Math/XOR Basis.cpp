//https://www.spoj.com/problems/XMAX/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 62;

long long basis[K];

void insert_vector(long long a) {
    for (int i = K - 1; i >= 0; i--) {
        long long c = a & (1ll << i);
        if (!c) {
            continue;
        }
        if (!basis[i]) {
            basis[i] = a;
            return;
        }
        a ^= basis[i];
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        insert_vector(a);
    }
    long long ans = 0;
    for (int i = K - 1; i >= 0; i--) {
        long long c = ans & (1ll << i);
        if (!c) {
            ans ^= basis[i];
        }
    }
    cout << ans;

    return 0;
}
