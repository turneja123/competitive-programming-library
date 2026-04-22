//https://codeforces.com/contest/2225/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

static const u32 MOD = 1e9 + 7;


const u32 B = 911382323;
const u32 B2 = 972663749;

u32 pw[N], h[N], rh[N];
u32 pw2[N], h2[N], rh2[N];

static inline u32 fastmod_u64(u64 x) {
    static const u64 inv = (u64)((u128(1) << 64) / MOD);
    u64 q = (u64)((u128)x * inv >> 64);
    u64 r = x - q * (u64)MOD;
    if (r >= MOD) r -= MOD;
    if (r >= MOD) r -= MOD;
    return (u32)r;
}

static inline u32 mul_small(u32 a, u32 b) {
    return fastmod_u64((u64)a * b);
}

inline u32 get_hash(u32 *a, int l, int r) {
    u32 ans = a[r + 1] + MOD - mul_small(a[l], pw[r - l + 1]);
    if (ans >= MOD) ans -= MOD;
    return ans;
}

inline u32 get_hash2(u32 *a, int l, int r) {
    u32 ans = a[r + 1] + MOD - mul_small(a[l], pw2[r - l + 1]);
    if (ans >= MOD) ans -= MOD;
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, L, k;
        cin >> n >> L >> k;
        string s;
        cin >> s;
        if ((ll)L * k > n) {
            cout << "NO" << endl;
            continue;
        }
        cout << "YES" << endl;
        if (k == 1) {
            cout << s << endl;
            continue;
        }
        pw[0] = 1;
        pw2[0] = 1;
        h[0] = 0;
        h2[0] = 0;
        for (int i = 0; i < n; i++) {
            pw[i + 1] = mul_small(pw[i], B);
            h[i + 1] = mul_small(h[i], B) + (s[i] - 'a' + 1);
            if (h[i + 1] >= MOD) {
                h[i + 1] -= MOD;
            }
            pw2[i + 1] = mul_small(pw2[i], B2);
            h2[i + 1] = mul_small(h2[i], B2) + (s[i] - 'a' + 1);
            if (h2[i + 1] >= MOD) {
                h2[i + 1] -= MOD;
            }
        }

        vector<pair<int, int>> options;
        for (int i = 0; i <= n - L; i++) {
            if (i != 0 && i < L) {
                continue;
            }
            int ct = i / L;
            if (ct >= k - 1) {
                options.push_back({i, n - 1});
                continue;
            }
            int l = i + L - 1, r = n - 1, spl = -1;
            while (l <= r) {

                int mid = (l + r) / 2;

                if (ct + 1 + (n - 1 - mid) / L >= k) {
                    spl = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            if (spl != -1) {
                options.push_back({i, spl});
            }
        }
        pair<int, int> ans = options[0];
        for (int i = 1; i < options.size(); i++) {
            auto [xl, xr] = ans;
            auto [yl, yr] = options[i];

            int sz = min(xr - xl + 1, yr - yl + 1);

            int l = 0, r = sz - 1, spl = -1;
            while (l <= r) {
                int mid = (l + r) / 2;

                if (get_hash(h, xl, xl + mid) != get_hash(h, yl, yl + mid) || get_hash2(h2, xl, xl + mid) != get_hash2(h2, yl, yl + mid)) {
                    spl = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (spl == -1) {
                if (yr - yl > xr - xl) {
                    ans = options[i];
                }
                continue;
            }
            if (s[yl + spl] > s[xl + spl]) {
                ans = options[i];
            }
        }
        string f = s.substr(ans.first, ans.second - ans.first + 1);
        cout << f << endl;
    }


    return 0;
}
