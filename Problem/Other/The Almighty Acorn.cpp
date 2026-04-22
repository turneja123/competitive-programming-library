//https://dmoj.ca/problem/wac4p4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 10005;
const ll M = 998244353;
const ll H = 1e9 + 7;
const ll B1 = 26;
const ll B2 = 53;

string s;
int n;
ll p1[N], p2[N], h1[N], h2[N];
ll p10[N], pr[N], bef[N];
int nz[N], n9[N], prv9[N], lp9[N];

ll calc(ll *h, ll *p, int l, int r) {
    ll x = (h[r + 1] - h[l] * p[r - l + 1]) % H;
    if (x < 0) {
        x += H;
    }
    return x;
}

bool eq(int l1, int r1, int l2, int r2) {
    if (r1 < l1 && r2 < l2) {
        return 1;
    }
    if (r1 < l1 || r2 < l2) {
        return 0;
    }
    return calc(h1, p1, l1, r1) == calc(h1, p1, l2, r2) && calc(h2, p2, l1, r1) == calc(h2, p2, l2, r2);
}

ll val(int l, int len) {
    ll x = (pr[l + len] - pr[l] * p10[len]) % M;
    if (x < 0) {
        x += M;
    }
    return x;
}

ll pos(int l, int len) {
    ll x = val(l, len) - p10[len - 1];
    if (x < 0) {
        x += M;
    }
    return (bef[len] + x * len + 1) % M;
}

ll poss(string t) {
    ll x = 0;
    for (int i = 0; i < t.size(); i++) {
        x = (x * 10 + t[i] - '0') % M;
    }
    x -= p10[t.size() - 1];
    if (x < 0) {
        x += M;
    }
    return (bef[t.size()] + x * t.size() + 1) % M;
}

bool ckp(int i, int p, int take) {
    if (!take) {
        return 1;
    }
    int m = lp9[i];
    if (m < 0) {
        return nz[p + take] - nz[p] == 0;
    }
    int pre = m;
    if (take <= pre) {
        return eq(0, take - 1, p, p + take - 1);
    }
    if (pre && !eq(0, pre - 1, p, p + pre - 1)) {
        return 0;
    }
    if (s[p + pre] != s[m] + 1) {
        return 0;
    }
    return nz[p + take] - nz[p + pre + 1] == 0;
}

bool cka(int l, int len, int p, int take) {
    if (!take) {
        return 1;
    }
    int r = l + len - 1;
    int m = prv9[r];
    if (m < l) {
        if (s[p] != '1') {
            return 0;
        }
        return nz[p + take] - nz[p + 1] == 0;
    }
    int pre = m - l;
    if (take <= pre) {
        return eq(l, l + take - 1, p, p + take - 1);
    }
    if (pre && !eq(l, m - 1, p, p + pre - 1)) {
        return 0;
    }
    if (s[p + pre] != s[m] + 1) {
        return 0;
    }
    return nz[p + take] - nz[p + pre + 1] == 0;
}

