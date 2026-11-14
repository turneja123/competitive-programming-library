//https://codeforces.com/gym/105493/problem/C
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e5 + 5;


int main() {
    int n;
    cin >> n;
    vector<pair<ll, ll>> a(n);
    set<pair<ll, ll>> st;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        st.insert({x, y});
        a[i] = {x, y};
    }
    if (st.size() != n) {
        cout << "NO";
        return 0;
    }
    if (n == 1) {
        cout << "YES" << endl;
        cout << "1 0" << endl;
        cout << "0 1" << endl;
        return 0;
    }
    pair<ll, ll> Y = {a[1].first - a[0].first, a[1].second - a[0].second};
    for (int i = 1; i < n - 1; i++) {
        pair<ll, ll> cur = {a[i + 1].first - a[i].first, a[i + 1].second - a[i].second};

        ll cross = Y.first * cur.second - Y.second * cur.first;
        if (cross > 0) {
            Y = cur;
        }
    }
    for (int i = 0; i < n; i++) {
        a[i] = {a[i].first * Y.second - a[i].second * Y.first, a[i].first * Y.first + a[i].second * Y.second};
    }
    for (int i = 0; i < n - 1; i++) {
        if (a[i].first > a[i + 1].first || (a[i].first == a[i + 1].first && a[i].second >= a[i + 1].second)) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES" << endl;
    cout << Y.second << " " << -Y.first << endl;
    cout << Y.first << " " << Y.second;


    return 0;
}
