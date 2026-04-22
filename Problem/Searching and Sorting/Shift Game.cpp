//https://www.codechef.com/problems/SHFTGAME
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e12 + 1;

vector<pair<ll, ll>> calc(string &a, int f) {
    int n = a.size();
    vector<pair<ll, ll>> ans;
    for (int i = 0; i < n;) {
        int j = i;
        while (i < n && a[j] == a[i]) {
            i++;
        }
        ans.push_back({i - j, (f && a[j] == '1' ? i - j : 0)});
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        string a, b;
        cin >> a >> b;
        int f = a[0] != b[0];



        int oka = 1, okb = 1;
        int i = 0;
        while (i < n && a[0] == a[i]) {
            i++;
        }
        pair<ll, ll> fa;
        if (i == n) {
            fa = {INF, (a[0] == '1' ? INF : 0)};
            oka = 0;
        } else {
            fa = {i, (a[0] == '1' ? i : 0)};
        }
        vector<pair<ll, ll>> ba;
        vector<ll> prefa;
        vector<ll> prefas;

        if (oka) {
            rotate(a.begin(), a.begin() + i, a.end());
            ba = calc(a, 1);
            prefa.resize(ba.size());
            prefas.resize(ba.size());
            for (int i = 0; i < ba.size(); i++) {
                if (i != 0) {
                    prefa[i] += prefa[i - 1];
                    prefas[i] += prefas[i - 1];
                }
                prefa[i] += ba[i].first;
                prefas[i] += ba[i].second;
            }

        }

        i = 0;
        while (i < n && b[0] == b[i]) {
            i++;
        }
        pair<ll, ll> fb;
        if (i == n) {
            fb = {INF, 0};
            okb = 0;
        } else {
            fb = {i, 0};
        }
        vector<pair<ll, ll>> bb;
        vector<ll> prefb;
        vector<ll> prefbs;
        if (okb) {
            rotate(b.begin(), b.begin() + i, b.end());
            bb = calc(b, 0);
            prefb.resize(bb.size());
            prefbs.resize(bb.size());
            for (int i = 0; i < bb.size(); i++) {
                if (i != 0) {
                    prefb[i] += prefb[i - 1];
                    prefbs[i] += prefbs[i - 1];
                }
                prefb[i] += bb[i].first;
                prefbs[i] += bb[i].second;
            }

        }

        if (f) {
            swap(fa, fb);
            swap(ba, bb);
            swap(prefa, prefb);
            swap(prefas, prefbs);
        }

        for (int i = 0; i < q; i++) {
            ll k;
            cin >> k;
            ll ans = 0;
            if (fa.first >= k) {
                ans += (fa.second ? k : 0);
                cout << ans << " ";
                continue;
            } else {
                ans += fa.second;
                k -= fa.first;
            }
            if (fb.first >= k) {
                ans += (fb.second ? k : 0);
                cout << ans << " ";
                continue;
            } else {
                ans += fb.second;
                k -= fb.first;
            }

            ll l = 0, r = 1e12, take = 0, add = 0;

            pair<ll, ll> FA = ba[0], FB = bb[0];

            while (l <= r) {
                ll mid = (l + r) / 2;

                ll cur = mid / ba.size() * prefa.back() + mid / bb.size() * prefb.back();
                ll curs = mid / ba.size() * prefas.back() + mid / bb.size() * prefbs.back();

                int JA = mid % ba.size(), JB = mid % bb.size();

                if (JA) {
                    cur += prefa[JA - 1];
                    curs += prefas[JA - 1];
                }
                if (JB) {
                    cur += prefb[JB - 1];
                    curs += prefbs[JB - 1];
                }
                if (cur <= k) {
                    take = cur;
                    add = curs;
                    l = mid + 1;

                    FA = ba[JA];
                    FB = bb[JB];
                } else {
                    r = mid - 1;
                }
            }
            ans += add;
            k -= take;

            if (FA.first >= k) {
                ans += (FA.second ? k : 0);
                cout << ans << " ";
                continue;
            } else {
                k -= FA.first;
                ans += FA.second;
            }
            if (FB.first >= k) {
                ans += (FB.second ? k : 0);
                cout << ans << " ";
                continue;
            } else {
                k -= FB.first;
                ans += FB.second;
            }
            cout << ans << " ";

        }
        cout << endl;
    }

    return 0;
}
