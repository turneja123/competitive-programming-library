//https://www.spoj.com/problems/ADAMATCH/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define int long long
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int ans[2 * N];
vector<char> c = {'A', 'C', 'G', 'T'};

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

main() {
    IOS;
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    for (int j = 0; j < 4; j++) {
        vector<int> x(n, 0);
        vector<int> y(m, 0);
        for (int i = 0; i < n; i++) {
            if (a[i] == c[j]) {
                x[i] = 1;
            }
        }
        for (int i = 0; i < m; i++) {
            if (b[i] == c[j]) {
                y[m - 1 - i] = 1;
            }
        }
        vector<int> z = multiply(x, y);
        for (int i = m - 1; i <= m - 1 + n - m; i++) {
            ans[i - (m - 1)] += z[i];
        }
    }
    int mn = m;
    for (int i = 0; i <= n - m; i++) {
        mn = min(mn, m - ans[i]);
    }
    cout << mn;

    return 0;
}
