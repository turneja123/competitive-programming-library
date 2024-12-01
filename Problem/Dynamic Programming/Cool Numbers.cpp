//https://www.spoj.com/problems/COOLNUMS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

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

long long pw[12];
gp_hash_table<long long, array<long long, 3>, custom_hash> dp[12];
gp_hash_table<long long, bool, custom_hash> mp;

bool get(long long j) {
    vector<int> b;
    int d = 0;
    while (j > 0) {
        for (int i = 0; i < j % 12; i++) {
            b.push_back(d);
        }
        j /= 12;
        d++;
    }
    int sum = 0, m = b.size();
    for (int i = 0; i < m; i++) {
        sum += b[i];
    }
    if (sum % 2 == 1) {
        return false;
    }
    for (int mask = 1; mask < 1 << m; mask++) {
        int cur = 0;
        for (int i = 0; i < m; i++) {
            int c = mask & (1 << i);
            if (c) {
                cur += b[i];
            }
        }
        if (cur == sum / 2) {
            return true;
        }
    }
    return false;
}

long long calc(long long n) {
    if (n == 0) {
        return 0;
    }
    vector<int> b;
    while (n > 0) {
        b.push_back(n % 10);
        n /= 10;
    }
    reverse(b.begin(), b.end());
    for (int d = 1; d < 10; d++) {
        if (d < b[0]) {
            dp[0][pw[d]][0]++;
        } else if (d == b[0]) {
            dp[0][pw[d]][2]++;
        } else {
            dp[0][pw[d]][1]++;
        }
    }
    for (int i = 1; i < b.size(); i++) {
        for (auto it = dp[i - 1].begin(); it != dp[i - 1].end(); ++it) {
            long long j = it->first;
            for (int d = 0; d < 10; d++) {
                if (b[i] > d) {
                    dp[i][j + pw[d]][0] += it->second[0] + it->second[2];
                    dp[i][j + pw[d]][1] += it->second[1];
                } else if (b[i] == d) {
                    dp[i][j + pw[d]][0] += it->second[0];
                    dp[i][j + pw[d]][1] += it->second[1];
                    dp[i][j + pw[d]][2] += it->second[2];
                } else {
                    dp[i][j + pw[d]][0] += it->second[0];
                    dp[i][j + pw[d]][1] += it->second[1] + it->second[2];
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < b.size(); i++) {
        for (auto it = dp[i].begin(); it != dp[i].end(); ++it) {
            long long j = it->first;
            auto f = mp.find(j);
            if (f == mp.end()) {
                mp[j] = get(j);
            }
            if (mp[j] == false) {
                continue;
            }
            ans += it->second[0] + it->second[2];
            if (i != b.size() - 1) {
                ans += it->second[1];
            }
        }
    }
    return ans;
}

int main() {
	IOS;
	pw[0] = 1;
	for (int i = 1; i < 12; i++) {
        pw[i] = pw[i - 1] * 12;
	}

	long long l, r;
	cin >> l >> r;
	while (l != 0) {
        long long ans = calc(r);
        for (int i = 0; i < 12; i++) {
            dp[i].clear();
        }
        ans -= calc(l - 1);
        for (int i = 0; i < 12; i++) {
            dp[i].clear();
        }
        cout << ans << endl;
        cin >> l >> r;
	}
	return 0;
}
