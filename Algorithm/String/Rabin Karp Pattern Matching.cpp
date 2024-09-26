//https://cses.fi/problemset/task/1753/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

string a, b;

const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;

pair<long long, long long> calc(string s) {
    int n = s.size();
    long long p = 0, q = 0;
    long long p_pow = 1, q_pow = 1;
    for (int i = 0; i < n; i++) {
        p = (p + p_pow * (s[i] - 'a' + 1)) % M;
        q = (q + q_pow * (s[i] - 'a' + 1)) % M;
        p_pow = (p_pow * P) % M;
        q_pow = (q_pow * Q) % M;
    }
    return make_pair(p, q);
}

int main() {
    IOS;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    if (n < m) {
        cout << 0 << endl;
        return 0;
    }
    pair<long long, long long> h = calc(b);

    long long p = 0, q = 0;
    long long p_pow = 1, q_pow = 1;
    for (int i = 0; i < m; i++) {
        p = (p + p_pow * (a[i] - 'a' + 1)) % M;
        q = (q + q_pow * (a[i] - 'a' + 1)) % M;
        if (i != m - 1) {
            p_pow = (p_pow * P) % M;
            q_pow = (q_pow * Q) % M;
        }
    }
    pair<long long, long long> sub = make_pair(p, q);
    int ans = 0;
    if (sub == h) {
        ans++;
    }
    for (int i = m; i < n; i++) {
        p = ((p - (a[i - m] - 'a' + 1) + M) * INV_P + p_pow * (a[i] - 'a' + 1)) % M;
        q = ((q - (a[i - m] - 'a' + 1) + M) * INV_Q + q_pow * (a[i] - 'a' + 1)) % M;
        sub = make_pair(p, q);
        if (sub == h) {
            ans++;
        }
    }
    cout << ans << endl;


    return 0;
}
