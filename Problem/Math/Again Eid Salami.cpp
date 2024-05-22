//https://www.spoj.com/problems/EIDSALAMI2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int M = 1e9 + 7;

struct chash {
    long long operator()(pair<int, int> x) const { return (long long)x.first* 1000005 + x.second; }
};
gp_hash_table<pair<int, int>, int, chash> mp;

int calc(int n, int m) {
    if (n == 1 && m == 1) {
        return 1;
    }
    if (m == 0 || m >= n) {
        return 0;
    }
    auto it = mp.find(make_pair(n, m));
    if (it != mp.end()) {
        return it->second;
    }
    return mp[make_pair(n, m)] = (calc(n - m, m) + calc(n - m, m - 1)) % M;
}

int main() {
    IOS;
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int m, n;
        cin >> m >> n;
        cout << "Case " << tt << ": " << calc(m, n) << endl;
    }
    return 0;
}
