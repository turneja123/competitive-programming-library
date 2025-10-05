//https://codeforces.com/contest/364/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

mt19937 gen(1707);
ll a[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n, greater<ll>());
    ll ans = 1;
    set<ll> skip;
    for (int rep = 0; rep < 13; rep++) {
        int j = gen() % n;
        vector<ll> mp(n);
        vector<pair<ll, int>> freqs(n);
        for (int i = 0; i < n; i++) {
            mp[i] = __gcd(a[i], a[j]);
        }
        sort(mp.begin(), mp.end());
        ll last = -1; int ct = 0, m = 0;
        for (int i = 0; i < n; i++) {
            if (last != mp[i]) {
                if (ct != 0) {
                    freqs[m++] = {last, ct};
                }
                last = mp[i];
                ct = 1;
            } else {
                ct++;
            }
        }
        freqs[m++] = {last, ct};
        for (int i = m - 1; i >= 0; i--) {
            if (freqs[i].first <= ans) {
                break;
            }
            int ct = freqs[i].second;
            for (int j = i + 1; j < m; j++) {
                if (freqs[j].first % freqs[i].first == 0) {
                    ct += freqs[j].second;
                }
            }
            if (ct >= n / 2 + n % 2) {
                ans = freqs[i].first;
            }
        }
    }
    cout << ans;
    return 0;
}
