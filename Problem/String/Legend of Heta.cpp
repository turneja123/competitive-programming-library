//https://www.spoj.com/problems/BLHETA/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 105;

const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;

long long pw_p[N], pw_q[N];
long long inv_p[N], inv_q[N];

pair<long long, long long> hsh[K];
string a[K];
vector<tuple<long long, long long, int>> pref;


int main() {
    IOS;
    pw_p[0] = 1, pw_q[0] = 1;
    inv_p[0] = 1, inv_q[0] = 1;
    for (int i = 1; i < N; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
        inv_p[i] = inv_p[i - 1] * INV_P % M;
        inv_q[i] = inv_q[i - 1] * INV_Q % M;
    }
    string s;
    cin >> s;
    int n = s.size();
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        for (int j = 0; j < a[i].size(); j++) {
            hsh[i].first = (hsh[i].first + (a[i][j] - 'A' + 1) * pw_p[j]) % M;
            hsh[i].second = (hsh[i].second + (a[i][j] - 'A' + 1) * pw_q[j]) % M;
        }
    }
    for (int i = 0; i < n; i++) {
        if (pref.empty()) {
            pref.push_back(make_tuple(s[i] - 'A' + 1, s[i] - 'A' + 1, i));
        } else {
            auto [pf, ps, j] = pref.back();
            int sz = pref.size();
            pref.push_back(make_tuple((pf + (s[i] - 'A' + 1) * pw_p[sz]) % M, (ps + (s[i] - 'A' + 1) * pw_q[sz]) % M, i));
        }
        for (int j = 0; j < m; j++) {
            int r = (int)pref.size() - 1, l = r - (int)a[j].size() + 1;
            if (l < 0) {
                continue;
            }
            pair<long long, long long> h = make_pair(get<0>(pref.back()), get<1>(pref.back()));
            if (l != 0) {
                h = make_pair((h.first - get<0>(pref[l - 1]) + M) * inv_p[l] % M, ((h.second - get<1>(pref[l - 1]) + M) * inv_q[l] % M));
            }
            if (h == hsh[j]) {
                for (int k = 0; k < a[j].size(); k++) {
                    pref.pop_back();
                }
            }
        }
    }
    string ans = "";
    for (auto [pf, ps, j] : pref) {
        ans += s[j];
    }
    cout << ans;
    return 0;
}
