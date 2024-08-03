//https://www.spoj.com/problems/CHECKMEET/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

string a[8];
string s;

struct custom_hash {
    static __int128 splitmix64(__int128 x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(__int128 x) const {
        static const __int128 FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

struct mini {
    size_t operator()(pair<int, int> x) const {
        return x.first * 1000 + x.second;
    }
};

vector<vector<pair<int, int>>> movesl, movesr;

set<pair<int, int>> st;
gp_hash_table<pair<int, int>, int, mini> mp;

gp_hash_table<__int128, int, custom_hash> freq[8][8];

bool b[500];
bool vis[8][8];

long long ans = 0;

int popcount(__int128 x) {
    int ct = 0;
    while (x > 0) {
        ct++;
        x = x & (x - 1);
    }
    return ct;
}

void gen_moves(vector<pair<int, int>> &v, int n, vector<vector<pair<int, int>>> &moves) {
    if (v.size() == n) {
        moves.push_back(v);
        return;
    }
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (abs(dx) + abs(dy) != 0) {
                int x = v[v.size() - 1].first + dx, y = v[v.size() - 1].second + dy;
                bool good = true;
                for (int i = 0; i < v.size(); i++) {
                    if (v[i].first == x && v[i].second == y) {
                        good = false;
                    }
                }
                if (!good) {
                    continue;
                }
                v.push_back(make_pair(x, y));

                st.insert(make_pair(x, y));
                gen_moves(v, n, moves);
                v.pop_back();
            }
        }
    }
}

gp_hash_table<__int128, int, custom_hash> memo[8][8];

long long solve(int x, int y, vector<pair<int, int>> &visited) {
    long long ans = 0;
    __int128 mask = 0;
    for (int p = 0; p < visited.size(); p++) {
        auto it = mp.find(make_pair(visited[p].first - x, visited[p].second - y));
        if (it == mp.end()) {
            continue;
        }
        __int128 pw = it->second;
        if (!b[pw]) {
            continue;
        }
        __int128 bit = (__int128)1 << pw;
        mask += bit;
    }
    auto f = memo[x][y].find(mask);
    if (f != memo[x][y].end()) {
        return f->second;
    }
    for (__int128 s = mask; s; s = (s - 1) & mask) {
        auto it = freq[x][y].find(s);
        if (it == freq[x][y].end()) {
            continue;
        }
        ans += it->second;
    }
    ans += freq[x][y][0];
    memo[x][y][mask] = ans;
    return ans;

}

int main(){
	IOS;
	int n;
	cin >> n;
	cin >> s;
	for (int i = 0; i < 8; i++) {
        cin >> a[i];
	}
	if (n == 1) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (a[i][j] == s[0]) {
                    ans++;
                }
            }
        }
        cout << ans;
        return 0;
	}
	int m = n / 2;
	vector<pair<int, int>> v;
	v.push_back(make_pair(0, 0));
	gen_moves(v, m, movesl);
	gen_moves(v, n - m, movesr);
    st.insert(make_pair(0, 0));
	for (auto it = st.begin(); it != st.end(); ++it) {
        mp[*it] = mp.size();

	}
	for (int k = 0; k < movesr.size(); k++) {
        for (int p = 0; p < movesr[k].size(); p++) {
            b[mp[make_pair(movesr[k][p].first, movesr[k][p].second)]] = true;
        }
	}
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < movesr.size(); k++) {
                int x = i, y = j; bool good = true;
                for (int p = 0; p < movesr[k].size() && good; p++) {
                    x = i + movesr[k][p].first, y = j + movesr[k][p].second;
                    if (x < 0 || x >= 8 || y < 0 || y >= 8 || a[x][y] != s[m + p]) {
                        good = false;
                    }
                }
                if (!good) {
                    continue;
                }
                __int128 mask = 0;
                for (int p = 0; p < movesr[k].size(); p++) {
                    __int128 pw = mp[make_pair(movesr[k][p].first, movesr[k][p].second)];
                    mask += (__int128)1 << pw;

                }
                for (__int128 s = mask; s; s = (s - 1) & mask) {
                    freq[i][j][s]++;
                }
                freq[i][j][0]++;
            }
            for (auto it = freq[i][j].begin(); it != freq[i][j].end(); ++it) {
                if (popcount(it->first) % 2 == 1) {
                    it->second = -it->second;
                }
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < movesl.size(); k++) {
                int x = i, y = j; bool good = true;
                vector<pair<int, int>> visited;
                for (int p = 0; p < movesl[k].size() && good; p++) {
                    x = i + movesl[k][p].first, y = j + movesl[k][p].second;
                    visited.push_back(make_pair(x, y));
                    if (x < 0 || x >= 8 || y < 0 || y >= 8 || a[x][y] != s[p]) {
                        good = false;
                    }
                }
                if (!good) {
                    continue;
                }
                for (int p = 0; p < visited.size(); p++) {
                    vis[visited[p].first][visited[p].second] = true;
                }
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (abs(dx) + abs(dy) != 0 && x + dx >= 0 && x + dx < 8 && y + dy >= 0 && y + dy < 8 && !vis[x + dx][y + dy]) {
                            ans += solve(x + dx, y + dy, visited);
                        }
                    }
                }
                for (int p = 0; p < visited.size(); p++) {
                    vis[visited[p].first][visited[p].second] = false;
                }
            }
            //cout << i << " " << j << endl;
        }
    }
    cout << ans;
	return 0;
}
