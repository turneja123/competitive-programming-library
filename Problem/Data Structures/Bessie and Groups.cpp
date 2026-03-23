//https://contest.joincpi.org/contest?id=Myb-ebc4AHL67vnWMucwU&tab=problem-7wHytfXm6928kosjDXhz2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 1e9 + 7;
const int P = 26;
const int Q = 53;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

ll pw_p[N], pw_q[N];

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
        ll ans = 0;
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


ll solve(vector<int> &a) {
    int n = a.size();
    ll inv = 0;
    BIT bit(n);
    for (int i = 0; i < n; i++) {
        if (a[i] < n - 1) {
            inv += bit.query(a[i] + 1, n - 1);
        }
        bit.upd(a[i], 1);
    }
    vector<int> pref(n);
    for (int i = 0; i < n; i++) {
        pref[a[i]]++;
    }
    for (int i = 1; i < n; i++) {
        pref[i] += pref[i - 1];
    }

    ll ans = inv;
    for (int i = 0; i < n; i++) {
        inv += pref[n - 1] - pref[a[i]] - (a[i] == 0 ? 0 : pref[a[i] - 1]);
        ans = min(ans, inv + i + 1);
    }
    return ans;
}

int main() {
    IOS;
    pw_p[0] = 1, pw_q[0] = 1;
    for (int i = 1; i < N; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<int> sa = a;
        sort(sa.begin(), sa.end());
        ll ans = 1e18;
        for (int d = 1; d <= n; d++) {
            if (n % d == 0) {
                gp_hash_table<long long, pair<int, int>, custom_hash> mp;

                for (int i = 0, p = 0; i < n; i += d) {
                    ll P = 0, Q = 0;
                    for (int j = i; j < i + d; j++)  {
                        P = (P + pw_p[j - i] * (sa[j] + 1)) % M;
                        Q = (Q + pw_q[j - i] * (sa[j] + 1)) % M;
                    }
                    auto it = mp.find(P + (Q << 32));
                    if (it == mp.end()) {
                        mp[P + (Q << 32)] = {p++, 1};
                    } else {
                        it->second.second++;
                    }
                }
                int ok = 1;
                vector<int> v;
                for (int i = 0; i < n; i += d) {
                    ll P = 0, Q = 0;
                    for (int j = i; j < i + d; j++)  {
                        P = (P + pw_p[j - i] * (a[j] + 1)) % M;
                        Q = (Q + pw_q[j - i] * (a[j] + 1)) % M;
                    }
                    auto it = mp.find(P + (Q << 32));
                    if (it == mp.end()) {
                        ok = 0;
                        break;
                    }
                    v.push_back(it->second.first);
                    it->second.second--;
                }
                for (auto [x, y] : mp) {
                    if (y.second != 0) {
                        ok = 0;
                    }
                }
                if (!ok) {
                    continue;
                }
                ans = min(ans, solve(v));
            }
        }
        cout << ans << endl;
    }
    return 0;
}
