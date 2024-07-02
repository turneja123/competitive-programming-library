//https://dmoj.ca/problem/ccc20s3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const long long P = 26, Q = 53;

long long modInverse(long long a) {
    long long res = 1;
    long long y = M - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

struct chash {
    long long operator()(pair<long long, long long> x) const { return x.first* M + x.second; }
};

gp_hash_table<pair<long long, long long>, int, chash> mp;

int main() {
    IOS;
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    long long p = 1, q = 1;
    for (int i = 0; i < n; i++) {
        p = p * (P + a[i] - 'a') % M;
        q = q * (Q + a[i] - 'a') % M;
    }
    long long p_sub = 1, q_sub = 1, p_rolling = 0, q_rolling = 0;
    long long p_pow = 1, q_pow = 1;

    for (int i = 0; i < min(n, m); i++) {
        p_sub = p_sub * (P + b[i] - 'a') % M;
        q_sub = q_sub * (Q + b[i] - 'a') % M;
        p_rolling = (p_rolling * P + (b[i] - 'a' + 1)) % M;
        q_rolling = (q_rolling * Q + (b[i] - 'a' + 1)) % M;
        if (i != min(n, m) - 1) {
            p_pow = p_pow * P % M;
            q_pow = q_pow * Q % M;
        }
    }
    int ans = 0;
    if (p_sub == p && q_sub == q) {
        ans++;
    }
    mp[make_pair(p_rolling, q_rolling)] = 1;
    for (int i = n, l = 0; i < m; i++, l++) {
        p_sub = p_sub * (modInverse(P + b[l] - 'a')) % M;
        q_sub = q_sub * (modInverse(Q + b[l] - 'a')) % M;
        p_sub = p_sub * (P + b[i] - 'a') % M;
        q_sub = q_sub * (Q + b[i] - 'a') % M;
        p_rolling = ((p_rolling - p_pow * (b[l] - 'a' + 1) % M + M) % M * P + (b[i] - 'a' + 1)) % M;
        q_rolling = ((q_rolling - q_pow * (b[l] - 'a' + 1) % M + M) % M * Q + (b[i] - 'a' + 1)) % M;
        auto it = mp.find(make_pair(p_rolling, q_rolling));
        if (it == mp.end()) {
            if (p_sub == p && q_sub == q) {
                ans++;
            }
            mp[make_pair(p_rolling, q_rolling)] = 1;
        }
    }
    cout << ans;
    return 0;
}
