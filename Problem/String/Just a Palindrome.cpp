//https://www.spoj.com/problems/JUSTAPAL/
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

const u32 B = 911382323;
const u32 B2 = 972663749;

u32 pw[N], h[N], rh[N];
u32 pw2[N], h2[N], rh2[N];

string s;
int n;

vector<int> pos[58];

static const u32 MOD = 1e9 + 7;

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

inline bool chk(int l1, int r1, int l2, int r2) {
    return get_hash(h, l1, r1) == get_hash(rh, n - 1 - r2, n - 1 - l2) && get_hash2(h2, l1, r1) == get_hash2(rh2, n - 1 - r2, n - 1 - l2);
}

int calc(int l, int r, int n) {
    if (l < 0 || r >= n) {
        return 0;
    }
    int L = 0, R = min(l, n - r - 1), ans = 0;
    while (L <= R) {
        int mid = (L + R) / 2;
        if (chk(l - mid, l, r, r + mid)) {
            ans = mid + 1;
            L = mid + 1;
        } else {
            R = mid - 1;
        }
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        cin >> s;
        n = s.size();
        for (int i = 0; i < n; i++) {
            pos[s[i] - 'A'].push_back(i);
        }
        string t = s;
        reverse(t.begin(), t.end());

        pw[0] = 1;
        pw2[0] = 1;
        h[0] = 0;
        rh[0] = 0;
        h2[0] = 0;
        rh2[0] = 0;
        for (int i = 0; i < n; i++) {
            pw[i + 1] = mul_small(pw[i], B);
            h[i + 1] = mul_small(h[i], B) + (s[i] - 'A' + 1);
            if (h[i + 1] >= MOD) {
                h[i + 1] -= MOD;
            }
            rh[i + 1] = mul_small(rh[i], B) + (t[i] - 'A' + 1);
            if (rh[i + 1] >= MOD) {
                rh[i + 1] -= MOD;
            }

            pw2[i + 1] = mul_small(pw2[i], B2);
            h2[i + 1] = mul_small(h2[i], B2) + (s[i] - 'A' + 1);
            if (h2[i + 1] >= MOD) {
                h2[i + 1] -= MOD;
            }
            rh2[i + 1] = mul_small(rh2[i], B2) + (t[i] - 'A' + 1);
            if (rh2[i + 1] >= MOD) {
                rh2[i + 1] -= MOD;
            }
        }

        int best = 0;
        for (int i = 0; i < n; i++) {
            int l = 0, r = min(i, n - 1 - i), ans = 0;

            int L, R;

            auto f = [&](int d) -> void {
                if (L < 0 || R >= n) {
                    return;
                }
                int ans2 = calc(L - 1, R + 1, n);

                if (d == 1 && (s[i] == s[L] || s[i] == s[R])) {
                    best = max(best, R - L + 1 + 2 * ans2);
                }

                int need = s[R] - 'A';
                int first = pos[need][0];
                if (first < L) {
                    best = max(best, R - L + 1 + 2 * min(ans2, L - first - 1));
                }
                int last = pos[need].back();
                if (last > R) {
                    best = max(best, R - L + 1 + 2 * min(ans2, last - R - 1));
                }

                need = s[L] - 'A';
                first = pos[need][0];
                if (first < L) {
                    best = max(best, R - L + 1 + 2 * min(ans2, L - first - 1));
                }
                last = pos[need].back();
                if (last > R) {
                    best = max(best, R - L + 1 + 2 * min(ans2, last - R - 1));
                }

                int L2 = L - 1 - ans2, R2 = R + 1 + ans2;
                if (L2 >= 0 && R2 < n) {

                    vector<char> v{s[L], s[L2], s[R], s[R2]};
                    sort(v.begin(), v.end());
                    if (v[0] == v[1] && v[2] == v[3]) {

                        int ans3 = calc(L2 - 1, R2 + 1, n);
                        best = max(best, R2 - L2 + 1 + 2 * ans3);
                    }
                }
            };

            while (l <= r) {
                int mid = (l + r) / 2;
                if (chk(i - mid, i, i, i + mid)) {
                    ans = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            L = i - ans, R = i + ans;
            best = max(best, R - L + 1);
            L--, R++;
            f(1);

            if (i == n - 1) {
                continue;
            }
            if (s[i] == s[i + 1]) {
                int l = 0, r = min(i, n - 1 - (i + 1)), ans = 0;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    if (chk(i - mid, i, i + 1, i + 1 + mid)) {
                        ans = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                L = i - ans,
                R = i + 1 + ans;
            } else {
                L = i + 1;
                R = i;
            }
            best = max(best, R - L + 1);
            L--, R++;
            f(0);
        }
        cout << best << endl;
        for (int i = 0; i < 58; i++) {
            pos[i].clear();
        }
    }
    return 0;
}
