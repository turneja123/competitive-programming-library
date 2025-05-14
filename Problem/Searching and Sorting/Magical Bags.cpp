//https://algotester.com/en/ArchiveProblem/DisplayWithFile/71134#mySolutions
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

bool good[N];
vector<int> v[N];

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.second < b.second) {
        return true;
    }
    return false;
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<pair<int, int>> ivals;
    vector<int> v_mn, v_mx;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        int mx = -INF, mn = INF;
        for (int j = 0; j < k; j++) {
            int a;
            cin >> a;
            mx = max(mx, a);
            mn = min(mn, a);
            v[i].push_back(a);
        }
        sort(v[i].begin(), v[i].end());
        v_mn.push_back(mn);
        v_mx.push_back(mx);
        ivals.push_back(make_pair(mn, mx));
    }
    sort(v_mn.begin(), v_mn.end());
    sort(v_mx.begin(), v_mx.end());
    for (int i = 0; i < n; i++) {
        for (int x : v[i]) {
            int mn = v[i].front(), mx = v[i].back();
            good[i] = true;
            int j = upper_bound(v_mx.begin(), v_mx.end(), mn) - v_mx.begin();
            if (j < n && v_mx[j] < x) {
                good[i] = false;
            }
            j = lower_bound(v_mn.begin(), v_mn.end(), mx) - v_mn.begin() - 1;
            if (j >= 0 && v_mn[j] > x) {
                good[i] = false;
            }
            if (good[i]) {
                break;
            }
        }
    }
    vector<pair<int, int>> ivals_good;
    for (int i = 0; i < n; i++) {
        if (good[i]) {
            ivals_good.push_back(ivals[i]);
        }
    }
    sort(ivals_good.begin(), ivals_good.end(), comp);
    int ans = 2 * n, last = -1;
    for (auto [l, r] : ivals_good) {
        if (l > last) {
            ans--;
            last = r;
        }
    }
    cout << ans;


    return 0;
}
