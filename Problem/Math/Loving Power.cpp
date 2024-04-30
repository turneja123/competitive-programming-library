//https://www.spoj.com/problems/LOVINGPW/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
gp_hash_table<long long, long long> mp;

long long calc(long long n) {
    if (n == 0) {
        return 0;
    }
    if (mp.find(n) != mp.end()) {
        return mp[n];
    }
    if (n % 2 == 0) {
        return mp[n] = (calc(n / 2) + calc(n / 2 - 1) + n / 2) % M;
    }
    return mp[n] = (calc(n / 2) * 2 + n / 2 + 1) % M;
}

int main() {
    IOS;
    int t; long long n;
    cin >> t;
    while (t--) {
        cin >> n;
        cout << calc(n) << endl;
    }
    return 0;
}
