//https://www.spoj.com/problems/FIB64/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long M;

long long mulmod(long long x, long long y, long long m){
    long long k = (x * (long double)y / m) + 0.5, r = x * y - k * m;
    return r < 0 ? r + m : r;
}

vector<vector<long long>> ret(2, vector<long long>(2, 0));

void mul(vector<vector<long long>> &base, vector<vector<long long>> &mat) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            ret[i][j] = (mulmod(base[i][0], mat[0][j], M) + mulmod(base[i][1], mat[1][j], M));
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            base[i][j] = ret[i][j];
        }
    }
}

void expo(vector<vector<long long>> &base, int n, long long k) {
    vector<vector<long long>> ans;
    ans.assign(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = (i == j);
        }
    }
    if (k < 0) {
        cout << 0 << endl;
        return;
    }
    while (k) {
        if (k & 1) {
            mul(ans, base);
        }
        mul(base, base);
        k /= 2;
    }
    cout << ans[0][0] % M << endl;
}

int main() {
    IOS;
    for (int t = 0; t < 130000; t++) {
        long long n;
        cin >> n >> M;
        vector<vector<long long>> m{{1, 1}, {1, 0}};
        expo(m, 2, n - 1);
    }

    return 0;
}