int cmp(int l1, int l2, int len) {
    int l = 0, r = len, ans = 0;
    while (l <= r) {
        int m = (l + r) / 2;
        if (!m || eq(l1, l1 + m - 1, l2, l2 + m - 1)) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    if (ans == len) {
        return 0;
    }
    return s[l1 + ans] < s[l2 + ans] ? -1 : 1;
}

int cmp2(int x, int len, string &t, vector<ll> &a, vector<ll> &b) {
    int l = 0, r = len, ans = 0;
    while (l <= r) {
        int m = (l + r) / 2;
        if (!m || (calc(h1, p1, x, x + m - 1) == calc(a.data(), p1, 0, m - 1) && calc(h2, p2, x, x + m - 1) == calc(b.data(), p2, 0, m - 1))) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    if (ans == len) {
        return 0;
    }
    return s[x + ans] < t[ans] ? -1 : 1;
}

string add1(string t) {
    int i = t.size() - 1;
    while (i >= 0 && t[i] == '9') {
        t[i] = '0';
        i--;
    }
    if (i < 0) {
        return "1" + t;
    }
    t[i]++;
    return t;
}

string bld(int i, int j) {
    string t = s.substr(i);
    int m = lp9[i];
    if (m < 0) {
        t.append(i - j, '0');
        return t;
    }
    if (j < m) {
        t += s.substr(j, m - j);
        j = m;
    }
    if (j == m) {
        t.push_back(s[m] + 1);
        j++;
    }
    t.append(i - j, '0');
    return t;
}

int main() {
    IOS;

    cin >> s;
    n = s.size();

    p1[0] = p2[0] = 1;
    for (int i = 0; i <= n + 1; i++) {
        p1[i + 1] = p1[i] * B1 % H;
        p2[i + 1] = p2[i] * B2 % H;
    }
    for (int i = 0; i < n; i++) {
        h1[i + 1] = (h1[i] * B1 + s[i] - '0' + 1) % H;
        h2[i + 1] = (h2[i] * B2 + s[i] - '0' + 1) % H;
    }

    for (int i = 0; i < n; i++) {
        nz[i + 1] = nz[i] + (s[i] != '0');
        n9[i + 1] = n9[i] + (s[i] != '9');
        prv9[i] = s[i] != '9' ? i : (i ? prv9[i - 1] : -1);
    }
    lp9[0] = -1;
    for (int i = 1; i <= n; i++) {
        lp9[i] = s[i - 1] != '9' ? i - 1 : lp9[i - 1];
    }

    p10[0] = 1;
    for (int i = 1; i <= n + 1; i++) {
        p10[i] = p10[i - 1] * 10 % M;
    }
    for (int i = 0; i < n; i++) {
        pr[i + 1] = (pr[i] * 10 + s[i] - '0') % M;
    }
    bef[1] = 0;
    for (int i = 2; i <= n + 1; i++) {
        bef[i] = (bef[i - 1] + 9ll * p10[i - 2] % M * (i - 1)) % M;
    }

    bool e1 = 0;
    int ed = 0;

    bool a1 = 0;
    int al = 0, ad = 0, ao = 0, ai = 0;

    bool c1 = 0;
    int cl = 0, cd = 0, co = 0, ci = 0, cs = 0;

    for (int d = 1; d <= n; d++) {
        int lim = min(d - 1, n - d);
        for (int i = 0; i <= lim; i++) {
            if (s[i] == '0') {
                continue;
            }
            if (i && !ckp(i, d, i)) {
                continue;
            }
            int p = i + d;
            int l = i;
            int len = d;
            bool ok = 1;
            while (p < n) {
                int len2 = len + (n9[l + len] - n9[l] == 0);
                int take = min(len2, n - p);
                if (!cka(l, len, p, take)) {
                    ok = 0;
                    break;
                }
                if (take < len2) {
                    break;
                }
                l = p;
                len = len2;
                p += len2;
            }
            if (!ok) {
                continue;
            }
            if (!i) {
                if (!e1 || d < ed) {
                    e1 = 1;
                    ed = d;
                }
            } else {
                if (s[i] == '1' && nz[i + d] - nz[i + 1] == 0) {
                    int sl = d - 1;
                    int off = sl - i;
                    if (!c1 || sl < cs || (sl == cs && off < co)) {
                        c1 = 1;
                        cl = i;
                        cd = d;
                        co = off;
                        ci = i;
                        cs = sl;
                    }
                } else {
                    int off = d - i;
                    if (!a1 || d < ad || (d == ad && (cmp(i, al, d) < 0 || (cmp(i, al, d) == 0 && off < ao)))) {
                        a1 = 1;
                        al = i;
                        ad = d;
                        ao = off;
                        ai = i;
                    }
                }
            }
        }
    }

    bool e2 = 0;
    string es;
    if (s[0] == '0') {
        e2 = 1;
        es = "1" + s;
    }

    bool a2 = 0;
    string as;
    vector<ll> ah1, ah2;
    int ao2 = 0, ai2 = 0;

    bool c2 = 0;
    string ct;
    int co2 = 0, ci2 = 0, cs2 = 0;

    for (int i = 1; i < n; i++) {
        if (s[i] == '0') {
            continue;
        }
        int j = 0;
        for (int k = min(i, n - i) - 1; k >= 0; k--) {
            if (ckp(i, n - k, k)) {
                j = k;
                break;
            }
        }
        string x = bld(i, j);
        bool pw = x[0] == '1';
        for (int k = 1; k < x.size(); k++) {
            pw &= x[k] == '0';
        }
        if (pw) {
            int sl = x.size() - 1;
            int off = sl - i;
            if (!c2 || sl < cs2 || (sl == cs2 && off < co2)) {
                c2 = 1;
                ct = x;
                co2 = off;
                ci2 = i;
                cs2 = sl;
            }
        } else {
            int off = x.size() - i;
            if (!a2 || x.size() < as.size() || (x.size() == as.size() && (x < as || (x == as && off < ao2)))) {
                a2 = 1;
                as = x;
                ao2 = off;
                ai2 = i;
                ah1.assign(as.size() + 1, 0);
                ah2.assign(as.size() + 1, 0);
                for (int k = 0; k < as.size(); k++) {
                    ah1[k + 1] = (ah1[k] * B1 + as[k] - '0' + 1) % H;
                    ah2[k + 1] = (ah2[k] * B2 + as[k] - '0' + 1) % H;
                }
            }
        }
    }

    bool a = 0, ax = 0;
    int wl = 0, wd = 0, wo = 0, wi = 0;
    string ws;

    if (a1 && !a2) {
        a = 1;
        ax = 0;
        wl = al;
        wd = ad;
        wo = ao;
        wi = ai;
    } else if (!a1 && a2) {
        a = 1;
        ax = 1;
        ws = as;
        wo = ao2;
        wi = ai2;
    } else if (a1 && a2) {
        if (ad < as.size()) {
            a = 1;
            ax = 0;
            wl = al;
            wd = ad;
            wo = ao;
            wi = ai;
        } else if (ad > as.size()) {
            a = 1;
            ax = 1;
            ws = as;
            wo = ao2;
            wi = ai2;
        } else {
            int t = cmp2(al, ad, as, ah1, ah2);
            if (t < 0 || (t == 0 && ao < ao2)) {
                a = 1;
                ax = 0;
                wl = al;
                wd = ad;
                wo = ao;
                wi = ai;
            } else {
                a = 1;
                ax = 1;
                ws = as;
                wo = ao2;
                wi = ai2;
            }
        }
    }

    bool c = 0, cx = 0;
    int xl = 0, xd = 0, xo = 0, xi = 0, xs = 0;
    string xt;

    if (c1 && !c2) {
        c = 1;
        cx = 0;
        xl = cl;
        xd = cd;
        xo = co;
        xi = ci;
        xs = cs;
    } else if (!c1 && c2) {
        c = 1;
        cx = 1;
        xt = ct;
        xo = co2;
        xi = ci2;
        xs = cs2;
    } else if (c1 && c2) {
        if (cs < cs2 || (cs == cs2 && co <= co2)) {
            c = 1;
            cx = 0;
            xl = cl;
            xd = cd;
            xo = co;
            xi = ci;
            xs = cs;
        } else {
            c = 1;
            cx = 1;
            xt = ct;
            xo = co2;
            xi = ci2;
            xs = cs2;
        }
    }

    bool e = e1 || e2;
    int el = e1 ? ed : (e2 ? n + 1 : (int)1e9);
    int eo = e1 ? 0 : 1;
    int alen = a ? (ax ? ws.size() : wd) : (int)1e9;
    int clen = c ? xs : (int)1e9;
    int mn = min(el, min(alen, clen));

    int tp;
    if (e && el == mn) {
        if (a && alen == mn) {
            string x = ax ? ws : s.substr(wl, wd);
            string y = e1 ? s.substr(0, ed) : es;
            y = add1(y);
            if (y.size() > x.size() || (y.size() == x.size() && (x < y || (x == y && wo < eo)))) {
                tp = 1;
            } else {
                tp = 0;
            }
        } else {
            tp = 0;
        }
    } else if (a && alen == mn) {
        tp = 1;
    } else {
        tp = 2;
    }

    ll ans = 0;
    if (tp == 0) {
        if (e1) {
            ans = pos(0, ed);
        } else {
            ans = poss(es) + 1;
            if (ans >= M) {
                ans -= M;
            }
        }
    } else if (tp == 1) {
        if (ax) {
            ans = poss(ws) - wi;
        } else {
            ans = pos(wl, wd) - wi;
        }
        if (ans < 0) {
            ans += M;
        }
    } else {
        if (cx) {
            ans = poss(xt) - xi;
        } else {
            ans = pos(xl, xd) - xi;
        }
        if (ans < 0) {
            ans += M;
        }
    }

    cout << ans << endl;

    return 0;
}
