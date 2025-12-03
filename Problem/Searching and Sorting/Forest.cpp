//https://atcoder.jp/contests/arc211/tasks/arc211_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

int main() {
    IOS;
    int n;
    cin >> n;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<tuple<char, int, int>> v;
    for (int i = 0; i < n;) {
        int mx = 0, ct = 0;
        char last = s[i];
        while (i < n && s[i] == last) {
            if (a[i] > mx) {
                mx = a[i];
                ct = 1;
            } else if (a[i] == mx) {
                ct++;
            }
            i++;
        }
        v.push_back(make_tuple(last, mx, ct));
    }
    ll sum = 0;
    int m = 0;
    for (int i = 0; i < v.size(); i++) {
        if (get<0>(v[i]) == '.') {
            sum += get<1>(v[i]);
            m++;
        }
    }

    ll ans = 0; ll best = 0;
    for (int i = 0; i < v.size(); i++) {
        if (get<0>(v[i]) == '#') {
            continue;
        }
        if (i + 2 >= v.size()) {
            break;
        }
        int mx = max({get<1>(v[i]), get<1>(v[i + 1]), get<1>(v[i + 2])});

        ll gain = sum + (ll)(m - 2) * mx;
        best = max(best, gain);
    }
    for (int i = 0; i < v.size(); i++) {
        if (get<0>(v[i]) == '#') {
            continue;
        }
        if (i + 2 >= v.size()) {
            break;
        }
        int mx = max({get<1>(v[i]), get<1>(v[i + 1]), get<1>(v[i + 2])});

        ll gain = sum + (ll)(m - 2) * mx;
        if (gain == best) {
            ans += (ll)get<2>(v[i]) * get<2>(v[i + 2]);
        }
    }
    cout << ans;


    return 0;
}
