//https://atcoder.jp/contests/abc288/tasks/abc288_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

vector<long long> pref[15];
vector<int> inds[15];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    /*map<int, int> mp[n];
    for (int i = 0; i < n; i++) {
        mp[i][i]++;
    }
    for (int i = 0; i < n; i++) {
        if (i + k < n) {
            for (int j = i + 1; j < i + k; j++) {
                for (auto [x, y] : mp[i]) {
                    mp[j][x] -= y;
                }
            }
        } else {
            cout << i << ": " << endl << endl;
            for (auto [x, y] : mp[i]) {
                if (y == 0) {
                    continue;
                }
                cout << x << " " << y << endl;
            }
            cout << endl;
        }
    }
    return 0;*/
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        long long x = ((pref[i % k].empty()) ? a[i] : pref[i % k].back() + a[i]);
        pref[i % k].push_back(x);
        inds[i % k].push_back(i);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (k == 1) {
            cout << "Yes" << endl;
            continue;
        }
        if (r - l + 1 == k) {
            string ans = "Yes";
            int x = a[l];
            for (int j = l; j <= r; j++) {
                if (a[j] != x) {
                    ans = "No";
                }
            }
            cout << ans << endl;
            continue;
        }
        int md = (l + r - l + 1 - 1) % k;

        int L = lower_bound(inds[md].begin(), inds[md].end(), l) - inds[md].begin();
        int R = lower_bound(inds[md].begin(), inds[md].end(), r) - inds[md].begin() - 1;
        long long diff = pref[md][R] - (L == 0 ? 0 : pref[md][L - 1]);

        vector<long long> v;
        for (int j = 0; j < k - 1; j++) {
            int md = (l + r - l + 1 + j) % k;
            int L = lower_bound(inds[md].begin(), inds[md].end(), l) - inds[md].begin();
            int R = lower_bound(inds[md].begin(), inds[md].end(), r) - inds[md].begin() - 1;
            long long cur = pref[md][R] - (L == 0 ? 0 : pref[md][L - 1]) - diff;
            v.push_back(cur);
        }
        v.push_back(a[r]);
        string ans = "Yes";
        long long x = v[0];
        for (int j = 0; j < k; j++) {
            if (v[j] != x) {
                ans = "No";
            }
        }
        cout << ans << endl;
    }


    return 0;
}
