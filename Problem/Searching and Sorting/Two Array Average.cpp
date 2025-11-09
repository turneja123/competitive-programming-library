//https://cses.fi/problemset/task/3361/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

pair<ld, int> calc(vector<int> &a, ld x) {
    ld best = -1e9, sum = 0; int j = -1;
    for (int i = 0; i < a.size(); i++) {
        sum += (ld)a[i] - x;
        if (sum > best) {
            best = sum;
            j = i;
        }
    }
    return {best, j};
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    ld l = 0, r = 1e9;
    int ja, jb;
    for (int i = 0; i < 60; i++) {
        ld mid = (l + r) / 2.0;
        pair<ld, int> ap = calc(a, mid), bp = calc(b, mid);
        if (ap.first + bp.first >= 0) {
            l = mid;
            ja = ap.second;
            jb = bp.second;
        } else {
            r = mid;
        }
    }
    cout << ja + 1 << " " << jb + 1;


    return 0;
}
