//https://codeforces.com/contest/2118/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e7;

pair<int, int> a[N];
pair<int, int> mid;

bool comp(pair<int, int> &a, pair<int, int> &b) {
    int d1 = max(a.first, a.second);
    int d2 = max(b.first, b.second);
    if (d1 != d2) {
        return d1 < d2;
    }
    d1 = a.first + a.second;
    d2 = b.first + b.second;
    if (d1 != d2) {
        return d1 < d2;
    }
    if (a.first != b.first) {
        return a.first < b.first;
    }
    return a.second < b.second;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int p = 0;
        for (int i = 0; i <= n / 2; i++) {
            for (int j = 0; j <= m / 2; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                a[p++] = {i, j};
            }
        }
        sort(a, a + p, comp);
        pair<int, int> mid = {n / 2, m / 2};
        cout << mid.first + 1 << " " << mid.second + 1 << endl;
        for (int i = 0; i < p; i++) {
            cout << mid.first + 1 + a[i].first << " " << mid.second + 1 + a[i].second << endl;
            if (a[i].second != 0) {
                cout << mid.first + 1 + a[i].first << " " << mid.second + 1 - a[i].second << endl;
            }
            if (a[i].first != 0) {
                cout << mid.first + 1 - a[i].first << " " << mid.second + 1 + a[i].second << endl;
            }
            if (a[i].second != 0 && a[i].first != 0) {
                cout << mid.first + 1 - a[i].first << " " << mid.second + 1 - a[i].second << endl;
            }
        }
    }

    return 0;
}
