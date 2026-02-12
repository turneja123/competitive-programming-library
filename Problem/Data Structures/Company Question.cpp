//https://acm.timus.ru/problem.aspx?space=1&num=2199
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e4 + 5;
const int B = 175;
const int INF = 2e9 + 5;

pair<int, int> ans[N];
int a[N];
vector<tuple<int, int, int>> queries[B];


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[l / B].push_back(make_tuple(r, l, i));
    }
    for (int i = 0; i < B; i++) {
        if (queries[i].empty()) {
            continue;
        }

        sort(queries[i].begin(), queries[i].end());

        int ptr = (i + 1) * B;
        int mn = INF, x = -1, y = -1;
        set<pair<int, int>> st;


        for (auto [r, l, ind] : queries[i]) {
            while (ptr <= r) {
                if (st.size()) {
                    auto it = st.lower_bound({-a[ptr], INF});
                    if (it != st.end() && abs(a[ptr] + it->first) < mn) {
                        mn = abs(a[ptr] + it->first);
                        x = ptr, y = it->second;
                    }
                    if (it-- != st.begin() && abs(a[ptr] + it->first) < mn) {
                        mn = abs(a[ptr] + it->first);
                        x = ptr, y = it->second;
                    }
                }
                st.insert({a[ptr], ptr});
                ptr++;
            }
            set<pair<int, int>> tmp;
            tuple<int, int, int> restore = make_tuple(mn, x, y);
            for (int j = min(r, (i + 1) * B - 1); j >= l; j--) {
                if (st.size()) {
                    auto it = st.lower_bound({-a[j], INF});
                    if (it != st.end() && abs(a[j] + it->first) < mn) {
                        mn = abs(a[j] + it->first);
                        x = j, y = it->second;
                    }
                    if (it-- != st.begin() && abs(a[j] + it->first) < mn) {
                        mn = abs(a[j] + it->first);
                        x = j, y = it->second;
                    }
                }
                if (tmp.size()) {
                    auto it = tmp.lower_bound({-a[j], INF});
                    if (it != tmp.end() && abs(a[j] + it->first) < mn) {
                        mn = abs(a[j] + it->first);
                        x = j, y = it->second;
                    }
                    if (it-- != tmp.begin() && abs(a[j] + it->first) < mn) {
                        mn = abs(a[j] + it->first);
                        x = j, y = it->second;
                    }
                }
                tmp.insert({a[j], j});
            }
            ans[ind] = {x, y};
            tie(mn, x, y) = restore;
        }
    }
    for (int i = 0; i < q; i++) {
        auto [l, r] = ans[i];
        if (l > r) {
            swap(l, r);
        }
        cout << l + 1 << " " << r + 1 << endl;
    }





    return 0;
}
