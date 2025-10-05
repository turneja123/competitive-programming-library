//https://atcoder.jp/contests/arc197/tasks/arc197_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e6;

struct BIT {
    int n;
    vector<int> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    BIT(int _n, vector<int> &a) {
        n = _n;
        t.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) {
                t[j] += t[i];
            }
        }
    }
    void upd(int i, int val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
    int lb(int x) {
        if (x <= 0) {
            return 1;
        }
        int j = 0, s = 0, p = 1;
        while ((p << 1) <= n) {
            p <<= 1;
        }
        for (int k = p; k; k >>= 1) {
            if (j + k <= n && s + t[j + k] < x) {
                s += t[j + k];
                j = j + k;
            }
        }
        return j + 1;
    }
};

bool is_prime[N];

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
    vector<int> t(N - 1, 1), r(N, 0);
    BIT bit(N - 1, t);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        if (a < N && !r[a]) {
            for (int j = a; j < N; j += a) {
                if (t[j]) {
                    t[j] = 0;
                    bit.upd(j, -1);
                }
            }
            r[a] = 1;
        }
        cout << bit.lb(b) << endl;
    }
    return 0;
}
