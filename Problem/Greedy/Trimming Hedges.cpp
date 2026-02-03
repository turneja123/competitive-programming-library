//https://ocpc2026w.eolymp.space/en/compete/ig3v7lohgt0vd43nv48bk2lb4o/problem/12
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll unsigned long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 998244353;

int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> a(n), sorted(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sorted = a;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    if (sorted.size() == 1) {
        cout << 0;
        return 0;
    }
    vector<int> x;
    for (int i = 0; i < n; i++) {
        if (a[i] != sorted[0]) {
            x.push_back(i);
        }
    }
    int ok = 0;
    if (x.size() == 1) {
        ok = 1;
    } else {
        int g = x[1] - x[0];
        for (int i = 2; i < x.size(); i++) {
            g = __gcd(g, x[i] - x[i - 1]);
        }
        if (g > 1) {
            ok = 1;
        }
    }
    cout << 2 - ok;


    return 0;
}
