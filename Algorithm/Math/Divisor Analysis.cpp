//https://cses.fi/problemset/task/2182/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

long long div_ct(vector<pair<long long, int>> &f) {
    long long prod = 1;
    for (int i = 0; i < f.size(); i++) {
        prod = prod * (f[i].second + 1) % M;
    }
    return prod;
}

long long div_sum(vector<pair<long long, int>> &f, int x) {
    long long prod = 1;
    for (int i = 0; i < f.size(); i++) {
        prod = prod * (modPow(f[i].first, (f[i].second + 1) * x) - 1) % M * modPow(modPow(f[i].first, x) - 1, M - 2) % M;
    }
    return prod;
}

long long div_prod(vector<pair<long long, int>> &f) {
    long long prod = 1, n = 1, sq = 1;
    for (int i = 0; i < f.size(); i++) {
        prod = prod * (f[i].second + 1) % ((M - 1) * 2);
        n = n * modPow(f[i].first, f[i].second) % M;
        sq = sq * modPow(f[i].first, f[i].second / 2) % M;
    }
    long long ans = modPow(n, prod / 2);
    if (prod % 2 == 1) {
        ans = ans * sq % M;
    }
    return ans;
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<pair<long long, int>> f;
    for (int i = 0; i < n; i++) {
        int p, e;
        cin >> p >> e;
        f.push_back(make_pair(p, e));
    }
    cout << div_ct(f) << " " << div_sum(f, 1) << " " << div_prod(f);

    return 0;
}
