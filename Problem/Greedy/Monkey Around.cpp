//https://www.facebook.com/codingcompetitions/hacker-cup/2025/practice-round/problems/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int a[N];

int main() {
    IOS;
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<int> st;
        vector<pair<int, int>> blk;
        int i = 0;
        while (i < n) {
            if (a[i] == 1) {
                int last = a[i] - 1;
                while (i < n && a[i] == last + 1) {
                    st.push_back(a[i]);
                    last = a[i];
                    i++;
                }
            } else {
                int last = a[i];
                while (a[i] != 1) {
                    st.push_back(a[i]);
                    i++;
                }
                for (int j = 1; j < last; j++) {
                    st.push_back(a[i]);
                    i++;
                }
            }
            int pos;
            for (int j = 0; j < st.size(); j++) {
                if (st[j] == 1) {
                    pos = j;
                }
            }
            blk.push_back({st.size(), pos});
            st.clear();
        }


        vector<pair<int, int>> ans;
        int rot = 0;
        while (blk.size()) {
            auto [n, j] = blk.back();
            j = (j + rot) % n;
            for (int i = 0; i < (n - j) % n; i++) {
                ans.push_back({2, -1});
                rot++;
            }
            ans.push_back({1, n});
            blk.pop_back();
        }
        reverse(ans.begin(), ans.end());
        cout << "Case #" << tt << ": " << ans.size() << endl;
        for (auto [x, y] : ans) {
            if (y != -1) {
                cout << x << " " << y << endl;
            } else {
                cout << x << endl;
            }
        }


    }
    return 0;
}
