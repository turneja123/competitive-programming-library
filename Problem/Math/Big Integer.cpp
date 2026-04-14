//https://dmoj.ca/problem/bts17p8
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int f[N];
int val[N];
int p[N];
int d[N];
int state[N];

int mn[4 * N];
int who[4 * N];

ll ans[N];

using cd = complex<double>;
const double PI = acos(-1);

int reverse(int num, int lg_n) {
    int res = 0;
    for (int i = 0; i < lg_n; i++) {
        if (num & (1 << i)) {
            res |= 1 << (lg_n - 1 - i);
        }
    }
    return res;
}

void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n) {
        lg_n++;
    }

    for (int i = 0; i < n; i++) {
        if (i < reverse(i, lg_n)) {
            swap(a[i], a[reverse(i, lg_n)]);
        }
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

vector<int> multiply(vector<int> & a, vector<int> & b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = round(fa[i].real());
    }
    return result;
}


void build(int l, int r, int node) {

    if (l == r) {
        mn[node] = d[state[l]];
        who[node] = l;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    if (mn[2 * node + 1] < mn[2 * node + 2]) {
        mn[node] = mn[2 * node + 1];
        who[node] = who[2 * node + 1];
    } else {
        mn[node] = mn[2 * node + 2];
        who[node] = who[2 * node + 2];
    }
}

void calc(int l, int r, int node, int j) {
    int mx = 0;
    for (int i = l; i <= r; i++) {
        mx = max(mx, d[state[i]]);
    }
    vector<int> a(mx - mn[node] + 1, 0);
    vector<int> b(mn[node] - j + 1, 0);
    for (int i = l; i <= r; i++) {
        a[d[state[i]] - mn[node]]++;
    }
    int u = state[who[node]];
    while (d[u] != j) {
        b[mn[node] - d[u] + 1] += val[u];
        u = p[u];
    }
    vector<int> c = multiply(a, b);
    for (int i = 0; i < c.size(); i++) {
        ans[i] += c[i];
    }

    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    calc(l, mid, 2 * node + 1, mn[node]);
    calc(mid + 1, r, 2 * node + 2, mn[node]);
}

int main() {
    IOS;
    int n, cur = 0, m = 1;
    cin >> n;
    string s;
    cin >> s;
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == '-') {
            cur = p[cur];
        } else {
            p[m] = cur;
            val[m] = s[i - 1] - '0';
            d[m] = d[cur] + 1;
            cur = m++;
        }
        state[i] = cur;
    }
    build(0, n, 0);
    calc(0, n, 0, 0);
    string a = "";
    ll c = 0;
    for (int i = 1; i < N; i++) {
        c += ans[i];
        a += '0' + c % 10;
        c /= 10;
    }
    reverse(a.begin(), a.end());
    cout << a;

    return 0;
}
