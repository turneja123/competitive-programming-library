//https://atcoder.jp/contests/agc045/tasks/agc045_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 62;
const int N = 205;

long long a[N];
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

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        string s;
        cin >> s;
        int ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '0') {
                insert_vector(a[i]);
            } else if (!exists(a[i])) {
                ans = 1;
            }
        }
        cout << ans << endl;
        for (int i = 0; i < K; i++) {
            basis[i] = 0;
        }
    }

    return 0;
}
