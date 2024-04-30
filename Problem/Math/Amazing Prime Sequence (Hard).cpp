//https://www.spoj.com/problems/APS2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1111115;

__int128 prime_cnt[N];
__int128 prime_sum[N];
__int128 spf_cnt[N];
__int128 spf_sum[N];
bool flag[N];
const __int128 M = (__int128)1 << 64;

void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

auto udiv = [](const uint64_t& a, const uint32_t& b) -> uint64_t {
    return (double)a / b + 1e-9;
};

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        long long sq = sqrt(n);
        for (int i = 1; i <= sq; i++) {
            prime_cnt[i] = i - 1, prime_sum[i] = (long long)i * (i + 1) / 2 - 1;
            long long m = udiv(n, i);
            spf_cnt[i] = m - 1, spf_sum[i] = (__int128)m * (m + 1) / 2 - 1;
            flag[i] = false;
        }
        __int128 ans = spf_sum[1];
        for (long long i = 2; i <= sq; i++) {
            if (prime_cnt[i] == prime_cnt[i - 1]) {
                continue;
            }
            ans += (__int128)i * (spf_cnt[i] - prime_cnt[i - 1]) - (__int128)i * (spf_sum[i] - prime_sum[i - 1]);
            int k = (i == 2) ? 1 : 2;
            for (int j = i + k; j <= min(sq, n / (i * i)); j += k) {
                if (flag[i]) {
                    continue;
                }
                if (i * j <= sq) {
                    spf_cnt[j] -= spf_cnt[i * j] - prime_cnt[i - 1];
                    spf_sum[j] -= (__int128)i * (spf_sum[i * j] - prime_sum[i - 1]);
                } else {
                    spf_cnt[j] -= prime_cnt[udiv(n, i * j)] - prime_cnt[i - 1];
                    spf_sum[j] -= (__int128)i * (prime_sum[udiv(n, i * j)] - prime_sum[i - 1]);
                }
            }
            if (i * i <= sq) {
                for (int j = i * i; j < min(sq, n / (i * i)); j += i * k) {
                    flag[j] = true;
                }
            }
            __int128 t_cnt = prime_cnt[i - 1], t_sum = prime_sum[i - 1];
            for (int j = sq; j >= i * i - 1; j--) {
                prime_cnt[j] -= prime_cnt[udiv(j, i)] - t_cnt;
                prime_sum[j] -= (__int128)i * (prime_sum[udiv(j, i)] - t_sum);
            }
        }
        print(ans % M);
        putchar('\n');
    }
    return 0;
}
