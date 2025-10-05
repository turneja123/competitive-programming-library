//https://atcoder.jp/contests/arc194/tasks/arc194_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const long long INF = 1e18;

int a[N];
int b[N];
long long c[N];
vector<pair<int, int>> c01, c10, c11;

int pos01[N], pos10[N];

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

BIT bitct(N), bitsum(N);
ll ans = 1e18, cur = 0, s = 0;

void add(int j, int x) {
    bitsum.upd(j + 1, x);
    cur += s + bitsum.query(1, j + 1);
    cur += (ll)x * bitct.query(j + 1, N);
    bitct.upd(j + 1, 1);
}

int main() {
    IOS;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++) {
        if (a[i] == 0 && b[i] == 1) {
            c01.push_back({c[i], -1});
        } else if (a[i] == 1 && b[i] == 0) {
            s += c[i];
            c10.push_back({c[i], -1});
        } else if (a[i] == 1 && b[i] == 1) {
            s += c[i];
            c01.push_back({c[i], i});
            c10.push_back({c[i], i});
            c11.push_back({c[i], i});
        }
    }
    sort(c01.begin(), c01.end());
    sort(c10.begin(), c10.end(), greater<pair<int, int>>());
    sort(c11.begin(), c11.end(), greater<pair<int, int>>());


    ll sum = s;
    for (int i = 0; i < c10.size(); i++) {
        if (c10[i].second == -1) {
            sum -= c10[i].first;
            cur += sum;
            bitct.upd(1 + i, 1);
            bitsum.upd(1 + i, -c10[i].first);
        } else {
            pos10[c10[i].second] = i;
        }
    }
    for (int i = 0; i < c01.size(); i++) {
        if (c01[i].second == -1) {
            sum += c01[i].first;
            cur += sum;
            bitct.upd(1 + i + c10.size(), 1);
            bitsum.upd(1 + i + c10.size(), c01[i].first);
        } else {
            pos01[c01[i].second] = i + c10.size();
        }
    }
    ans = min(ans, cur);
    for (auto [x, j] : c11) {
        int l = pos10[j], r = pos01[j];
        add(l, -x);
        add(r, x);
        ans = min(ans, cur);
    }
    cout << ans;
    return 0;
}
