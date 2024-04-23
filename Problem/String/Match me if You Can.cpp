//https://www.spoj.com/problems/STRMATCH/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long M = 1e9 + 7;
long long P = 26, Q = 53;
const int N = 3005;

struct chash {
    long long operator()(pair<long long, long long> x) const { return x.first* (long long)(1000000007) + x.second; }
};
gp_hash_table<pair<long long, long long>, int, chash> mp[N];

void hash_sub(string &s, int i) {
    long long p_pow = 1, q_pow = 1;
    long long p_sub = 0, q_sub = 0;
    for (int j = i - 1; j >= 0; j--) {
        long long c = (s[j] - 'a') + 1;
        p_sub = (p_sub + c * p_pow) % M;
        q_sub = (q_sub + c * q_pow) % M;
        if (j != 0) {
            p_pow = (p_pow * P) % M;
            q_pow = (q_pow * Q) % M;
        }
    }
    mp[i][make_pair(p_sub, q_sub)]++;
    for (int j = i; j < s.size(); j++) {
        long long c_prev = (s[j - i] - 'a') + 1;
        long long c = (s[j] - 'a') + 1;
        p_sub = (((p_sub - c_prev * p_pow % M + M) % M) * P + c) % M;
        q_sub = (((q_sub - c_prev * q_pow % M + M) % M) * Q + c) % M;
        mp[i][make_pair(p_sub, q_sub)]++;
    }
}

pair<long long, long long> hash_string(string &s) {
    long long p_pow = 1, q_pow = 1;
    long long p = 0, q = 0;
    for (int j = s.size() - 1; j >= 0; j--) {
        long long c = (s[j] - 'a') + 1;
        p = (p + c * p_pow) % M;
        q = (q + c * q_pow) % M;
        if (j != 0) {
            p_pow = (p_pow * P) % M;
            q_pow = (q_pow * Q) % M;
        }
    }
    return make_pair(p, q);
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    for (int i = 1; i <= n; i++) {
        hash_sub(s, i);
    }
    for (int i = 0; i < q; i++) {
        string a;
        cin >> a;
        if (a.size() > s.size()) {
            cout << 0 << endl;
        } else {
            auto it = mp[a.size()].find(hash_string(a));
            if (it != mp[a.size()].end()) {
                cout << it->second << endl;
            } else {
                cout << 0 << endl;
            }
        }
    }

    return 0;
}
