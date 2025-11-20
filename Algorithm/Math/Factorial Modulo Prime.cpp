//https://www.spoj.com/problems/FACTMODP/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;
using ll = long long;
using cd = complex<long double>;

void fft(vector<cd>& a, bool invert) {
    int n = (int)a.size();
    static vector<int> rev;
    static vector<cd> roots;
    static int last_n = 0;

    if (n != last_n) {
        int lg = 0;
        while ((1 << lg) < n) ++lg;
        rev.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
        }
        roots.assign(n, cd(0, 0));
        const ld PI = acosl(-1.0L);
        for (int i = 0; i < n; ++i) {
            ld ang = 2 * PI * i / n;
            roots[i] = cd(cosl(ang), sinl(ang));
        }
        last_n = n;
    }

    for (int i = 0; i < n; ++i)
        if (i < rev[i]) swap(a[i], a[rev[i]]);

    for (int len = 1; len < n; len <<= 1) {
        int step = n / (len << 1);
        for (int i = 0; i < n; i += (len << 1)) {
            for (int j = 0; j < len; ++j) {
                cd w = roots[step * j];
                if (invert) w = conj(w);
                cd u = a[i + j];
                cd v = a[i + j + len] * w;
                a[i + j]       = u + v;
                a[i + j + len] = u - v;
            }
        }
    }

    if (invert) {
        ld inv_n = 1.0L / n;
        for (auto &x : a) x *= inv_n;
    }
}

vector<ll> convMod(const vector<ll> &a, const vector<ll> &b, ll M) {
    if (a.empty() || b.empty()) return {};
    int need = (int)a.size() + (int)b.size() - 1;
    int B = 32 - __builtin_clz(need);
    int n = 1 << B;
    ll cut = (ll)sqrtl((ld)M) + 1;

    vector<cd> L(n), R(n), outl(n), outs(n);

    for (int i = 0; i < (int)a.size(); i++) {
        ll x = a[i] % M;
        if (x < 0) x += M;
        L[i] = cd((ld)(x / cut), (ld)(x % cut));
    }
    for (int i = (int)a.size(); i < n; ++i) L[i] = cd(0, 0);

    for (int i = 0; i < (int)b.size(); i++) {
        ll x = b[i] % M;
        if (x < 0) x += M;
        R[i] = cd((ld)(x / cut), (ld)(x % cut));
    }
    for (int i = (int)b.size(); i < n; ++i) R[i] = cd(0, 0);

    fft(L, false);
    fft(R, false);
    for (int i = 0; i < n; i++) {
        int j = (n - i) & (n - 1);
        cd a1 = (L[i] + conj(L[j])) * cd(0.5L, 0);
        cd a2 = (L[i] - conj(L[j])) * cd(0, -0.5L);
        cd b1 = R[i];
        outl[i] = a1 * b1;
        outs[i] = a2 * b1;
    }
    fft(outl, true);
    fft(outs, true);

    vector<ll> res(need);
    for (int i = 0; i < need; i++) {
        ll av = (ll)llround(outl[i].real());
        ll bv = (ll)llround(outl[i].imag()) + (ll)llround(outs[i].real());
        ll cv = (ll)llround(outs[i].imag());

        av %= M; if (av < 0) av += M;
        bv %= M; if (bv < 0) bv += M;
        cv %= M; if (cv < 0) cv += M;

        __int128 x = av;
        x = (x * cut + bv) % M;
        x = (x * cut + cv) % M;
        res[i] = (ll)x;
    }
    return res;
}

long long modPow(long long a, long long y, ll M) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (__int128)res * a % M;
        }
        y /= 2;
        a = (__int128)a * a % M;
    }
    return res;
}

struct Factorial {
    ll M;
    vector<ll> _fact{1}, _inv_fact{1};

    Factorial(ll M) : M(M) {}

    void ensure(int m) {
        int n = _fact.size();
        if (m <= n) {
            return;
        }
        m = max(2 * n, m);
        _fact.resize(m);
        _inv_fact.resize(m);
        for (int i = n; i < m; i++) {
            _fact[i] = _fact[i - 1] * i % M;
        }
        _inv_fact[m - 1] = modPow(_fact[m - 1], M - 2, M);
        for (int i = m - 1; i > n; i--) {
            _inv_fact[i - 1] = _inv_fact[i] * i % M;
        }
    }

    ll fact(int n) {
        ensure(n + 1);
        return _fact[n];
    }
    ll inv_fact(int n) {
        ensure(n + 1);
        return _inv_fact[n];
    }
};

