//https://www.spoj.com/problems/VZLA2019G/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

long long pw(long long a, int n) {
    long long p = 1;
    for (int i = 0; i < n; i++) {
        p *= a;
    }
    return p;
}

vector<long long> x;

void calc(int i, int ct, int n, vector<int> &v) {
    if (ct > n) {
        return;
    }
    if (v[0] == n) {
        return;
    }
    if (i == 10 && ct != n) {
        return;
    }
    if (i == 10 && ct == n) {
        long long a = 0;
        for (int i = 0; i <= 9; i++) {
            a += v[i] * pow(i, n);
        }
        long long tmp = a;
        vector<int> t(10, 0);
        while (a > 0) {
            t[a % 10]++;
            a /= 10;
        }
        for (int i = 0; i <= 9; i++) {
            if (t[i] != v[i]) {
                return;
            }
        }
        x.push_back(tmp);

        return;
    }
    for (int j = 0; j <= n; j++) {
        v[i] = j;
        calc(i + 1, ct + j, n, v);
        v[i] = 0;
    }
}

int main() {
    IOS;
    for (int n = 1; n <= 10; n++) {
        vector<int> v(10, 0);
        calc(0, 0, n, v);
    }
    x.push_back(0);
    sort(x.begin(), x.end());
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        long long a;
        cin >> a;
        cout << "Case #" << tt << ": " << x[lower_bound(x.begin(), x.end(), a) - x.begin()] << endl;
    }
    return 0;
}
