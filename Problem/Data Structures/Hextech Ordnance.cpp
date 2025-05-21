//https://codesprintla25.kattis.com/contests/codesprintla25open/problems/hextechordnance
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int K = 21;

int mn[K][N];
int mx[K][N];

int last[N];
int a[N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        mn[0][i] = a[i - 1];
        mx[0][i] = a[i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            mn[k][i] = min(mn[k - 1][i], mn[k - 1][i + (1 << (k - 1))]);
            mx[k][i] = max(mx[k - 1][i], mx[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query_mn(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return min(mn[k][l], mn[k][r - (1 << k) + 1]);
}

int query_mx(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return max(mx[k][l], mx[k][r - (1 << k) + 1]);
}


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(n);
    long long ans = 0;
    priority_queue<tuple<int, int, int, int>> pq;
    for (int i = 0; i < n; i++) {
        int l = i, r = n - 1, spl = n, val = n + 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int d = query_mx(i + 1, mid + 1) - query_mn(i + 1, mid + 1);
            if (d != 0) {
                spl = mid;
                val = d;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        ans += spl - 1 - i;
        last[i] = spl - 1;
        if (ans >= n) {
            cout << "stable";
            return 0;
        }
        if (spl != n) {
            pq.push(make_tuple(-val, spl, val, i));
        }
    }
    for (int i = 1; i <= n; i++) {
        while (pq.size() && ans < n && -get<0>(pq.top()) <= i) {
            auto [D, SPL, VAL, I] = pq.top();
            pq.pop();
            D = -D;
            int l = SPL, r = n - 1, spl = n, val = n + 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                int d = query_mx(I + 1, mid + 1) - query_mn(I + 1, mid + 1);
                if (d != D) {
                    spl = mid;
                    val = d;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            ans += spl - 1 - last[I];
            last[I] = spl - 1;
            if (ans >= n) {
                cout << "stable";
                return 0;
            }
            if (spl != n) {
                pq.push(make_tuple(-val, spl, val, I));
            }
        }
        if (ans < i) {
            cout << "unstable";
            return 0;
        }
    }
    cout << "stable";
    return 0;
}
