//https://cses.fi/problemset/task/1670
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

long long pw[10];

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

gp_hash_table<long long, int, custom_hash> dist;

int main() {
	IOS;
	vector<int> v(9, 0);
	long long h = 0;
	for (int i = 0; i < 9; i++) {
        cin >> v[i];
        pw[i] = (i == 0 ? 1 : pw[i - 1] * 9);
        h += (v[i] - 1) * pw[i];
	}
	dist[h] = 0;
	queue<long long> q;
	q.push(h);
	while (q.size()) {
        long long h = q.front(), t = h;
        q.pop();
        int d = dist[h];
        for (int i = 0; i < 10; i++) {
            v[i] = t % 9;
            t /= 9;
        }
        for (int i = 0; i < 9; i++) {
            if (i < 6) {
                long long cur = h - pw[i] * v[i] - pw[i + 3] * v[i + 3] + pw[i] * v[i + 3] + pw[i + 3] * v[i];
                auto it = dist.find(cur);
                if (it == dist.end()) {
                    dist[cur] = d + 1;
                    q.push(cur);
                }

            }
            if (i % 3 != 2) {
                long long cur = h - pw[i] * v[i] - pw[i + 1] * v[i + 1] + pw[i] * v[i + 1] + pw[i + 1] * v[i];
                auto it = dist.find(cur);
                if (it == dist.end()) {
                    dist[cur] = d + 1;
                    q.push(cur);
                }
            }

        }
	}
	h = 0;
	for (int i = 0; i < 9; i++) {
        h += pw[i] * i;
	}
	cout << dist[h];
	return 0;
}
