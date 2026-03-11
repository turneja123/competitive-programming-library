//https://www.spoj.com/problems/UCV2013F/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

ll M;

using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
u64 inv;

static inline u32 fastmod_u64(u64 x) {
    u64 q = (u64)((u128)x * inv >> 64);
    u64 r = x - q * (u64)M;
    if (r >= M) r -= M;
    if (r >= M) r -= M;
    return (u32)r;
}

static inline u32 mul_small(u32 a, u32 b) {
    return fastmod_u64((u64)a * b);
}

vector<vector<long long>> mul(vector<vector<long long>> base, vector<vector<long long>> mat) {
    int n = base.size();
    int m = mat[0].size();

    vector<vector<long long>> ret;
    ret.assign(n, vector<long long>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int p = 0; p < n; p++) {
                ret[i][j] += mul_small(base[i][p], mat[p][j]);
                while (ret[i][j] >= M) {
                    ret[i][j] -= M;
                }
            }
        }
    }
    return ret;
}

vector<vector<long long>> expo(vector<vector<long long>> base, int n, ll k) {
    vector<vector<long long>> ans;
    ans.assign(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = (i == j);
        }
    }
    while (k) {
        if (k % 2 == 1) {
            ans = mul(ans, base);
        }
        base = mul(base, base);
        k /= 2;
    }
    return ans;
}

int main() {
    IOS;
    int m; ll y;
    cin >> m >> y >> M;
    while (m) {
        inv = (u64)((u128(1) << 64) / M);
        vector<vector<ll>> v(m, vector<ll>(1, 0));
        for (int i = 0; i < m; i++) {
            cin >> v[i][0];
        }
        vector<vector<ll>> mat(m, vector<ll>(m, 0));
        for (int i = 0; i < m; i++) {
            mat[0][i] = 1;
        }
        for (int i = 1; i < m; i++) {
            mat[i][i - 1] = 1;
        }
        vector<vector<ll>> prod = mul(expo(mat, m, y), v);
        ll ans = 0;
        for (int i = 0; i < m; i++) {
            ans = (ans + prod[i][0]) % M;
        }
        cout << ans << endl;

        cin >> m >> y >> M;
    }

    return 0;
}
