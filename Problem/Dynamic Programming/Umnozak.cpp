//https://www.spoj.com/problems/UMNOZAK/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e18;

vector<vector<int>> trans;
vector<int> p{2,3,5,7};


ll near(ll x) {
    if (x == 1) {
        return 1;
    }
    vector<int> dig;
    for (int d = 9; d >= 2; d--) {
        while (x % d == 0) {
            x /= d;
            dig.push_back(d);
        }
    }

    if (x != 1) {
        return -1;
    }

    reverse(dig.begin(), dig.end());

    __int128 ans = 0;
    for (int d : dig) {
        ans = ans * 10 + d;
        if (ans > INF) {
            return INF + 1;
        }
    }
    return (ll)ans;
}

vector<vector<vector<vector<int>>>> dp[19];


ll get(int i, int a, int b, int c, int d) {
    if (dp[i].size() <= a) {
        return 0;
    }
    if (dp[i][a].size() <= b) {
        return 0;
    }
    if (dp[i][a][b].size() <= c) {
        return 0;
    }
    if (dp[i][a][b][c].size() <= d) {
        return 0;
    }
    return dp[i][a][b][c][d];
}

ll calc(ll n, vector<int> &f) {
    if (n <= 0) {
        return 0;
    }
    vector<int> dig;
    while (n > 0) {
        dig.push_back(n % 10);
        n /= 10;
    }
    reverse(dig.begin(), dig.end());

    int m = dig.size();
    int fa = f[0], fb = f[1], fc = f[2], fd = f[3];

    ll ans = 0;

    for (int i = 1; i < m; i++) {
        ans += get(i, fa, fb, fc, fd);
    }

    int ca = 0, cb = 0, cc = 0, cd = 0;

    for (int i = 0; i < m; i++) {
        for (int d = 1; d < dig[i]; d++) {
            int na = ca + trans[d][0], nb = cb + trans[d][1], nc = cc + trans[d][2], nd = cd + trans[d][3];
            if (na > fa || nb > fb || nc > fc || nd > fd) {
                continue;
            }
            ans += get(m - i - 1, fa - na, fb - nb, fc - nc, fd - nd);
        }
        if (dig[i] == 0) {
            return ans;
        }

        ca += trans[dig[i]][0];
        cb += trans[dig[i]][1];
        cc += trans[dig[i]][2];
        cd += trans[dig[i]][3];
        if (ca > fa || cb > fb || cc > fc || cd > fd) {
            return ans;
        }
    }
    if (ca == fa && cb == fb && cc == fc && cd == fd) {
        ans++;
    }
    return ans;
}

int main() {
    IOS;
    trans.push_back({0, 0, 0, 0});
    trans.push_back({0, 0, 0, 0});
    trans.push_back({1, 0, 0, 0});
    trans.push_back({0, 1, 0, 0});
    trans.push_back({2, 0, 0, 0});
    trans.push_back({0, 0, 1, 0});
    trans.push_back({1, 1, 0, 0});
    trans.push_back({0, 0, 0, 1});
    trans.push_back({3, 0, 0, 0});
    trans.push_back({0, 2, 0, 0});
    dp[0].resize(1);
    dp[0][0].resize(1);
    dp[0][0][0].resize(1);
    dp[0][0][0][0].resize(1);
    dp[0][0][0][0][0] = 1;

    vector<vector<int>> states{{0, 0, 0, 0}};
    for (int i = 1; i < 19; i++) {
        set<vector<int>> nx;
        for (vector<int> &v : states) {
            for (int k = 1; k <= 9; k++) {
                vector<int> &add = trans[k];
                vector<int> go = v;
                for (int j = 0; j < 4; j++) {
                    go[j] += add[j];
                }
                nx.insert(go);
                if (dp[i].size() < go[0] + 1) {
                    dp[i].resize(go[0] + 1);
                }
                if (dp[i][go[0]].size() < go[1] + 1) {
                    dp[i][go[0]].resize(go[1] + 1);
                }
                if (dp[i][go[0]][go[1]].size() < go[2] + 1) {
                    dp[i][go[0]][go[1]].resize(go[2] + 1);
                }
                if (dp[i][go[0]][go[1]][go[2]].size() < go[3] + 1) {
                    dp[i][go[0]][go[1]][go[2]].resize(go[3] + 1);
                }

                dp[i][go[0]][go[1]][go[2]][go[3]] += dp[i - 1][v[0]][v[1]][v[2]][v[3]];
            }
        }
        states.clear();
        for (auto &v : nx) {
            states.push_back(v);
        }
    }

    vector<ll> prod{1};
    for (int i = 0; i < 16; i++) {
        vector<ll> nx;
        for (ll j : prod) {
            for (int d = 1; d < 10; d++) {
                nx.push_back(j * d);
            }
        }
        sort(nx.begin(), nx.end());
        nx.erase(unique(nx.begin(), nx.end()), nx.end());
        prod = nx;
    }

    vector<ll> v;
    for (int i = 0; i < prod.size(); i++) {
        if ((__int128)prod[i] * near(prod[i]) <= INF) {
            v.push_back(prod[i]);
        }

    }
    vector<vector<int>> f;
    for (int i = 0; i < v.size(); i++) {
        vector<int> cur;
        ll n = v[i];
        for (int P : p) {
            int e = 0;
            while (n % P == 0) {
                n /= P;
                e++;
            }
            cur.push_back(e);
        }
        f.push_back(cur);
    }
    int t;
    cin >> t;
    while (t--) {
        ll l, r;
        cin >> l >> r;
        l--;
        ll ans = 0;
        for (int i = 0; i < v.size(); i++) {
            ll x = r / v[i];
            if (x >= near(v[i])) {
                ans += calc(x, f[i]);
            }

            x = l / v[i];
            if (x >= near(v[i])) {
                ans -= calc(x, f[i]);
            }
        }
        cout << ans << endl;
    }


    return 0;
}
