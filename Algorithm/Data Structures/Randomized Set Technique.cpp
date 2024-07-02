//https://codeforces.com/problemset/problem/1418/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int K = 50;

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

int a[N];
int freq[N];
bool st[K][2 * N];
gp_hash_table<int, int, custom_hash> pos;

vector<int> nil;
vector<int> v[N];
map<vector<int>, int> mp;

void gen_sets(int n) {
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < n; i++) {
            if (generator() % 2) {
                st[k][i] = true;
            }
        }
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (pos.find(a[i]) == pos.end()) {
            pos[a[i]] = pos.size();
        }
        a[i] = pos[a[i]];
    }
    gen_sets(pos.size());
    vector<int> cur(K, 0);
    nil = cur;
    mp[nil]++;
    int l = -1;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        freq[a[i]]++;
        while (freq[a[i]] > 3) {
            if (l < 0) {
                mp[nil]--;
            } else {
                mp[v[l]]--;
            }
            freq[a[l + 1]]--;
            l++;
        }
        for (int k = 0; k < K; k++) {
            if (st[k][a[i]]) {
                cur[k] = (cur[k] + 1) % 3;
            }
        }
        ans += mp[cur];
        mp[cur]++;
        v[i] = cur;
    }
    cout << ans;
    return 0;
}
