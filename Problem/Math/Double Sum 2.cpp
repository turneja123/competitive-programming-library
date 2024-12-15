//https://atcoder.jp/contests/abc384/tasks/abc384_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 25;

long long a[N];
long long pw[K];
long long ans[K];

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

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

gp_hash_table<int, pair<long long, int>, custom_hash> mp[K];

int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < K; i++) {
        pw[i] = pw[i - 1] * 2;
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < K; j++) {
            mp[j][a[i] % pw[j]].first += a[i];
            mp[j][a[i] % pw[j]].second++;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < K; j++) {
            int need = (pw[j] - a[i] % pw[j]) % pw[j];
            auto it = mp[j].find(need);
            if (it == mp[j].end()) {
                continue;
            }
            pair<long long, int> p = it->second;
            ans[j] += p.first + a[i] * p.second;
            mp[j][a[i] % pw[j]].first -= a[i];
            mp[j][a[i] % pw[j]].second--;
        }
    }
    long long sum = 0;
    for (int i = K - 1; i >= 0; i--) {
        for (int j = i + 1; j < K; j++) {
            ans[i] -= ans[j];
        }
        sum += ans[i] / pw[i];
    }
    cout << sum;

    return 0;
}
