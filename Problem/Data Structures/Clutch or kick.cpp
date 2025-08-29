//https://basecamp.eolymp.com/en/problems/12200
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll INF = -(1e18);

ll a[N];
ll ans[N];
ll pref[N];

ll bestl[N];
ll bestr[N];

void calc(int l, int r, ll s) {
    if (l >= r) {
        return;
    }
    int mid = (l + r) / 2;

    for (int i = l; i <= r; i++) {
        bestl[i] = INF;
        bestr[i] = INF;
    }

    vector<ll> prefr;
    for (int i = mid + 1; i <= r; i++) {
        prefr.push_back(pref[i]);
    }
    sort(prefr.begin(), prefr.end());
    for (int i = mid; i >= l; i--) {
        ll cur = (i == 0 ? 0 : -pref[i - 1]);
        int j = upper_bound(prefr.begin(), prefr.end(), s - cur) - prefr.begin();
        j--;
        if (j != -1) {
            bestl[i] = max(bestl[i], cur + prefr[j]);
        }
    }
    ll p = INF;
    for (int i = l; i <= mid; i++) {
        p = max(p, bestl[i]);
        ans[i] = max(ans[i], p);
    }


    vector<ll> prefl;
    for (int i = l; i <= mid; i++) {
        ll cur = (i == 0 ? 0 : -pref[i - 1]);

        prefl.push_back(cur);
    }
    sort(prefl.begin(), prefl.end());
    for (int i = mid + 1; i <= r; i++) {
        ll cur = pref[i];
        int j = upper_bound(prefl.begin(), prefl.end(), s - cur) - prefl.begin();
        j--;
        if (j != -1) {
            bestr[i] = max(bestr[i], cur + prefl[j]);
        }
    }
    p = INF;
    for (int i = r; i >= mid + 1; i--) {
        p = max(p, bestr[i]);
        ans[i] = max(ans[i], p);
    }


    calc(l, mid, s);
    calc(mid + 1, r, s);
    return;

}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, s;
        cin >> n >> s;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] <= s) {
                ans[i] = a[i];
            } else {
                ans[i] = INF;
            }
            pref[i] = (i == 0 ? 0 : pref[i - 1]) + a[i];
        }
        calc(0, n - 1, s);
        for (int i = 0; i < n; i++) {
            if (ans[i] != INF) {
                cout << ans[i] << " ";
            } else {
                cout << 'x' << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
