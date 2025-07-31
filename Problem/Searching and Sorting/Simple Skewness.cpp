//https://codeforces.com/contest/626/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

const int N = 2e5 + 5;

int a[N];
long long pref[N];

ld best = 0.0;
tuple<int, int, int> ans;

ld calc(int k, int s, ld med, int n, int L, int R) {
    ld sum = med;
    if (k != 0) {
        sum += (ld)pref[n - 1] - (ld)pref[n - 1 - k];
        sum += (ld)pref[L - 1] - (ld)(L - 1 - k < 0 ? 0 : pref[L - 1 - k]);
    }
    sum /= (ld)s;
    sum -= med;
    if (sum > best) {
        best = sum;
        ans = {L, R, k};
    }
    return sum;
}


void solve(int L, int R, int n) {
    ld med = ((ld)a[L] + (ld)a[R]) / (ld)2.0;
    int l = 0, r = min(L, n - 1 - R);
    while (r - l >= 3) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        ld f1 = calc(m1, R - L + 1 + 2 * m1, med, n, L, R);
        ld f2 = calc(m2, R - L + 1 + 2 * m2, med, n, L, R);

        if (f1 < f2) {
            l = m1 + 1;
        } else {
            r = m2 - 1;
        }
    }
    for (; l <= r; l++) {
        calc(l, R - L + 1 + 2 * l, med, n, L, R);
    }

}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);

    for (int i = 0; i < n; i++) {
        pref[i] = (i == 0 ? 0 : pref[i - 1]) + a[i];
    }
    for (int i = 0; i < n; i++) {
        solve(i, i, n);
        if (i != n - 1) {
            solve(i, i + 1, n);
        }
    }
    vector<int> out;
    auto [l, r, k] = ans;
    out.push_back(a[l]);
    if (r != l) {
        out.push_back(a[r]);
    }
    for (int i = 0; i < k; i++) {
        out.push_back(a[n - 1 - i]);
        out.push_back(a[l - 1 - i]);
    }
    cout << out.size() << endl;
    for (int x : out) {
        cout << x << " ";
    }

    return 0;
}
