//https://ocpc2025s.eolymp.space/en/compete/s47ok89k9t7evbt1ovdfvc933c/problem/11
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 25;
const long long M = 998244353;

const ll P = 26;
const ll Q = 53;

int parent[N];
int sz[N];
long long pw_p[N], pw_q[N];

struct chash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    long long operator()(pair<long long, long long> x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x.first + FIXED_RANDOM) + splitmix64(x.second * M + FIXED_RANDOM);

    }
};


gp_hash_table<pair<long long, long long>, long long, chash> dp;

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

long long calc(multiset<int> &st, int all) {
    if (st.size() == 1) {
        return 0;
    }
    long long p = 0, q = 0;
    int j = 0;
    for (auto x : st) {
        p = (p + pw_p[j] * x) % M;
        q = (q + pw_q[j] * x) % M;
        j++;
    }
    pair<long long, long long> h = {p, q};
    auto it = dp.find(h);
    if (it != dp.end()) {
        return it->second;
    }
    long long ans = 0;
    int stay = 0;
    vector<int> v;
    for (int x : st) {
        v.push_back(x);
    }
    int n = v.size();
    for (int i = 0; i < n; i++) {
        stay += v[i] * v[i];
    }
    long long inv = modPow(all, M - 2);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            st.erase(st.find(v[i]));
            st.erase(st.find(v[j]));
            st.insert(v[i] + v[j]);
            ans = (ans + calc(st, all) * (v[i] * v[j]) % M * inv % M) % M;
            st.erase(st.find(v[i] + v[j]));
            st.insert(v[i]);
            st.insert(v[j]);
        }
    }
    ans = (ans + 1) * all % M * modPow(all - stay, M - 2) % M;
    return dp[h] = ans;
}

int main() {
    IOS;
    pw_p[0] = 1, pw_q[0] = 1;
    for (int i = 1; i < N; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
    }
    int t, n;
    cin >> t >> n;
    while (t--) {
        int m;
        cin >> m;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            u = dsu_find(u), v = dsu_find(v);
            if (u != v) {
                dsu_unite(u, v);
            }
        }
        multiset<int> st;
        for (int i = 0; i < n; i++) {
            if (dsu_find(i) == i) {
                st.insert(sz[i]);
            }
        }

        cout << calc(st, n * n) << endl;
    }

    return 0;
}
