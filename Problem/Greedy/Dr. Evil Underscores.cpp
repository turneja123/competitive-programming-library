//https://codeforces.com/contest/1285/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

vector<int> a;

int calc(vector<int> a, int k) {
    if (k < 0) {
        return 0;
    }
    vector<int> l, r;
    for (int i = 0; i < a.size(); i++) {
        int c = a[i] & (1 << k);
        if (!c) {
            l.push_back(a[i]);
        } else {
            r.push_back(a[i]);
        }
    }
    if (l.empty()) {
        return calc(r, k - 1);
    }
    if (r.empty()) {
        return calc(l, k - 1);
    }
    return (1 << k) + min(calc(l, k - 1), calc(r, k - 1));

}

int main() {
    IOS;
    int n;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << calc(a, 30);

    return 0;
}
