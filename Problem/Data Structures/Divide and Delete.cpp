//https://dmoj.ca/problem/yac9p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int K = 20;

int a[N];
int table[K][N];
int lpf[N];
bool is_prime[N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = lpf[a[i - 1]] - (i - 1);
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = max(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    return max(table[k][l], table[k][r - (1 << k) + 1]);
}

void sieve(int n){
    for (int i = 1; i < n; i++) {
        lpf[i] = 1;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            lpf[i] = i;
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                lpf[j] = i;
            }
        }
    }
}

int main() {
    IOS;
    sieve(N);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(n);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int l = i, r = n - 1, spl = i - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int x = query(i, mid) + i;
            if (x <= 1) {
                spl = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ans += spl - i + 1;
    }
    cout << ans;
    return 0;
}
