//https://www.spoj.com/problems/JPM2/
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define int long long
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using cd = complex<double>;
const double PI = acos(-1);
const int N = 5e5 + 5;

bool composite[N];


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
    composite[1] = true;
    for (int i = 2; i < N; i++) {
        if (!composite[i]) {
            for (int j = i * i; j < N; j += i) {
                composite[j] = true;
            }
        }
    }
    vector<int> a(N + 1, 0);
    vector<int> b(N + 1, 0);
    for (int i = 2; i < N; i++) {
        if (!composite[i]) {
            a[i] = 1;
            b[i] = 1;
        }
    }
    vector<int> even = multiply(a, b);
    even.resize(N + 1);
    vector<int> doubles(N + 1);
    for (int i = 2; i < even.size(); i++) {
        even[i] /= 2;
        if (i % 2 == 0 && !composite[i / 2]) {
            doubles[i] = 1;
        }
    }
    vector<int> odd = multiply(even, a);
    vector<int> duplicate = multiply(doubles, a);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n == 1 || n == 4 || n == 6) {
            cout << "-1 -1" << endl;
        } else if (!composite[n]) {
            cout << "1 1" << endl;
        } else if (n % 2 == 0) {
            cout << "2 " << even[n] << endl;
        } else if (!composite[n - 2]) {
            cout << "2 1" << endl;
        } else {
            cout << "3 " << (odd[n] - duplicate[n]) / 3 + ((odd[n] - duplicate[n]) % 3 == 2) << endl;
        }
    }

    return 0;
}
