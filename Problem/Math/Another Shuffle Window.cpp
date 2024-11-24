//https://atcoder.jp/contests/abc380/tasks/abc380_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e6 + 5;
const long long M = 998244353;

int a[N];
long long fact[N];

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

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> tr;

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % M;
    }
    if (n == k) {
        long long ans = (long long)n * (n - 1) % M * modPow(4, M - 2) % M;
        cout << ans;
        return 0;
    }
    long long tot = 0, totinv = 0, inv = 0;
    for (int i = 0; i < n; i++) {
        totinv += tr.size() - tr.order_of_key(a[i]);
        tr.insert(a[i]);
    }
    tr.clear();
    for (int i = 0; i < k; i++) {
        inv += tr.size() - tr.order_of_key(a[i]);
        tr.insert(a[i]);
    }
    tot += (long long)k * (k - 1) % M * fact[k] % M * modPow(4, M - 2) % M + (totinv - inv) % M * fact[k] % M;
    for (int i = 1; i <= n - k; i++) {
        inv -= tr.order_of_key(a[i - 1]);
        tr.erase(a[i - 1]);
        inv += tr.size() - tr.order_of_key(a[k + i - 1]);
        tr.insert(a[k + i - 1]);
        tot += (long long)k * (k - 1) % M * fact[k] % M * modPow(4, M - 2) % M + (totinv - inv) % M * fact[k] % M;
    }
    tot = tot % M * modPow(fact[k] * (n - k + 1) % M, M - 2) % M;
    cout << tot;
    return 0;
}
