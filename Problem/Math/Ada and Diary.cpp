//https://www.spoj.com/problems/ADAHACK/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const __int128 M = 100000000003;

long long a[6];

__int128 modInverse(__int128 a, __int128 m) {
    __int128 res = 1;
    __int128 y = m - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}

vector<__int128> berlekamp_massey(vector<__int128> s) {
    int n = s.size(), l = 0, m = 0;
    vector<__int128> c(n), b(n), t(n);
    c[0] = 1, b[0] = 1;
    __int128 d = 1;
    for (int i = 0; i < n; i++) {
        m++;
        __int128 d_next = s[i];
        for (int j = 1; j <= l; j++) {
            d_next = (d_next + (c[j] * s[i - j]) % M) % M;
        }
        if (d_next == 0) {
            continue;
        }
        t = c;
        __int128 coef = (d_next * modInverse(d, M)) % M;
        for (int j = m; j < n; j++) {
            c[j] = (c[j] - (coef * b[j - m]) % M + M) % M;
        }
        if (2 * l > i) {
            continue;
        }
        l = i + 1 - l, b = t, d = d_next, m = 0;
    }
    c.resize(l + 1);
    c.erase(c.begin());
    for (int i = 0; i < l; i++) {
        c[i] *= -1;
        c[i] = (c[i] + M) % M;
    }
    return c;
}


int main() {
    IOS;
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        for(int i = 0; i < 6; i++) {
            iss >> a[i];
        }
        vector<__int128> s(6);
        for (int i = 0; i < 6; i++) {
            s[i] = a[i];
        }
        vector<__int128> c = berlekamp_massey(s);
        __int128 ans = 0;
        for (int j = 0; j < c.size(); j++) {
            ans += c[j] * s[6 - j - 1];
        }
        ans %= M;
        cout << (long long)ans << endl;
    }

    return 0;
}
