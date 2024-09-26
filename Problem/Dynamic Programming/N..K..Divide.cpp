//https://www.spoj.com/problems/NKDIV/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

map<long long, int> dp[2];
map<long long, vector<pair<long long, int>>> mp;

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23};
vector<__int128> factors;

__int128 mult(__int128 a, __int128 b, __int128 mod) {
    return (__int128)a * b % mod;
}

__int128 f(__int128 x, __int128 c, __int128 mod) {
    return (mult(x, x, mod) + c) % mod;
}

__int128 binpower(__int128 base, __int128 e, __int128 mod) {
    __int128 result = 1;
    base %= mod;
    while (e) {
        if (e & 1) {
            result = (__int128)result * base % mod;
        }
        base = (__int128)base * base % mod;
        e >>= 1;
    }
    return result;
}

__int128 rho(__int128 n) {
    __int128 c = rand() % (n + 1);
    __int128 x = rand() % (n + 1);
    __int128 xx = x;
    __int128 g = 1;
    if (n % 2 == 0) {
        return 2;
    }

    while (g == 1) {
        x = f(x, c, n);
        xx = f(xx, c, n);
        xx = f(xx, c, n);
        g = __gcd(abs(x - xx), n);
    }
    return g;
}

bool check_composite(__int128 n, __int128 a, __int128 d, int s) {
    __int128 x = binpower(a, d, n);
    if (x == 1 || x == n - 1) {
        return false;
    }
    for (int r = 1; r < s; r++) {
        x = (__int128)x * x % n;
        if (x == n - 1) {
            return false;
        }
    }
    return true;
};


bool is_prime(__int128 n) {
    if (n < 2) {
        return false;
    }
    int r = 0;
    __int128 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for (int a : primes) {
        if (n == a) {
            return true;
        }
        if (check_composite(n, a, d, r)) {
            return false;
        }
    }
    return true;
}

void factor(__int128 n) {
    if (n == 1) {
        return;
    }
    if (is_prime(n)) {
        factors.push_back(n);
        return;
    }

    __int128 divisor = rho(n);
    factor(divisor);
    factor(n / divisor);
    return;
}

void get_divs(int i, long long cur, vector<pair<long long, int>> &f, vector<pair<long long, int>> &v, vector<long long> &divs, bool b) {
    if (i == f.size()) {
        if (b) {
            mp[cur] = v;
        }
        divs.push_back(cur);
        return;
    }
    for (int j = 0; j <= f[i].second; j++) {
        v[i].first = f[i].first, v[i].second = j;
        get_divs(i + 1, cur, f, v, divs, b);
        cur *= f[i].first;
    }
    v[i] = make_pair(0, 0);
    return;
}

int calc(long long n, int k, int flag, vector<pair<long long, int>> f, bool b) {
    auto it = dp[flag].find(n);
    if (it != dp[flag].end()) {
        return it->second;
    }
    vector<long long> divs;
    vector<pair<long long, int>> v(f.size());
    get_divs(0, 1, f, v, divs, b);
    int ans = ((flag == 0) ? 1 : 0);
    for (int i = 0; i < divs.size(); i++) {
        vector<pair<long long, int>> d = mp[divs[i]];
        vector<pair<long long, int>> nw = f;
        int o = 0;
        for (int j = 0; j < f.size(); j++) {
            if (d[j].second != 0) {
                o++;
                nw[j].second -= d[j].second;
            }
        }
        if (o <= k && divs[i] != 1) {
            if (!flag) {
                ans = min(ans, calc(n / divs[i], k, 1, nw, 0));
            } else {
                ans = max(ans, calc(n / divs[i], k, 0, nw, 0));
            }
        }
    }
    return dp[flag][n] = ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    int last = 1, a = 0, b = 0;
    for (int tt = 1; tt <= t; tt++) {
        dp[0][1] = 1, dp[1][1] = 0;
        long long n, k;
        cin >> n >> k;
        factor(n);
        sort(factors.begin(), factors.end());
        int i = 0, j = 0, m = factors.size();
        vector<pair<long long, int>> f;
        while (i < m) {
            __int128 cur = factors[i];
            while (i < m && factors[i] == cur) {
                i++;
            }
            f.push_back(make_pair(factors[j], i - j));
            j = i;
        }
        factors.clear();
        last = calc(n, k, last, f, 1);
        if (last == 1) {
            cout << "Mona" << endl;
            a++;
        } else {
            cout << "Alaa" << endl;
            b++;
        }
        mp.clear();
        dp[0].clear();
        dp[1].clear();
    }
    cout << endl;
    if (a >= b) {
        cout << "Mona" << endl;
    } else {
        cout << "Alaa" << endl;
    }

    return 0;
}
