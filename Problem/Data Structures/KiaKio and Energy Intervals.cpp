//https://codeforces.com/contest/2268/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 18;

int pref[N];

int table_mx[K][N];
int mx[K][N];
int a[N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table_mx[0][i] = a[i];
        mx[0][i] = i;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table_mx[k - 1][i] >= table_mx[k - 1][i + (1 << (k - 1))]) {
                table_mx[k][i] = table_mx[k - 1][i];
                mx[k][i] = mx[k - 1][i];
            } else {
                table_mx[k][i] = table_mx[k - 1][i + (1 << (k - 1))];
                mx[k][i] = mx[k - 1][i + (1 << (k - 1))];
            }
        }
    }
    return;
}

int query(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    int b;
    if (table_mx[k][l] >= table_mx[k][r - (1 << k) + 1]) {
        b = mx[k][l];
    } else {
        b = mx[k][r - (1 << k) + 1];
    }
    return b;
}

int seen[1 << K];
vector<int> pos[1 << K];
int ok = 0;

void calc(int l, int r, int cur) {
    if (l >= r || ok) {
        return;
    }
    int mid = query(l, r);

    if ((a[mid] & cur) == cur) {
        if (mid - l + 1 <= r - mid + 1) {
            for (int i = l; i <= mid; i++) {
                if (seen[pref[i - 1]]) {
                    continue;
                }
                seen[pref[i - 1]] = 1;
                int need = pref[i - 1] ^ cur;
                if (pos[need].size()) {
                    auto it = lower_bound(pos[need].begin(), pos[need].end(), (i == mid ? mid + 1 : mid));
                    if (it != pos[need].end() && *it <= r) {
                        ok = 1;
                        break;
                    }
                }
            }
            for (int i = l; i <= mid; i++) {
                seen[pref[i - 1]] = 0;
            }
        } else {
            for (int i = mid; i <= r; i++) {
                if (seen[pref[i]]) {
                    continue;
                }
                if (i != mid) {
                    seen[pref[i]] = 1;
                }
                int need = pref[i] ^ cur;
                if (pos[need].size()) {
                    auto it = lower_bound(pos[need].begin(), pos[need].end(), mid);
                    if (it != pos[need].begin()) {
                        it--;
                        if (i == mid && *it == mid - 1) {
                            if (it == pos[need].begin()) {
                                continue;
                            }
                            it--;
                        }
                        if (*it >= l - 1) {
                            ok = 1;
                            break;
                        }
                    }
                }
            }
            for (int i = mid; i <= r; i++) {
                seen[pref[i]] = 0;
            }
        }
    }
    calc(l, mid - 1, cur);
    calc(mid + 1, r, cur);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        build(n);
        int ans = 0;
        for (int k = 17; k >= 0; k--) {
            int cur = ans | (1 << k);
            pos[0].push_back(0);
            for (int i = 1; i <= n; i++) {
                pref[i] = pref[i - 1] ^ (a[i] & cur);
                pos[pref[i]].push_back(i);
            }
            ok = 0;
            calc(1, n, cur);
            pos[0].clear();
            for (int i = 1; i <= n; i++) {
                pos[pref[i]].clear();
            }
            if (ok) {
                ans = cur;
            }
        }
        cout << ans << endl;

    }


    return 0;
}
