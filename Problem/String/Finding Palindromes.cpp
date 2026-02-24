//https://www.spoj.com/problems/VPALIN/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;

const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;

int n[N];
string s[N];

long long pw_p[N], pw_q[N];
long long inv_p[N], inv_q[N];

vector<pair<long long, long long>> pref[N], suf[N];

pair<long long, long long> get_pref(int l, int r, int n, int m) {
    pair<long long, long long> ans = pref[m][r];
    if (l != 0) {
        ans.first = (ans.first - pref[m][l - 1].first + M) * inv_p[l] % M;
        ans.second = (ans.second - pref[m][l - 1].second + M) * inv_q[l] % M;
    }
    return ans;
}

pair<long long, long long> get_suf(int l, int r, int n, int m) {
    pair<long long, long long> ans = suf[m][l];
    if (r != n - 1) {
        ans.first = (ans.first - suf[m][r + 1].first + M) * inv_p[n - 1 - r] % M;
        ans.second = (ans.second - suf[m][r + 1].second + M) * inv_q[n - 1 - r] % M;
    }
    return ans;
}


vector<pair<ll, ll>> pref_full[N], pref_pref[N];
vector<int> ct_full[N], ct_pref[N];

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
    int t;
    cin >> t;
    for (int m = 0; m < t; m++) {
        cin >> n[m] >> s[m];
        pref[m].resize(n[m]);
        suf[m].resize(n[m]);


        for (int i = 0; i < n[m]; i++) {
            pref[m][i].first = ((i == 0 ? 0 : pref[m][i - 1].first) + (s[m][i] - 'a' + 1) * pw_p[i]) % M;
            pref[m][i].second = ((i == 0 ? 0 : pref[m][i - 1].second) + (s[m][i] - 'a' + 1) * pw_q[i]) % M;
        }
        for (int i = n[m] - 1; i >= 0; i--) {
            suf[m][i].first = ((i == n[m] - 1 ? 0 : suf[m][i + 1].first) + (s[m][i] - 'a' + 1) * pw_p[n[m] - 1 - i]) % M;
            suf[m][i].second = ((i == n[m] - 1 ? 0 : suf[m][i + 1].second) + (s[m][i] - 'a' + 1) * pw_q[n[m] - 1 - i]) % M;
        }
        pref_full[n[m]].push_back(pref[m][n[m] - 1]);
        pref_pref[n[m]].push_back(pref[m][n[m] - 1]);

        for (int i = 0; i < n[m] - 1; i++) {
            if (get_pref(0, i, n[m], m) == get_suf(0, i, n[m], m)) {
                pref_pref[n[m] - 1 - i].push_back(get_pref(i + 1, n[m] - 1, n[m], m));
            }
        }
    }
    for (int i = 0; i < N; i++) {
        if (pref_pref[i].size()) {
            sort(pref_pref[i].begin(), pref_pref[i].end());
            int ct = 1; auto last = pref_pref[i][0];
            for (int j = 1; j < pref_pref[i].size(); j++) {
                if (pref_pref[i][j] != last) {
                    ct_pref[i].push_back(ct);
                    ct = 0;
                    last = pref_pref[i][j];
                }
                ct++;
            }
            ct_pref[i].push_back(ct);
            pref_pref[i].erase(unique(pref_pref[i].begin(), pref_pref[i].end()), pref_pref[i].end());
        }
        if (pref_full[i].size()) {
            sort(pref_full[i].begin(), pref_full[i].end());
            int ct = 1; auto last = pref_full[i][0];
            for (int j = 1; j < pref_full[i].size(); j++) {
                if (pref_full[i][j] != last) {
                    ct_full[i].push_back(ct);
                    ct = 0;
                    last = pref_full[i][j];
                }
                ct++;
            }
            ct_full[i].push_back(ct);
            pref_full[i].erase(unique(pref_full[i].begin(), pref_full[i].end()), pref_full[i].end());
        }

    }

    long long ans = 0;
    for (int m = 0; m < t; m++) {
        int j = lower_bound(pref_pref[n[m]].begin(), pref_pref[n[m]].end(), suf[m][0]) - pref_pref[n[m]].begin();
        if (j != pref_pref[n[m]].size() && pref_pref[n[m]][j] == suf[m][0]) {
            ans += ct_pref[n[m]][j];
        }
        for (int i = n[m] - 1; i > 0; i--) {
            if (get_pref(i, n[m] - 1, n[m], m) == get_suf(i, n[m] - 1, n[m], m)) {

                int j = lower_bound(pref_full[i].begin(), pref_full[i].end(), get_suf(0, i - 1, n[m], m)) - pref_full[i].begin();
                if (j != pref_full[i].size() && pref_full[i][j] == get_suf(0, i - 1, n[m], m)) {
                    ans += ct_full[i][j];
                }
            }
        }
    }
    cout << ans;
    return 0;
}
