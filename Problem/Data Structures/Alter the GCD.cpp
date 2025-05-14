//https://codeforces.com/contest/2005/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int K = 20;

int a[2][N];
int table[2][K][N];

int ans = 0; long long ct = 0;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void build(int n, int j) {
    for (int i = 1; i <= n; i++) {
        table[j][0][i] = a[j][i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[j][k][i] = __gcd(table[j][k - 1][i], table[j][k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query(int l, int r, int j) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    return __gcd(table[j][k][l], table[j][k][r - (1 << k) + 1]);
}

void solve(int n) {
    build(n, 0);
    build(n, 1);
    gp_hash_table<int, int, custom_hash> mpa, mpb;
    mpa[a[0][0]] = 0;
    mpb[a[1][0]] = 0;
    ans = __gcd(a[1][0], query(1, n - 1, 0)) + __gcd(a[0][0], query(1, n - 1, 1));
    ct = 1;
    vector<int> events_pref{0, 1};
    int ga = a[0][0], gb = a[1][0];
    for (int i = 1; i < n; i++) {
        int nxa = __gcd(ga, a[0][i]), nxb = __gcd(gb, a[1][i]);
        if (nxa != ga || nxb != gb) {
            events_pref.push_back(i + 1);
            events_pref.push_back(i);
        }
        ga = nxa, gb = nxb;
    }
    sort(events_pref.begin(), events_pref.end());
    events_pref.erase(unique(events_pref.begin(), events_pref.end()), events_pref.end());

    for (int i = 1; i < n; i++) {
        gp_hash_table<int, int, custom_hash> nxa, nxb;
        nxa[a[0][i]] = i;
        nxb[a[1][i]] = i;
        for (auto [g, j] : mpa) {
            int G = __gcd(g, a[0][i]);
            auto it = nxa.find(G);
            if (it == nxa.end()) {
                nxa[G] = j;
            } else if (j < it->second) {
                nxa[G] = j;
            }
        }
        for (auto [g, j] : mpb) {
            int G = __gcd(g, a[1][i]);
            auto it = nxb.find(G);
            if (it == nxb.end()) {
                nxb[G] = j;
            } else if (j < it->second) {
                nxb[G] = j;
            }
        }
        mpa = nxa;
        mpb = nxb;
        vector<int> events;
        for (auto [g, j] : mpa) {
            events.push_back(j);
        }
        for (auto [g, j] : mpb) {
            events.push_back(j);
        }
        for (int j : events_pref) {
            if (j <= i) {
                events.push_back(j);
            } else {
                break;
            }
        }
        sort(events.begin(), events.end());
        events.erase(unique(events.begin(), events.end()), events.end());
        int last = i + 1;
        for (int k = events.size() - 1; k >= 0; k--) {
            int j = events[k];
            int g1 = query(j, i, 1);
            if (j != 0) {
                g1 = __gcd(g1, query(0, j - 1, 0));
            }
            if (i != n - 1) {
                g1 = __gcd(g1, query(i + 1, n - 1, 0));
            }

            int g2 = query(j, i, 0);
            if (j != 0) {
                g2 = __gcd(g2, query(0, j - 1, 1));
            }
            if (i != n - 1) {
                g2 = __gcd(g2, query(i + 1, n - 1, 1));
            }
            if (g1 + g2 > ans) {
                ans = g1 + g2;
                ct = last - j;
            } else if (g1 + g2 == ans) {
                ct += last - j;
            }
            last = j;
        }
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[0][i];
        }
        for (int i = 0; i < n; i++) {
            cin >> a[1][i];
        }
        if (n == 1) {
            cout << a[0][0] + a[1][0] << " " << 1 << endl;
            continue;
        }
        ans = 0, ct = 0;
        solve(n);
        cout << ans << " " << ct << endl;

    }
    return 0;
}