//Computes f(t),f(t+1),...,f(t+m-1) from f(0),f(1),...,f(n-1)

vector<ll> shift_of_sampling_points(vector<ll> &ys, ll t, int m, Factorial &F) {
    int n = ys.size();
    F.ensure(max(n, m));
    vector<ll> f(n), g(n);
    ll M = F.M;
    for (int i = 0; i < n; i++) {
        f[i] = (__int128)ys[i] * F.inv_fact(i) % M;
        g[i] = ((i & 1 ? -1 : 1) * F.inv_fact(i) + M) % M;
    }
    vector<ll> b = convMod(f, g, M);
    b.resize(n);
    vector<ll> c(n);
    ll prd = 1;
    reverse(b.begin(), b.end());
    for (int i = 0; i < n; i++) {
        b[i] = (__int128)b[i] * F.fact(n - i - 1) % M;
        c[i] = (__int128)prd * F.inv_fact(i) % M;
        prd = (__int128)prd * (t - i + M) % M;
    }
    vector<ll> e = convMod(b, c, M);
    e.resize(n);
    reverse(e.begin(), e.end());
    for (int i = 0; i < n; i++) {
        e[i] = (__int128)e[i] * F.inv_fact(i) % M;
    }
    vector<ll> j(m);
    for (int i = 0; i < m; i++) {
        j[i] = F.inv_fact(i);
    }
    vector<ll> res = convMod(e, j, M);
    res.resize(m);
    for (int i = 0; i < m; i++) {
        res[i] = (__int128)res[i] * F.fact(i) % M;
    }
    return res;
}

int log_block_size = 17;
int block_size = 1 << log_block_size;
int block_num;

//Computes (iB)! for i=0,1,...,floor(P/B) where B=2^(log2(sqrt(p)))

ll kth_block_fact(int block_num, ll M, int q) {
    Factorial F(M);
    vector<ll> f{1};
    f.reserve(block_size);
    for (int i = 0; i < log_block_size; ++i) {
        vector<ll> g = shift_of_sampling_points(f, 1 << i, 3 << i, F);
        const auto get = [&](int j) { return j < (1 << i) ? f[j] : g[j - (1 << i)]; };
        f.resize(2 << i);
        for (int j = 0; j < 2 << i; ++j) {
            // (2*j+1)*2^i <= 2^(2*_log_b) + 2^(_log_b-1) < 2^31 holds if _log_b <= 15
            f[j] = (__int128)get(2 * j) * get(2 * j + 1) % M * ((2ll * j + 1) << i) % M;
        }
    }
    // f_B(x) = (x+1) * ... * (x+B-1)
    if (block_num > block_size) {
        vector<ll> g = shift_of_sampling_points(f, block_size, block_num - block_size, F);
        move(g.begin(), g.end(), std::back_inserter(f));
    } else {
        f.resize(block_num);
    }
    for (int i = 0; i < block_num; ++i) {
        f[i] = (__int128)f[i] * block_size * (i + 1) % M;
    }
    // f[i] = (i*B + 1) * ... * (i*B + B)

    f.insert(f.begin(), 1);
    for (int i = 1; i <= block_num; ++i) {
        f[i] = (__int128)f[i] * f[i - 1] % M;
    }
    return f[q];
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        ll n, M;
        cin >> n >> M;
        if (n >= M) {
            cout << 0 << endl;
            continue;
        }
        log_block_size = 0;
        ll B = 1; while ((B << 1) * (B << 1) <= M) { B <<= 1; log_block_size++; } block_size = B; block_num = M / block_size;
        ll res;
        int q = n / block_size, r = n % block_size;
        block_num = M >> log_block_size;
        if (2 * r <= block_size) {
            res = kth_block_fact(block_num, M, q);
            for (int i = 0; i < r; ++i) {
                res = (__int128)res * (n - i) % M;
            }
        } else if (q != block_num) {
            res = kth_block_fact(block_num, M, q + 1);
            ll den = 1;
            for (int i = 1; i <= block_size - r; ++i) {
                den = (__int128)den * (n + i) % M;
            }
            res = (__int128)res * modPow(den, M - 2, M) % M;
        } else {
            // Wilson's theorem
            res = M - 1;
            ll den = 1;
            for (ll i = M - 1; i > n; --i) {
                den = (__int128)den * i % M;
            }
            res = (__int128)res * modPow(den, M - 2, M) % M;
        }
        cout << res << endl;
    }

    return 0;
}
