//https://codeforces.com/contest/1977/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

pair<__int128, __int128> h[N];
pair<__int128, __int128> hc[N];
vector<int> a[N];

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

__int128 gen() {
    long long h = generator() + ((__int128)generator() << 30) + ((__int128)generator() << 60);
    return h;
}

map<pair<__int128, __int128>, int> mp;

int main() {
    IOS;
    for (int i = 0; i < N; i++) {
        h[i].first = generator();
        h[i].second = generator();
    }
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            a[i].resize(m);
            string s;
            cin >> s;
            for (int j = 0; j < m; j++) {
                a[i][j] = s[j] - '0';
                if (a[i][j]) {
                    hc[j].first ^= h[i].first;
                    hc[j].second ^= h[i].second;

                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                __int128 hf =  hc[j].first ^ h[i].first;
                __int128 hs =  hc[j].second ^ h[i].second;
                mp[make_pair(hf, hs)]++;
            }
        }
        pair<__int128, __int128> ans;
        int best = 0;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            if (it->second > best) {
                best = it->second;
                ans = it->first;
            }
        }
        vector<int> s(n, 0);
        bool found = false;
        for (int i = 0; i < n && !found; i++) {
            for (int j = 0; j < m && !found; j++) {
                __int128 hf =  hc[j].first ^ h[i].first;
                __int128 hs =  hc[j].second ^ h[i].second;
                if (hf == ans.first && hs == ans.second) {
                    for (int k = 0; k < n; k++) {
                        s[k] = a[k][j];
                    }
                    s[i] ^= 1;
                    found = true;
                }
            }
        }
        cout << best << endl;
        for (int i = 0; i < n; i++) {
            cout << s[i];
            a[i].clear();
        }
        cout << endl;
        mp.clear();
        for (int j = 0; j < m; j++) {
            hc[j] = make_pair(0, 0);
        }
    }

    return 0;
}
