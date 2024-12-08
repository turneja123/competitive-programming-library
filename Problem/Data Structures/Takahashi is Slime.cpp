//https://atcoder.jp/contests/arc189/tasks/arc189_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int K = 20;

int a[N];
long long table[2][K][N];
long long pref[N];
long long suf[N];

long long tot[N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][0][i] = pref[i - 1];
        table[1][0][i] = suf[i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[0][k][i] = max(table[0][k - 1][i], table[0][k - 1][i + (1 << (k - 1))]);
            table[1][k][i] = max(table[1][k - 1][i], table[1][k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

long long query(int l, int r, int n) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    return max(table[n][k][l], table[n][k][r - (1 << k) + 1]);
}


int move_right(int i, long long x, int n) {
    int l = i + 1, r = n - 1, ans = i;
    while (l <= r) {
        int mid = (l + r) / 2;
        long long val = query(i + 1, mid, 0) + (i == 0 ? 0 : tot[i - 1]) - (x - a[i]);
        if (val < 0) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int move_left(int i, long long x, int n) {
    int l = 0, r = i - 1, ans = i;
    while (l <= r) {
        int mid = (l + r) / 2;
        long long val = query(mid, i - 1, 1) + (tot[n - 1] - tot[i]) - (x - a[i]);
        if (val < 0) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}


int main() {
    IOS;
    int n;
    cin >> n;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i] = a[i] - sum;
        sum += a[i];
        tot[i] = sum;
    }
    sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = a[i] - sum;
        sum += a[i];
    }

    build(n);
    for (int i = 0; i < n; i++) {
        int lq = i, rq = i;
        long long sum = a[i];
        while (1) {
            int nw_rq = move_right(rq, sum, n);
            sum = tot[nw_rq] - (lq == 0 ? 0 : tot[lq - 1]);
            int nw_lq = move_left(lq, sum, n);
            sum = tot[nw_rq] - (nw_lq == 0 ? 0 : tot[nw_lq - 1]);
            if (nw_rq == rq && nw_lq == lq) {
                break;
            }
            rq = nw_rq, lq = nw_lq;
        }
        cout << sum << " ";
    }

    return 0;
}
