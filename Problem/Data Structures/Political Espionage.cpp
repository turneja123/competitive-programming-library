//https://dmoj.ca/problem/utso24p4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int priority[N];
int lf[N], rt[N];
long long ans[N];

void calc(int l, int r, int d) {
    if (l > r) {
        return;
    }
    if (l == r) {
        priority[l] = d;
        return;
    }
    int mid = (l + r) / 2;
    priority[mid] = d;
    lf[mid] = l, rt[mid] = r;
    calc(l, mid - 1, d + 1);
    calc(mid + 1, r, d + 1);
    return;
}

struct BIT {
    int n;
    vector<long long> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, long long val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    void upd(int l, int r, long long val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    long long query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    long long query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    IOS;
    int n;
    cin >> n;
    calc(0, n - 1, 0);
    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < n; i++) {
        pq.push(make_pair(priority[i], i));
    }
    BIT t = BIT(n);
    while (pq.size()) {
        int i = pq.top().second;
        pq.pop();
        ans[i] = t.query(lf[i] + 1, rt[i] + 1) + 1;
        t.upd(i + 1, ans[i]);
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;

}
