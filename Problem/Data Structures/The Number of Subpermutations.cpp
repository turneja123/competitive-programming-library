//https://codeforces.com/problemset/problem/1175/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int a[N];
long long h[N];
long long perm[N];
long long pref[N];

vector<int> pos;
mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

long long gen() {
    long long h = generator() + ((long long)generator() << 30);
    return h;
}

long long calc(int l, int r) {
    if (l < 0) {
        return -1;
    }
    long long x = pref[r];
    if (l != 0) {
        x ^= pref[l - 1];
    }
    return x;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 1) {
            pos.push_back(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        h[i] = gen();
        perm[i] = perm[i - 1] ^ h[i];
    }
    pref[0] = h[a[0]];
    for (int i = 1; i < n; i++) {
        pref[i] = pref[i - 1] ^ h[a[i]];
    }
    long long ans = 0;
    for (int k = 0; k < pos.size(); k++) {
        int j = pos[k];
        int l = ((k == 0) ? -1 : pos[k - 1]);
        int r = ((k == pos.size() - 1) ? n : pos[k + 1]);
        ans++;
        int mx = 1;
        for (int rt = j + 1; rt < r; rt++) {
            mx = max(mx, a[rt]);
            if (calc(rt - mx + 1, rt) == perm[mx]) {
                ans++;
            }
        }
        mx = 1;
        for (int lf = j - 1; lf > l; lf--) {
            mx = max(mx, a[lf]);
            if (calc(lf, lf + mx - 1) == perm[mx]) {
                ans++;
            }
        }
    }
    cout << ans;

    return 0;
}
