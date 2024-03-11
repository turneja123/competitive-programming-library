//solution for https://www.spoj.com/problems/AHASH/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


const int N = 1e6 + 5;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

long long powers[N];
gp_hash_table<int, int, custom_hash> mp;

const int k = 4;

long long calchash(string s, int n, long long m) {
    long long H = 0;
     for (int i = 0; i < s.size(); i++) {
        long long _this = (long long)(s[i] - 'a' + 1) * powers[n - i - 1];
        _this %= m;
        H += _this;
        H %= m;
    }
    return H;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; long long b, m, H = 0, firstk = 0;
        string s, first = "";
        cin >> n >> b >> m >> s;
        powers[0] = 1;
        for (int i = 1; i < n; i++) {
            powers[i] = powers[i - 1] * b;
            powers[i] %= m;
        }
        for (int i = 0; i < k; i++) {
            firstk += (long long)(s[i] - 'a' + 1) * powers[n - i - 1];
            firstk %= m;
            first += s[i];
        }

        H = firstk;

        for (int i = k; i < n; i++) {
            long long _this = (long long)(s[i] - 'a' + 1) * powers[n - i - 1];
            _this %= m;
            if (i % 100 == 0) {
                for (long long j = 1; j <= 26; j++) {
                    long long cur = (j * powers[n - i - 1]) % m;
                    mp.insert({cur - _this, 0});
                }
            }
            H += _this;
            H %= m;
        }
        for (int i = 0; i < (long long)(pow((long long)26, k)); i++) {
            string f = "";
            long long temp = i;
            while (temp > 0) {
                f += 'a' + (temp % 26);
                temp /= 26;
            }
            while (f.size() < k) {
                f += 'a';
            }
            reverse(f.begin(), f.end());
            if (f == first) {
                continue;
            }

            long long hsh = 0;
            for (int j = 0; j < k; j++) {
                hsh += (long long)(f[j] - 'a' + 1) * powers[n - j - 1];
                hsh %= m;
            }
            long long diff = firstk - hsh;
            string ans = "";
            if (mp.find(diff) != mp.end()) {
                bool flag = false;
                for (int j = 0; j < k; j++) {
                    ans += f[j];
                }
                for (int j = k; j < n; j++) {
                    if (flag) {
                        ans += s[j];
                        continue;

                    }
                    long long _this = (long long)(s[j] - 'a' + 1) * powers[n - j - 1];
                    _this %= m;


                    for (long long p = 1; p <= 26; p++) {
                        long long cur = (p * powers[n - j - 1]) % m;
                        if (cur - _this == diff) {
                            flag = true;
                            ans += (char)('a' + p - 1);
                            break;
                        }
                    }
                    if (!flag) {
                        ans += s[j];
                    }
                }
                cout << ans << endl;
                mp.clear();
            }
        }
    }
    return 0;
}
