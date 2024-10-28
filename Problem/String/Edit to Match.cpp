//https://atcoder.jp/contests/abc377/tasks/abc377_g
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

struct chash {
    long long operator()(pair<long long, long long> x) const { return x.first* M + x.second; }
};

gp_hash_table<pair<long long, long long>, int, chash> mp[N];

int main() {
    IOS;
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        string s;
        cin >> s;
        int n = s.size();
        int ans = n;
        long long p = 0, q = 0;
        long long p_pow = 1, q_pow = 1;
        for (int i = 0; i < n; i++) {
            p = (p + p_pow * (s[i] - 'a' + 1)) % M;
            q = (q + q_pow * (s[i] - 'a' + 1)) % M;
            p_pow = (p_pow * P) % M;
            q_pow = (q_pow * Q) % M;
            auto it = mp[i].find(make_pair(p, q));
            if (it != mp[i].end()) {
                ans = min(ans, n - i - 1 + (it->second - i - 1));
                it->second = min(it->second, n);
            } else {
                mp[i][make_pair(p, q)] = n;
            }
        }
        cout << ans << endl;

    }
    return 0;
}
