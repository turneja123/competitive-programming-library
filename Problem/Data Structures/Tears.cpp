//https://dmoj.ca/problem/noi20p3
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int SQ = 200;
const int B = N / SQ + 5;

int a[N];

vector<pair<int, int>> b[B];
int blk[B][N];
unsigned short z[B][N];
unsigned short p[N][SQ + 5];
int ord[B][SQ + 5];
int in[B][SQ + 5][SQ + 5];

int ans[B][B][SQ + 5];

int lx[SQ + 5];
int ly[SQ + 5];

int get_blk(int i, int j) {
    if (i < 0 || j < 0) {
        return 0;
    }
    return blk[i][j];
}

ll get_ans(int i, int j, int k) {
    if (j < 0 || k <= 0) {
        return 0;
    }
    return ans[i][j][k];
}

ll calc(int l, int r, int x, int y) {
    if (l > r) {
        return 0;
    }
    ll ans = 0;
    int id = l / SQ;
    int g = x == 0 ? 0 : z[id][x - 1];
    if (l == id * SQ) {
        for (int i = l; i <= r; i++) {
            if (a[i] < x || a[i] > y) {
                continue;
            }
            int h = a[i] == 0 ? 0 : z[id][a[i] - 1];
            ans += p[i][h] - p[i][g];
        }
    } else {
        for (int i = l; i <= r; i++) {
            if (a[i] < x || a[i] > y) {
                continue;
            }
            int h = a[i] == 0 ? 0 : z[id][a[i] - 1];
            ans += p[i][h] - p[i][g] - p[l - 1][h] + p[l - 1][g];
        }
    }
    return ans;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    int ct = (n - 1) / SQ + 1;
    for (int i = 0; i < ct; i++) {
        int l = i * SQ;
        int r = min(n, (i + 1) * SQ);

        for (int j = l; j < r; j++) {
            b[i].push_back({a[j], j});
            blk[i][a[j]] = 1;
        }

        sort(b[i].begin(), b[i].end());
        for (int j = 0; j < b[i].size(); j++) {
            ord[i][j + 1] = b[i][j].first;
            p[b[i][j].second][j + 1] = 1;
        }

        for (int j = 0, ptr = 0; j < n; j++) {
            while (ptr < b[i].size() && b[i][ptr].first <= j) {
                ptr++;
            }
            z[i][j] = ptr;
        }

        for (int j = l; j < r; j++) {
            for (int k = 1; k <= b[i].size(); k++) {
                p[j][k] += p[j][k - 1];
                if (j != l) {
                    p[j][k] += p[j - 1][k] - p[j - 1][k - 1];
                }
            }
        }

        for (int j = 0; j < n; j++) {
            if (j != 0) {
                blk[i][j] += blk[i][j - 1];
            }
            if (i != 0) {
                blk[i][j] += blk[i - 1][j] - (j == 0 ? 0 : blk[i - 1][j - 1]);
            }
        }

        for (int j = 0; j < i; j++) {
            for (int k = 1; k <= b[i].size(); k++) {
                ans[i][j][k] = ans[i][j][k - 1] + blk[j][ord[i][k]];
            }
        }

        for (int j = 1; j <= b[i].size(); j++) {
            for (int k = j + 1; k <= b[i].size(); k++) {
                in[i][j][k] = in[i][j][k - 1] + p[b[i][k - 1].second][k - 1] - p[b[i][k - 1].second][j - 1];
            }
        }
    }

    for (int i = 0; i < q; i++) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        l--, r--, x--, y--;

        int bl = l / SQ;
        if (l % SQ != 0) {
            bl++;
        }
        int br = r / SQ;
        if ((r + 1) % SQ != 0) {
            br--;
        }

        ll sum = 0;
        if (l / SQ == r / SQ) {
            cout << calc(l, r, x, y) << endl;
            continue;
        }

        if (l < bl * SQ) {
            sum += calc(l, bl * SQ - 1, x, y);
        }
        if ((br + 1) * SQ <= r) {
            sum += calc((br + 1) * SQ, r, x, y);
        }

        int s1 = 0, s2 = 0;
        if (l < bl * SQ) {
            int id = l / SQ;
            for (auto [u, v] : b[id]) {
                if (v < l || u < x || u > y) {
                    continue;
                }
                lx[s1++] = u;
                sum += get_blk(br, y) - get_blk(bl - 1, y) - get_blk(br, u) + get_blk(bl - 1, u);
            }
        }
        if ((br + 1) * SQ <= r) {
            int id = r / SQ;
            for (auto [u, v] : b[id]) {
                if (v > r || u < x || u > y) {
                    continue;
                }
                ly[s2++] = u;
                sum += get_blk(br, u - 1) - get_blk(bl - 1, u - 1) - get_blk(br, x - 1) + get_blk(bl - 1, x - 1);
            }
        }

        for (int i = 0, j = 0; i < s1 && j < s2;) {
            if (lx[i] < ly[j]) {
                sum += s2 - j;
                i++;
            } else {
                j++;
            }
        }


        ll ct = 0;
        for (int j = bl; j <= br; j++) {
            int u = x == 0 ? 0 : z[j][x - 1], v = z[j][y];
            if (v > u) {
                sum += in[j][u + 1][v];
                if (j != bl) {
                    sum += get_ans(j, j - 1, v) - get_ans(j, bl - 1, v) - get_ans(j, j - 1, u) + get_ans(j, bl - 1, u) - ct * (v - u);
                }
            }
            ct += u;
        }

        cout << sum << endl;
    }

    return 0;
}

