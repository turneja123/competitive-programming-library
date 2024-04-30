//https://www.spoj.com/problems/FINDLR/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

long long inverse(long long a, long long mod) {
    return a == 1 ? 1 : (ll)(mod - mod / a) * inverse(mod % a, mod) % mod;
};

void extend(vector<long long> &a, int d, ll value = 0) {
    if (d <= a.size()) {
        return;
    }
    a.resize(d, value);
}

struct LinearRecurrence {
    static vector<long long> berlekamp_massey(const vector<long long> &s, ll mod) {
        vector<long long> c = {1}, b = {1};
        long long d = s[0];
        for (int i = 1, m = 1; i < s.size(); ++i, m++) {
            long long d_next = 0;
            for (int j = 0; j < c.size(); ++j) {
                d_next += c[j] * s[i - j] % mod;
            }
            if (!(d_next %= mod)) {
                continue;
            }
            if (2 * (c.size() - 1) <= i) {
                auto temp = c;
                extend(c, b.size() + m);
                long long coef = d_next * inverse(d, mod) % mod;
                for (int j = 0; j < b.size(); ++j) {
                    c[j + m] = (c[j + m] - coef * b[j] % mod + mod) % mod;
                }
                b = temp, d = d_next, m = 0;
            } else {
                extend(c, b.size() + m);
                long long coef = d_next * inverse(d, mod) % mod;
                for (int j = 0; j < b.size(); ++j) {
                    c[j + m] = (c[j + m] - coef * b[j] % mod + mod) % mod;
                }
            }
        }
        return c;
    }
    static void exgcd(long long a, long long b, long long &g, long long &x, long long &y) {
        if (!b) {
            x = 1, y = 0, g = a;
        } else {
            exgcd(b, a % b, g, y, x);
            y -= x * (a / b);
        }
    }
    static long long crt(const vector<long long> &c, const vector<long long> &m) {
        int n = c.size();
        long long M = 1, ans = 0;
        for (int i = 0; i < n; ++i) {
            M *= m[i];
        }
        for (int i = 0; i < n; ++i) {
            long long x, y, g, tm = M / m[i];
            exgcd(tm, m[i], g, x, y);
            ans = (ans + tm * x * c[i] % M) % M;
        }
        return (ans + M) % M;
    }
    static vector<long long> reeds_sloane(const vector<long long> &s, long long mod) {
        auto inverse = [] (ll a, ll m) {
            long long d, x, y;
            exgcd(a, m, d, x, y);
            return d == 1 ? (x % m + m) % m : -1;
        };
        auto L = [] (const vector<long long> &a, const vector<long long> &b) {
            int da = (a.size() > 1 || (a.size() == 1 && a[0])) ? a.size() - 1 : -40000;
            int db = (b.size() > 1 || (b.size() == 1 && b[0])) ? b.size() - 1 : -40000;
            return max(da, db + 1);
        };
        auto prime_power = [&] (const vector<long long> &s, long long mod, long long p, long long e) {
            vector<vector<long long>> a(e), b(e), an(e), bn(e), ao(e), bo(e);
            vector<long long> t(e), u(e), r(e), to(e, 1), uo(e), pw(e + 1, 1);;
            for (int i = 1; i <= e; ++i) {
                pw[i] = pw[i - 1] * p;
            }
            for (ll i = 0; i < e; ++i) {
                a[i] = {pw[i]}, an[i] = {pw[i]};
                b[i] = {0}, bn[i] = {s[0] * pw[i] % mod};
                t[i] = s[0] * pw[i] % mod;
                if (t[i] == 0) {
                    t[i] = 1, u[i] = e;
                } else {
                    for (u[i] = 0; t[i] % p == 0; t[i] /= p, ++u[i]);
                }
            }
            for (int k = 1; k < s.size(); ++k) {
                for (int g = 0; g < e; ++g) {
                    if (L(an[g], bn[g]) > L(a[g], b[g])) {
                        ao[g] = a[e - 1 - u[g]];
                        bo[g] = b[e - 1 - u[g]];
                        to[g] = t[e - 1 - u[g]];
                        uo[g] = u[e - 1 - u[g]];
                        r[g] = k - 1;
                    }
                }
                a = an, b = bn;
                for (int o = 0; o < e; ++o) {
                    ll d = 0;
                    for (int i = 0; i < a[o].size() && i <= k; ++i) {
                        d = (d + a[o][i] * s[k - i]) % mod;
                    }
                    if (d == 0) {
                        t[o] = 1, u[o] = e;
                    } else {
                        for (u[o] = 0, t[o] = d; t[o] % p == 0; t[o] /= p, ++u[o]);
                        int g = e - 1 - u[o];
                        if (L(a[g], b[g]) == 0) {
                            extend(bn[o], k + 1);
                            bn[o][k] = (bn[o][k] + d) % mod;
                        } else {
                            ll coef = t[o] * inverse(to[g], mod) % mod * pw[u[o] - uo[g]] % mod;
                            int m = k - r[g];
                            assert(m >= 0);
                            extend(an[o], ao[g].size() + m);
                            extend(bn[o], bo[g].size() + m);
                            for (int i = 0; i < ao[g].size(); ++i) {
                                an[o][i + m] -= coef * ao[g][i] % mod;
                                if (an[o][i + m] < 0) {
                                    an[o][i + m] += mod;
                                }
                            }
                            while (an[o].size() && an[o].back() == 0) {
                                an[o].pop_back();
                            }
                            for (int i = 0; i < bo[g].size(); ++i) {
                                bn[o][i + m] -= coef * bo[g][i] % mod;
                                if (bn[o][i + m] < 0) {
                                    bn[o][i + m] -= mod;
                                }
                            }
                            while (bn[o].size() && bn[o].back() == 0) {
                                bn[o].pop_back();
                            }
                        }
                    }
                }
            }
            return make_pair(an[0], bn[0]);
        };
        vector<tuple<long long, long long, int>> fac;
        for (long long i = 2; i * i <= mod; ++i) {
            if (mod % i == 0) {
                ll cnt = 0, pw = 1;
                while (mod % i == 0) {
                    mod /= i, ++cnt, pw *= i;
                }
                fac.emplace_back(pw, i, cnt);
            }
        }
        if (mod > 1) {
            fac.emplace_back(mod, mod, 1);
        }
        vector<vector<long long>> as;
        int n = 0;
        for (auto &&x: fac) {
            ll mod, p, e;
            vector<long long> a, b;
            tie(mod, p, e) = x;
            auto ss = s;
            for (auto &&x: ss) {
                x %= mod;
            }
            tie(a, b) = prime_power(ss, mod, p, e);
            as.emplace_back(a);
            n = max(n, (int)a.size());
        }
        vector<long long> a(n), c(as.size()), m(as.size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < as.size(); ++j) {
                m[j] = get<0>(fac[j]);
                c[j] = i < as[j].size() ? as[j][i] : 0;
            }
            a[i] = crt(c, m);
        }
        return a;
    }

    LinearRecurrence(const vector<long long> &s, ll mod, bool is_prime = true): mod(mod) {
        vector<long long> c;
        if (is_prime) {
            c = berlekamp_massey(s, mod);
        } else {
            c = reeds_sloane(s, mod);
        }
        m = s.size() / 2, L = c.size();
        c.resize(m + 1, 0);
        trans.resize(m);
        for (int i = 0; i < m; ++i) {
            trans[i] = (mod - c[i + 1]) % mod;
        }
        if (m == 0) {
            m = 1, trans = {1};
        }
        reverse(trans.begin(), trans.end());
        init = {s.begin(), s.begin() + m};
    }
    long long solve(long long n) {
        if (mod == 1) {
            return 0;
        }
        if (n < 0) {
            return 0;
        }
        if (n < m) {
            return init[n];
        }
        vector<long long> v(m), u(m << 1);
        long long mask = !!n;
        for (long long m = n; m > 1; m >>= 1) {
            mask <<= 1;
        }
        v[0] = 1;
        for (long long x = 0; mask; mask >>= 1, x <<= 1) {
            fill_n(u.begin(), m * 2, 0);
            x |= !!(n & mask);
            if (x < m) {
                u[x] = 1;
            } else {
                for (int i = 0; i < m; ++i) {
                    for (int j = 0, t = i + (x & 1); j < m; ++j, ++t) {
                        u[t] = (u[t] + v[i] * v[j]) % mod;
                    }
                }
                for (int i = m * 2 - 1; i >= m; --i) {
                    for (int j = 0, t = i - m; j < m; ++j, ++t) {
                        u[t] = (u[t] + trans[j] * u[i]) % mod;
                    }
                }
            }
            v = {u.begin(), u.begin() + m};
        }
        long long ret = 0;
        for (int i = 0; i < m; ++i) {
            ret = (ret + v[i] * init[i]) % mod;
        }
        return ret;
    }
    vector<long long> init, trans;
    long long mod;
    int m, L;
};
int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long k, mod;
        cin >> k >> mod;
        vector<long long> s(2 * k);
        for (int i = 0; i < 2 * k; i++) {
            cin >> s[i];
        }
        LinearRecurrence c(s, mod, 0);
        ll ans = c.solve(2 * k);
        cout << ans << endl;
    }
    return 0;
}
