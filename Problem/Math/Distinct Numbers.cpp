//https://www.codechef.com/problems/DISTNUMS
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

long long modPow(long long a, long long y, long long m) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<pair<int, int>> f;
        int m = n;
        for (int i = 2; i <= sqrt(n); i++) {
            if (m % i == 0) {
                int ct = 0;
                while (m % i == 0) {
                    m /= i;
                    ct++;
                }
                f.push_back(make_pair(i, ct));
            }
        }
        if (m > 1) {
            f.push_back(make_pair(m, 1));
        }
        long long ans = 1, smaller = 1;
        for (int i = 0; i < f.size(); i++) {
            long long p = f[i].first, e = f[i].second;
            ans = ans * (modPow(p, e * modPow(2, k, M - 1) % (M - 1) + 1 - e + (M - 1), M) % M - 1 + M) % M * modPow(p - 1, M - 2, M) % M;
        }
        cout << ans * n % M << endl;

    }
    return 0;
}
