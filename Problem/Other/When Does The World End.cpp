//https://www.spoj.com/problems/PONY10/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = (ll)4e18;

ll p10[19];
string s;
int m;
int p[25];
int to[25][10], addv[25][10];
ll cnt[25][25], sumv[25][25];
string b[25], c[25];
vector<ll> sp;

ll pos(ll x) {
    if (!x) {
        return 0;
    }
    string t = to_string(x);
    int n = t.size();
    ll ans = 1;
    for (int i = 1; i < n; i++) {
        ans += 9 * p10[i - 1] * i;
    }
    ans += (x - p10[n - 1]) * n;
    return ans;
}

ll ca(ll x) {
    if (x < 0) {
        return 0;
    }
    ll ans = (s == "0");
    if (!x) {
        return ans;
    }
    string t = to_string(x);
    int n = t.size();
    for (int l = 1; l < n; l++) {
        for (int d = 1; d <= 9; d++) {
            int ns = to[0][d];
            int z = addv[0][d];
            __int128 cur = (__int128)z * cnt[l - 1][ns] + sumv[l - 1][ns];
            ans = min((__int128)INF, (__int128)ans + cur);
        }
    }
    int st = 0;
    ll cur = 0;
    for (int i = 0; i < n; i++) {
        int lim = t[i] - '0';
        for (int d = (i ? 0 : 1); d < lim; d++) {
            int ns = to[st][d];
            int z = addv[st][d];
            int rem = n - i - 1;
            __int128 val = (__int128)(cur + z) * cnt[rem][ns] + sumv[rem][ns];
            ans = min((__int128)INF, (__int128)ans + val);
        }
        cur = min((__int128)INF, (__int128)cur + addv[st][lim]);
        st = to[st][lim];
    }
    ans = min((__int128)INF, (__int128)ans + cur);
    return ans;
}

ll q(int n, int a[], string &lim) {
    int suf[25];
    suf[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i + 1] + (a[i] == -1);
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int cur = lim[i] - '0';
        if (a[i] != -1) {
            if (a[i] < cur) {
                ans = min((__int128)INF, (__int128)ans + p10[suf[i + 1]]);
            }
            if (a[i] != cur) {
                return ans;
            }
        }
        else {
            int l = (i == 0);
            if (cur > l) {
                __int128 val = (__int128)(cur - l) * p10[suf[i + 1]];
                ans = min((__int128)INF, (__int128)ans + val);
            }
            if (cur < l) {
                return ans;
            }
        }
    }
    ans = min((__int128)INF, (__int128)ans + 1);
    return ans;
}

ll cb(ll x) {
    if (x < 0) {
        return 0;
    }
    ll y = x + 1;
    string lim = to_string(y);
    int n = lim.size();
    ll ans = 0;
    for (int i = 1; i < m; i++) {
        int a = i, d = m - i;
        for (int l = 1; l <= n; l++) {
            if (l <= a || l <= d) {
                continue;
            }
            int z[25];
            for (int j = 0; j < l; j++) {
                z[j] = -1;
            }
            bool ok = 1;
            for (int j = 0; j < d; j++) {
                int v = b[i][j] - '0';
                if (z[j] != -1 && z[j] != v) {
                    ok = 0;
                }
                z[j] = v;
            }
            for (int j = 0; j < a; j++) {
                int p = l - a + j;
                int v = c[i][j] - '0';
                if (z[p] != -1 && z[p] != v) {
                    ok = 0;
                }
                z[p] = v;
            }
            if (!ok || z[0] == 0) {
                continue;
            }
            ll cur = 1;
            if (l < n) {
                int free = 0;
                for (int j = 0; j < l; j++) {
                    free += (z[j] == -1);
                }
                cur = p10[free];
            }
            else {
                cur = q(l, z, lim);
            }
            if (a == l - 1) {
                bool good = 1;
                if (z[0] != 1) {
                    good = 0;
                }
                for (int j = 1; j < l; j++) {
                    if (z[j] != -1 && z[j] != 0) {
                        good = 0;
                    }
                }
                if (good) {
                    cur--;
                }
            }
            ans = min((__int128)INF, (__int128)ans + cur);
        }
    }
    return ans;
}

