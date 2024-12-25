//https://atcoder.jp/contests/dp/tasks/dp_j
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e7 + 5;

long double dp[N];

long double calc(vector<int> &a, int n) {
    if (a[0] == n) {
        return 0.0;
    }
    int h = (a[0] + 301 * a[1] + 301 * 301 * a[2]);
    if (dp[h] > 0.0) {
        return dp[h];
    }
    long double cur = 1.0;
    for (int i = 1; i <= 3; i++) {
        if (a[i] > 0) {
            long double p = (long double)a[i] / (long double)n;
            a[i]--;
            a[i - 1]++;
            cur += p * calc(a, n);
            a[i]++;
            a[i - 1]--;
        }
    }
    cur = cur / ((long double)1.0 - (long double)a[0] / (long double)n);
    return dp[h] = cur;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    vector<int> freq(4, 0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        freq[a]++;
    }
    cout << calc(freq, n);
    return 0;
}
