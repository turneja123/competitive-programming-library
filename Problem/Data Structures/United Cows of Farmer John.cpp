//solution for http://usaco.org/index.php?page=viewproblem2&cpid=1137
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int freq[N];
int sz;
vector<int> pos[N];

bool compare(pair<int, int> p1, pair<int, int> p2) {
    int block1 = p1.first / sz;
    int block2 = p2.first / sz;
    if (block1 != block2) {
        return block1 < block2;
    }
    int r1 = p1.second;
    int r2 = p2.second;
    return r1 < r2;
}

int main() {
    IOS;
    int n;
    cin >> n;
    sz = sqrt(n - 1);
    if (sz * sz != n - 1) {
        sz++;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    pair<int, int> queries[n - 1];
    for (int i = 0; i < n - 1; i++) {
        int ind = lower_bound(pos[a[i]].begin(), pos[a[i]].end(), i) - pos[a[i]].begin();
        int r;
        if (ind + 1 == pos[a[i]].size()) {
            r = n - 1;
        } else {
            r = pos[a[i]][ind + 1];
        }
        queries[i] = {i, r};
    }
    sort(queries, queries + n - 1, compare);
    int l = 0;
    int r = -1;
    ll ct = 0;
    ll ans = 0;
    for (int i = 0; i < n - 1; i++) {
        int lcur = queries[i].first;
        int rcur = queries[i].second;
        while (r < rcur) {
            r++;
            freq[a[r]]++;
            if (freq[a[r]] == 1) {
                ct++;
            }
        }
        while (r > rcur) {
            freq[a[r]]--;
            if (freq[a[r]] == 0) {
                ct--;
            }
            r--;
        }
        while (l < lcur) {
            freq[a[l]]--;
            if (freq[a[l]] == 0) {
                ct--;
            }
            l++;
        }
        while (l > lcur) {
            l--;
            freq[a[l]]++;
            if (freq[a[l]] == 1) {
                ct++;
            }
        }
        ans += ct - 1;
    }
    cout << ans << endl;
    return 0;
}
