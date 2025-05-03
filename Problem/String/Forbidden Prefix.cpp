//https://atcoder.jp/contests/abc403/tasks/abc403_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 53, INV_Q = 56603774;

long long pw_p[N], pw_q[N];

map<pair<long long, long long>, set<int>> pref[N];
set<pair<long long, long long>> st;

string strings[N];

int main() {
    IOS;
    pw_p[0] = 1, pw_q[0] = 1;
    for (int i = 1; i < N; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
    }
    int q;
    cin >> q;
    int ans = 0;
    for (int j = 0; j < q; j++) {
        int t; string s;
        cin >> t >> s;
        strings[j] = s;
        int n = s.size();
        if (t == 1) {
            pair<long long, long long> h = make_pair(0, 0);
            for (int i = 0; i < n; i++) {
                h.first = (h.first + pw_p[i] * (s[i] - 'a' + 1)) % M;
                h.second = (h.second + pw_q[i] * (s[i] - 'a' + 1)) % M;
            }
            st.insert(h);
            auto it = pref[n - 1].find(h);
            if (it != pref[n - 1].end()) {
                set<int> tmp = it->second;
                for (auto j : tmp) {
                    ans--;
                    pair<long long, long long> h = make_pair(0, 0);
                    for (int i = 0; i < strings[j].size(); i++) {
                        h.first = (h.first + pw_p[i] * (strings[j][i] - 'a' + 1)) % M;
                        h.second = (h.second + pw_q[i] * (strings[j][i] - 'a' + 1)) % M;
                        pref[i][h].erase(j);
                    }
                }
            }

        } else {
            pair<long long, long long> h = make_pair(0, 0);
            vector<pair<long long, long long>> v;
            for (int i = 0; i < n; i++) {
                h.first = (h.first + pw_p[i] * (s[i] - 'a' + 1)) % M;
                h.second = (h.second + pw_q[i] * (s[i] - 'a' + 1)) % M;
                if (st.find(h) != st.end()) {
                    break;
                }
                v.push_back(h);
            }
            if (v.size() == n) {
                ans++;
                for (int i = 0; i < n; i++) {
                    pref[i][v[i]].insert(j);
                }
            }
        }
        cout << ans << endl;
    }

    return 0;
}
