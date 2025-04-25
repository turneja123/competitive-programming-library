//https://dmoj.ca/problem/utso21p7
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const int K = 32;
const long long M = 1e9 + 7;

int a[N];
int b[N];
int suf[N][K];

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(const pair<array<int, 31>, int> &x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        uint64_t h = 0;
        for (int i = 0; i < 31; i++) {
            h ^= splitmix64(x.first[i] + FIXED_RANDOM);
        }
        h ^= splitmix64(x.second + FIXED_RANDOM);
        return h;
    }
};

gp_hash_table<pair<array<int, 31>, int>, long long, custom_hash> dp, dp_next;

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    for (int i = 0; i < n; i++) {
        b[i] = 31 - __builtin_clz(a[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 31; j++) {
            suf[i][j] += suf[i + 1][j];
        }
        suf[i][b[i]]++;
    }
    array<int, 31> v = {};
    dp[make_pair(v, b[0])] = 1;
    for (int i = 1; i < n; i++) {
        for (auto it = dp.begin(); it != dp.end(); ++it) {
            array<int, 31> v = it->first.first;
            int j = 1;
            bool can = true;
            for (int k = 0; k < 31; k++) {
                j += v[k];
                if (v[k] > suf[i][k + 1]) {
                    can = false;
                }
            }
            if (!can) {
                continue;
            }
            int last = it->first.second;
            int ct_left = v[b[i] - 1];
            if (ct_left) {
                v[b[i] - 1]--;
                dp_next[make_pair(v, last)] += it->second * ct_left;
                v[b[i] - 1]++;
            }

            v[b[i]]++;
            dp_next[make_pair(v, last)] += it->second * j;
            v[b[i]]--;
            v[last]++;
            dp_next[make_pair(v, b[i])] += it->second;
            v[last]--;

            dp_next[make_pair(v, last)] += it->second * j;
            if (ct_left) {
                v[b[i]]++;
                v[b[i] - 1]--;
                dp_next[make_pair(v, last)] += it->second * ct_left;
                v[b[i]]--;
                v[b[i] - 1]++;
            }
            if (last == b[i] - 1) {
                dp_next[make_pair(v, b[i])] += it->second;
            }
        }
        dp = dp_next;
        for (auto it = dp.begin(); it != dp.end(); ++it) {
            it->second %= M;
        }
        dp_next.clear();
    }
    long long ans = 0;
    for (auto it = dp.begin(); it != dp.end(); ++it) {
        array<int, 31> v = it->first.first;
        int j = 1;
        for (int k = 0; k < 31; k++) {
            j += v[k];
        }
        if (j == 1) {
            ans = (ans + it->second) % M;
        }
    }
    cout << ans;
    return 0;
}
