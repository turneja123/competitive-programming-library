//https://codeforces.com/contest/2149/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int SQ = 250;

int a[N];
int heavy[N];
int freq[N];
int pref[SQ][N];
int val[N];
int id[N];
bool seen[N];

vector<int> pos[N];
mt19937 gen(1);

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<pair<int, int>> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i].first;
            v[i].second = i;
        }
        sort(v.begin(), v.end());
        int m = -1, last = -1;
        for (int i = 0; i < n; i++) {
            if (v[i].first != last) {
                last = v[i].first;
                m++;
            }
            val[m] = last;
            a[v[i].second] = m;
        }
        m++;
        for (int i = 0; i < n; i++) {
            freq[a[i]]++;
            pos[a[i]].push_back(i);
        }
        vector<pair<int, int>> sorted;
        for (int i = 0; i < m; i++) {
            sorted.push_back({freq[i], i});
        }
        sort(sorted.begin(), sorted.end(), greater<pair<int, int>>());
        int z = 0;
        for (int i = 0; i < min(m, SQ); i++) {
            int j = sorted[i].second;
            heavy[j] = true;
            id[j] = z++;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < z; j++) {
                pref[j][i] = (i == 0 ? 0 : pref[j][i - 1]);
            }
            if (heavy[a[i]]) {
                pref[id[a[i]]][i]++;
            }
        }
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            int need = (r - l + 1) / 3;
            vector<int> ans;
            for (int rep = 0; rep < 70; rep++) {
                int j = l + (gen() % (r - l + 1));
                int ct;
                if (!heavy[a[j]]) {
                    ct = upper_bound(pos[a[j]].begin(), pos[a[j]].end(), r) - lower_bound(pos[a[j]].begin(), pos[a[j]].end(), l);
                } else {
                    ct = pref[id[a[j]]][r] - (l == 0 ? 0 : pref[id[a[j]]][l - 1]);

                }
                if (ct > need) {
                    if (!seen[a[j]]) {
                        seen[a[j]] = true;
                        ans.push_back(a[j]);
                    }
                }

            }
            vector<int> conv_ans;
            for (int x : ans) {
                conv_ans.push_back(val[x]);
                seen[x] = false;
            }
            if (conv_ans.size()) {
                sort(conv_ans.begin(), conv_ans.end());
                for (int x : conv_ans) {
                    cout << x << " ";
                }
            } else {
                cout << -1;
            }
            cout << endl;

        }
        for (int i = 0; i < n; i++) {
            pos[a[i]].clear();
            heavy[a[i]] = false;
            freq[a[i]] = 0;
        }

    }
    return 0;
}
