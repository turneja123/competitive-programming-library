//https://atcoder.jp/contests/abc411/tasks/abc411_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 6e5 + 5;
const long long M = 998244353;

pair<int, int> a[N];
long long dp[N];
long long prob[N];

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


int main() {
    IOS;
    long long inv = modPow(6, M - 2);
    int n, m = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            int x;
            cin >> x;
            a[m++] = {x, i};
        }
    }
    int ct = n;
    sort(a, a + m);
    long long prod = 1, ans = 0;
    int j = 0;
    for (int i = 0; i < m;) {
        int cur = a[i].first;
        while (i < m && a[i].first == cur) {
            if (prob[a[i].second] == 0) {
                ct--;
            } else {
                prod = prod * modPow(prob[a[i].second], M - 2) % M;
            }
            prob[a[i].second] = (prob[a[i].second] + inv) % M;
            prod = prod * prob[a[i].second] % M;
            i++;
        }
        if (ct > 0) {
            dp[j] = 0;
        } else {
            dp[j] = prod;
        }
        ans = (ans + (dp[j] - (j == 0 ? 0 : dp[j - 1]) + M) * cur) % M;
        j++;
    }
    cout << ans << endl;
    return 0;
}
