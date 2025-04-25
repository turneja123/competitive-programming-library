//https://www.spoj.com/problems/ZQUERY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e4 + 5;
const int B = 200;

int a[N];
int pref[N];
int ptr[N];

int freq[N];
int freq_b[N];
int ans[N];

vector<int> pos[2 * N];
tuple<int, int, int> queries[N];

bool comp(tuple<int, int, int> &a, tuple<int, int, int> &b) {
    if (get<0>(a) / B != get<0>(b) / B) {
        return get<0>(a) / B < get<0>(b) / B;
    }
    return get<1>(a) < get<1>(b);
}


void add(int x, int y) {
    freq[x] += y;
    freq_b[x / B] += y;
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    pos[N].push_back(0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
        ptr[i] = pos[pref[i] + N].size();
        pos[pref[i] + N].push_back(i);
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        queries[i] = make_tuple(l, r, i);
    }
    sort(queries, queries + q, comp);

    int l = 1, r = 0;
    for (int i = 0; i < q; i++) {
        auto [lq, rq, ind]  = queries[i];
        while (r < rq) {
            r++;
            int val = pref[r] + N;
            int j = lower_bound(pos[val].begin(), pos[val].end(), l - 1) - pos[val].begin();
            if (j < ptr[r] - 1) {
                add(pos[val][ptr[r] - 1] - pos[val][j], -1);
            }
            if (j < ptr[r]) {
                add(pos[val][ptr[r]] - pos[val][j], 1);
            }
        }
        while (r > rq) {
            int val = pref[r] + N;
            int j = lower_bound(pos[val].begin(), pos[val].end(), l - 1) - pos[val].begin();
            if (j < ptr[r]) {
                add(pos[val][ptr[r]] - pos[val][j], -1);
            }
            if (j < ptr[r] - 1) {
                add(pos[val][ptr[r] - 1] - pos[val][j], 1);
            }
            r--;
        }
        while (l < lq) {
            int val = pref[l - 1] + N;
            int j = upper_bound(pos[val].begin(), pos[val].end(), r) - pos[val].begin() - 1;
            if (ptr[l - 1] < j) {
                add(pos[val][j] - pos[val][ptr[l - 1]], -1);
            }
            if (ptr[l - 1] + 1 < j) {
                add(pos[val][j] - pos[val][ptr[l - 1] + 1], 1);
            }
            l++;
        }
        while (l > lq) {
            l--;
            int val = pref[l - 1] + N;
            int j = upper_bound(pos[val].begin(), pos[val].end(), r) - pos[val].begin() - 1;
            if (ptr[l - 1] < j) {
                add(pos[val][j] - pos[val][ptr[l - 1]], 1);
            }
            if (ptr[l - 1] + 1 < j) {
                add(pos[val][j] - pos[val][ptr[l - 1] + 1], -1);
            }
        }
        int mx = -1;
        for (int i = 0; i * B <= n; i++) {
            if (freq_b[i]) {
                mx = i;
            }
        }
        if (mx != -1) {
            for (int i = mx * B; i <= min(n, (mx + 1) * B); i++) {
                if (freq[i]) {
                    ans[ind] = i;
                }
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
