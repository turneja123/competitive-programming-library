//https://atcoder.jp/contests/abc368/tasks/abc368_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> a;

int main() {
    IOS;
    int n;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long t = 0;
    for (int i = 0; i < n; i++) {
        long long l = t + 1, r = 1e18, nx = l;
        while (l <= r) {
            long long mid = (l + r) / 2;
            long long ct = mid - t + (mid / 3 - t / 3) * 2;
            if (ct >= a[i]) {
                r = mid - 1;
                nx = mid;
            } else {
                l = mid + 1;
            }
        }
        t = nx;
    }
    cout << t;

    return 0;
}
