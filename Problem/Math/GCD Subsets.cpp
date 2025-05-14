//https://cses.fi/problemset/task/3161/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

int freq[N];
int sum[N];
long long ans[N];

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
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        freq[a]++;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            sum[i] += freq[j];
        }
        ans[i] = modPow(2, sum[i]) - 1;
    }
    for (int i = n; i > 0; i--) {
        for (int j = 2 * i; j <= n; j += i) {
            ans[i] = (ans[i] - ans[j] + M) % M;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
