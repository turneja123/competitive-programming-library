//https://cses.fi/problemset/task/2106
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

string a;

const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;

struct chash {
    long long operator()(pair<long long, long long> x) const { return x.first* M + x.second; }
};

gp_hash_table<pair<long long, long long>, int, chash> mp;

int main() {
    IOS;
    cin >> a;
    int n = a.size();

    int l = 1, r = n;
    pair<int, int> ans = make_pair(-1, -1);
    while (l <= r) {
        int m = (l + r) / 2;
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
        mp[sub] = 1;
        bool can = false;
        for (int i = m; i < n && !can; i++) {
            p = ((p - (a[i - m] - 'a' + 1) + M) * INV_P + p_pow * (a[i] - 'a' + 1)) % M;
            q = ((q - (a[i - m] - 'a' + 1) + M) * INV_Q + q_pow * (a[i] - 'a' + 1)) % M;
            sub = make_pair(p, q);
            auto it = mp.find(sub);
            if (it != mp.end()) {
                can = true;
                ans = make_pair(m, i - m + 1);
            } else {
                mp[sub] = 1;
            }
        }
        if (can) {
            l = m + 1;
        } else {
            r = m - 1;
        }
        mp.clear();
    }
    if (ans.first == -1) {
        cout << -1;
    } else {
        for (int i = ans.second; i < ans.second + ans.first; i++) {
            cout << a[i];
        }
    }


    return 0;
}
