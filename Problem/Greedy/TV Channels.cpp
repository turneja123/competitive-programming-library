//bbc15
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

vector<int> v[N];
int ptr[N];

int main() {
    IOS;
    int n, t;
    cin >> n >> t;
    set<pair<int, int>> st;
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        for (int j = 0; j < s; j++) {
            int x;
            cin >> x;
            v[i].push_back(x);
        }
        sort(v[i].begin(), v[i].end());
        v[i].push_back(N);
        st.insert({v[i][0], i});

    }
    int ban = -1, cur = 1, ans = 0;
    while (cur <= t) {
        while (st.begin()->first < cur) {
            int j = st.begin()->second;
            ptr[j]++;
            st.erase(st.begin());
            st.insert({v[j][ptr[j]], j});
        }
        int fi = -1, se = -1;
        auto it = st.rbegin();
        while (it != st.rend() && (fi == -1 || se == -1)) {
            if (it->second != ban) {
                if (fi == -1) {
                    fi = it->second;
                } else {
                    se = it->second;
                }
            }
            it++;
        }
        if (se == -1 || v[fi][ptr[fi]] != v[se][ptr[se]]) {
            ban = fi;
        } else {
            ban = -1;
        }
        if (v[fi][ptr[fi]] == N) {
            break;
        }
        cur = v[fi][ptr[fi]] + 1;
        ans++;
    }
    cout << ans;
    return 0;
}
