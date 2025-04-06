//https://www.spoj.com/problems/MINSEQ/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;

long long pw_p[N], pw_q[N];
long long inv_p[N], inv_q[N];
pair<long long, long long> pw[N];

pair<long long, long long> mul(pair<long long, long long> a, pair<long long, long long> b) {
    return make_pair(a.first * b.first % M, a.second * b.second % M);
}

pair<long long, long long> sub(pair<long long, long long> a, pair<long long, long long> b) {
    return make_pair((a.first - b.first + M) % M, (a.second - b.second + M) % M);
}

pair<long long, long long> add(pair<long long, long long> a, pair<long long, long long> b) {
    return make_pair((a.first + b.first + M) % M, (a.second + b.second + M) % M);
}

pair<long long, long long> get_pref(int l, int r, int n, vector<pair<long long, long long>> &pref) {
    pair<long long, long long> ans = pref[r];
    if (l != 0) {
        ans.first = (ans.first - pref[l - 1].first + M) * inv_p[l] % M;
        ans.second = (ans.second - pref[l - 1].second + M) * inv_q[l] % M;
    }
    return ans;
}


pair<long long, long long> calc_hash(int x, int r, string &a, string &b, vector<pair<long long, long long>> &prefa, vector<pair<long long, long long>> &prefb) {
    int n = a.size(), m = b.size();
    if (r < x) {
        return prefa[r];
    }

    pair<long long, long long> h = (x == 0 ? make_pair(0ll, 0ll) : prefa[x - 1]);
    if (r < x + m) {
        h = add(h, mul(prefb[r - x], pw[x]));
        return h;
    }
    h = add(h, mul(prefb[m - 1], pw[x]));
    pair<long long, long long> suf = prefa[r - m];
    if (x != 0) {
        suf = sub(suf, prefa[x - 1]);
    }
    suf = mul(suf, pw[m]);
    return add(h, suf);
}


char get_char(int x, int r, string &a, string &b) {
    int n = a.size(), m = b.size();
    if (r < x) {
        return a[r];
    }
    if (r < x + m) {
        return b[r - x];
    }
    return a[r - m];
}


bool comp(int x, int y, string &a, string &b, vector<pair<long long, long long>> &prefa, vector<pair<long long, long long>> &prefb) {
    int n = a.size(), m = b.size();
    int l = 0, r = n + m - 1, sz = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (calc_hash(x, mid, a, b, prefa, prefb) == calc_hash(y, mid, a, b, prefa, prefb)) {
            sz = mid + 1;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    if (sz == n + m) {
        return true;
    }
    char ca = get_char(x, sz, a, b), cb = get_char(y, sz, a, b);
    if (ca < cb) {
        return true;
    }
    return false;
}

int main() {
    IOS;
    pw_p[0] = 1, pw_q[0] = 1;
    inv_p[0] = 1, inv_q[0] = 1;
    pw[0] = make_pair(1, 1);
    for (int i = 1; i < N; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
        pw[i] = make_pair(pw_p[i], pw_q[i]);
        inv_p[i] = inv_p[i - 1] * INV_P % M;
        inv_q[i] = inv_q[i - 1] * INV_Q % M;
    }
    string a, b;
    while (cin >> a) {
        cin >> b;
        int n = a.size(), m = b.size();
        vector<pair<long long, long long>> prefa(n), prefb(m);

        for (int i = 0; i < n; i++) {
            prefa[i].first = ((i == 0 ? 0 : prefa[i - 1].first) + (a[i] - '0' + 1) * pw_p[i]) % M;
            prefa[i].second = ((i == 0 ? 0 : prefa[i - 1].second) + (a[i] - '0' + 1) * pw_q[i]) % M;
        }

        for (int i = 0; i < m; i++) {
            prefb[i].first = ((i == 0 ? 0 : prefb[i - 1].first) + (b[i] - '0' + 1) * pw_p[i]) % M;
            prefb[i].second = ((i == 0 ? 0 : prefb[i - 1].second) + (b[i] - '0' + 1) * pw_q[i]) % M;
        }
        int best = 0;
        for (int i = 1; i <= n; i++) {
            if (!comp(best, i, a, b, prefa, prefb)) {
                best = i;
            }
        }
        string ans = "";
        if (best != 0) {
            ans += a.substr(0, best);
        }
        ans += b;
        if (best != n) {
            ans += a.substr(best, n - best);
        }
        cout << ans << endl;

    }
    return 0;
}
