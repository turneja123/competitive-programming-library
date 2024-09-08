//https://codeforces.com/contest/1279/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 998244353;

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

int ct[N];
vector<int> v[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int a;
            cin >> a;
            ct[a]++;
            v[i].push_back(a);
        }
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long cur = 0;
        for (int j = 0; j < v[i].size(); j++) {
            cur += modPow(v[i].size(), M - 2) * modPow(n, M - 2) % M * ct[v[i][j]];
        }
        cur = cur % M * modPow(n, M - 2) % M;
        ans += cur;
    }
    cout << ans % M;

    return 0;
}
