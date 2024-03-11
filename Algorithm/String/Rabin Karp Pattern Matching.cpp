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
const long long P = 26;
const long long Q = 53;

long long compute_hash(string s, long long X) {
    long long hash_value = 0;
    long long p_pow = 1;
    for (int i = s.size() - 1; i >= 0; i--) {
        hash_value = (hash_value + (long long)(s[i] - 'a' + 1) * p_pow) % M;
        p_pow = (p_pow * X) % M;
    }
    return hash_value;
}

int main() {
    IOS;
    cin >> a >> b;
    if (a.size() < b.size()) {
        cout << 0 << endl;
        return 0;
    }
    pair<long long, long long> h = make_pair(compute_hash(b, P), compute_hash(b, Q));
    long long p = 0, q = 0;
    long long p_pow = 1, q_pow = 1;
    int ans = 0;
    for (int i = b.size() - 1; i >= 0; i--) {
        p = (p + (long long)(a[i] - 'a' + 1) * p_pow) % M;
        q = (q + (long long)(a[i] - 'a' + 1) * q_pow) % M;
        if (i != 0) {
            p_pow = (p_pow * P) % M;
            q_pow = (q_pow * Q) % M;
        }
    }
    pair<long long, long long> sub = make_pair(p, q);
    if (sub == h) {
        ans++;
    }
    for (int i = b.size(); i < a.size(); i++) {
        p = (((p - p_pow * (long long)(a[i - b.size()] - 'a' + 1) + P * M) % M) * P + (long long)(a[i] - 'a' + 1)) % M;
        q = (((q - q_pow * (long long)(a[i - b.size()] - 'a' + 1) + Q * M) % M) * Q + (long long)(a[i] - 'a' + 1)) % M;
        sub = make_pair(p, q);
        if (sub == h) {
            ans++;
        }
    }
    cout << ans << endl;


    return 0;
}
