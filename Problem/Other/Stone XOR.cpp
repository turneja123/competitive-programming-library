//https://atcoder.jp/contests/abc390/tasks/abc390_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 12;

long long a[N];
string s[N];

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

//set<pair<vector<long long>, int>> st;
gp_hash_table<long long, int, custom_hash> ans;

void calc(vector<long long> &v, int i, int n) {
    int m = v.size();
    if (i == n) {
        long long x = v[0];
        for (int j = 1; j < m; j++) {
            x ^= v[j];
        }
        ans[x] = 1;
        return;
    }

    for (int j = 0; j < m; j++) {
        v[j] += a[i];
        calc(v, i + 1, n);
        v[j] -= a[i];
    }
    v.push_back(a[i]);
    calc(v, i + 1, n);
    v.pop_back();

}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<long long> v{a[0]};
    calc(v, 1, n);
    cout << ans.size();
    return 0;
}
