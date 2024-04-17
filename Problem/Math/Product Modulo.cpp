//https://atcoder.jp/contests/agc047/tasks/agc047_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define int long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 200003;

int pos[M];
int val[M];
int dupl[3 * M];

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
    int root = 2, i = root;
    for (int j = 1; j < M; i = (root * i) % M, j++) {
        pos[i] = j;
        val[j] = i;
    }
    vector<long long> a(M, 0);
    vector<long long> b(M, 0);
    int n; long long ans = 0;
    cin >> n;
    for (int j = 0; j < n; j++) {
        int k;
        cin >> k;
        if (k != 0) {
            a[pos[k]]++;
            b[pos[k]]++;
        }
    }
    for (int j = 1; j < M; j++) {
        dupl[j + j] = a[j];
    }

    vector<long long> c = multiply(a, b);
    for (int j = 1; j < c.size(); j++) {
        int ind = (j >= M) ? (j + 1) % M : j;
        ans += (c[j] - dupl[j]) * val[ind] / 2;
    }
    cout << ans;

    return 0;
}
