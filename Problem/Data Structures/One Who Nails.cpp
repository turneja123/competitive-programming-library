//https://tlx.toki.id/contests/troc-44/problems/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int B = 2000;

int a[N];
ll pref[N];
ll ans[2 * N];

vector<tuple<int, int, int>> small[B];
vector<tuple<int, int, int, int, int>> ask[N];

struct BIT {
    int n;
    vector<int> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, int val) {
        i++;
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
        l++, r++;
        return query(r) - query(l - 1);
    }
};

int main() {
    IOS;
    int n, q;
    cin >> n >> q;


    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int x, int y) {return a[x] < a[y];});

    for (int i = 0; i < q; i++) {
        int l, r, s;
        cin >> l >> r >> s;
        l--, r--;
        if (s < B) {
            small[s].push_back({l, r, i});
        } else {
            int ct = 0;
            auto add = [&](int j, int f) -> void {
                if (j < 0) {
                    return;
                }
                j = min(j, N - 1);
                ask[j].push_back({l, r, i, f, ct});
            };

            int lf = 0, rt = s - 1;
            while (lf < N) {
                add(lf - 1, -1);
                add(rt, 1);
                lf = rt + 1;
                rt += s;
                ct++;
            }
        }
    }
    for (int j = 1; j < B; j++) {
        for (int i = 0; i < n; i++) {
            pref[i] = (i == 0 ? 0 : pref[i - 1]) + a[i] / j;
        }
        for (auto [l, r, ind] : small[j]) {
            ans[ind] = pref[r] - (l == 0 ? 0 : pref[l - 1]);
        }
    }
    BIT bit(n);
    int ptr = 0;
    for (int j = 0; j < N; j++) {
        while (ptr < n && a[ord[ptr]] <= j) {
            bit.upd(ord[ptr], 1);
            ptr++;
        }
        for (auto [l, r, ind, f, ct] : ask[j]) {
            ans[ind] += bit.query(l, r) * f * ct;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }


    return 0;
}