ll cc(ll x) {
    return upper_bound(sp.begin(), sp.end(), x) - sp.begin();
}

ll cg(ll x) {
    if (x < 0) {
        return 0;
    }
    ll ans = ca(x);
    ans = min((__int128)INF, (__int128)ans + cb(x));
    ans = min((__int128)INF, (__int128)ans + cc(x));
    return ans;
}

int main() {
    IOS;

    p10[0] = 1;
    for (int i = 1; i < 19; i++) {
        p10[i] = p10[i - 1] * 10;
    }

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        ll k;
        cin >> k >> s;
        m = s.size();

        for (int i = 0; i < m; i++) {
            p[i] = 0;
        }
        for (int i = 1; i < m; i++) {
            int j = p[i - 1];
            while (j && s[i] != s[j]) {
                j = p[j - 1];
            }
            if (s[i] == s[j]) {
                j++;
            }
            p[i] = j;
        }
        for (int i = 0; i < m; i++) {
            for (int d = 0; d <= 9; d++) {
                int j = i;
                char curch = '0' + d;
                while (j && s[j] != curch) {
                    j = p[j - 1];
                }
                if (s[j] == curch) {
                    j++;
                }
                if (j == m) {
                    addv[i][d] = 1;
                    j = p[m - 1];
                }
                else {
                    addv[i][d] = 0;
                }
                to[i][d] = j;
            }
        }

        for (int i = 0; i <= m; i++) {
            cnt[0][i] = 1;
            sumv[0][i] = 0;
        }
        for (int l = 1; l < 19; l++) {
            for (int i = 0; i < m; i++) {
                cnt[l][i] = 0;
                sumv[l][i] = 0;
                for (int d = 0; d <= 9; d++) {
                    int j = to[i][d];
                    cnt[l][i] = min((__int128)INF, (__int128)cnt[l][i] + cnt[l - 1][j]);
                    __int128 cur = (__int128)addv[i][d] * cnt[l - 1][j] + sumv[l - 1][j];
                    sumv[l][i] = min((__int128)INF, (__int128)sumv[l][i] + cur);
                }
            }
        }

        for (int i = 1; i < m; i++) {
            b[i] = s.substr(i);
            c[i] = s.substr(0, i);
            int j = i - 1;
            while (j >= 0 && c[i][j] == '9') {
                c[i][j] = '0';
                j--;
            }
            if (j >= 0) {
                c[i][j]++;
            }
        }

        sp.clear();
        for (int l = 0; l < m; l++) {
            ll x = 0;
            for (int r = l; r < m; r++) {
                if (r > l && s[l] == '0') {
                    break;
                }
                x = x * 10 + s[r] - '0';
                if (!l && r == m - 1) {
                    continue;
                }
                if (!x && l) {
                    continue;
                }
                string t;
                ll st = x;
                if (l) {
                    string y = to_string(x - 1);
                    if (l >= y.size()) {
                        continue;
                    }
                    t = y.substr(y.size() - l);
                    st = x - 1;
                }
                ll y = x;
                while (t.size() < m) {
                    t += to_string(y);
                    y++;
                }
                bool ok = 1;
                for (int i = 0; i < m; i++) {
                    if (t[i] != s[i]) {
                        ok = 0;
                    }
                }
                if (ok) {
                    sp.push_back(st);
                }
            }
        }
        sort(sp.begin(), sp.end());

        ll l = 0, r = 1;
        while (cg(r) < k) {
            r *= 2;
        }
        while (l < r) {
            ll mid = (l + r) / 2;
            if (cg(mid) >= k) {
                r = mid;
            }
            else {
                l = mid + 1;
            }
        }

        ll x = l;
        ll need = k - cg(x - 1);
        string t;
        ll y = x;
        while (t.size() < to_string(x).size() + m - 1) {
            t += to_string(y);
            y++;
        }
        vector<ll> v;
        for (int i = 0; i < to_string(x).size(); i++) {
            bool ok = 1;
            for (int j = 0; j < m; j++) {
                if (t[i + j] != s[j]) {
                    ok = 0;
                }
            }
            if (ok) {
                v.push_back(pos(x) + i);
            }
        }

        cout << "Case #" << tc << ": " << v[need - 1] << endl;
    }
    return 0;
}
