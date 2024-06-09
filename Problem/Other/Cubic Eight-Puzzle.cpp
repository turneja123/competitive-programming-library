//https://www.spoj.com/problems/YOKOC/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int H = 40353600;
const int N = 1e6;

map<char, int> c;
gp_hash_table<int, int> mp;
//int mp[H + 1];
int q[N];
pair<int, int> comb[3][2];


map<pair<int, int>, int> id;
pair<int, int> get_id[7];
int pw[9];
int id_pair[30];
char a[3][3];

int neither(int x, int y) {
    vector<bool> b(3, 0);
    b[x] = true, b[y] = true;
    for (int i = 0; i < 3; i++) {
        if (!b[i]) {
            return i;
        }
    }
    return 0;
}

pair<int, int> transf(int x, int y, int i) {
    int a, b;
    if (i == 1) {
        b = x;
        a = y;
    } else {
        b = y;
        a = neither(x, y);
    }
    return make_pair(a, b);
}

int get_hash(vector<vector<pair<int, int>>> &v) {
    int h = 0;
    for (int i = 0, k = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++, k++) {
            h += pw[k] * id[v[i][j]];
        }
    }
    return h;
}

int bfs(vector<vector<pair<int, int>>> &sus) {
    queue<int> q;
    gp_hash_table<int, int> dist;
    int h = get_hash(sus);
    dist[h] = 0;
    q.push(h);
    int ans = 31;
    while (q.size()) {
        int h = q.front(), t = h;
        q.pop();
        int x, y, d = dist[h];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                sus[i][j] = get_id[t % 7];
                t /= 7;
                if (sus[i][j].first == -1) {
                    x = i, y = j;
                }
            }
        }
        if (d == 9) {
            continue;
        }
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) == 1 && x + dx >= 0 && x + dx < 3 && y + dy >= 0 && y + dy < 3) {
                    int t;
                    if (abs(dx) == 1) {
                        t = -1;
                    } else {
                        t = 1;
                    }
                    pair<int, int> nw = transf(sus[x + dx][y + dy].first, sus[x + dx][y + dy].second, t), temp = sus[x + dx][y + dy];
                    sus[x][y] = nw; sus[x + dx][y + dy] = make_pair(-1, -1);
                    int nw_h = h - id_pair[(temp.first + 1) * 4 + temp.second + 1] * pw[(x + dx) * 3 + y + dy] + id_pair[(nw.first + 1) * 4 + nw.second + 1] * pw[x * 3 + y];
                    auto it = dist.find(nw_h);
                    if (it == dist.end()) {
                        auto f = mp.find(nw_h);
                        if (f == mp.end()) {
                            dist[nw_h] = d + 1;
                            q.push(nw_h);
                        } else {
                            ans = min(ans, f->second + d + 1);
                        }
                    }
                    sus[x][y] = make_pair(-1, -1); sus[x + dx][y + dy] = temp;
                }
            }
        }
    }
    return ans;
}

int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < 9; i++) {
        pw[i] = pw[i - 1] * 7;
    }
    /*for (int i = 0; i <= H; i++) {
        mp[i] = -1;
    }*/
    c['W'] = 0;
    c['B'] = 1;
    c['R'] = 2;
    comb[0][0] = make_pair(0, 1), comb[0][1] = make_pair(0, 2);
    comb[1][0] = make_pair(1, 0), comb[1][1] = make_pair(1, 2);
    comb[2][0] = make_pair(2, 0), comb[2][1] = make_pair(2, 1);
    id[make_pair(-1, -1)] = 0;
    id[make_pair(0, 1)] = 1;
    id[make_pair(0, 2)] = 2;
    id[make_pair(1, 0)] = 3;
    id[make_pair(1, 2)] = 4;
    id[make_pair(2, 0)] = 5;
    id[make_pair(2, 1)] = 6;
    for (auto it = id.begin(); it != id.end(); ++it) {
        get_id[it->second] = it->first;
        id_pair[(it->first.first + 1) * 4 + it->first.second + 1] = it->second;
    }
    int x, y;
    cin >> x >> y;
    while (!(x == 0 && y == 0)) {
        x--, y--;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cin >> a[i][j];
            }
        }
        vector<vector<pair<int, int>>> sus(3, vector<pair<int, int>>(3));
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                sus[i][j] = make_pair(0, 1);
            }
        }
        int qs = 0;
        sus[y][x] = make_pair(-1, -1);
        int h = get_hash(sus);
        q[qs++] = h;
        mp[h] = 0;
        sus[y][x] = make_pair(0, 1);
        int ct = 0, mx = 0, ans = -1;
        int qp = 0;
        while (qp < qs) {
            ct++;
            int h = q[qp], t = h;
            mx = max(mx, h);
            qp++;
            int x, y, d = mp[h], k = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    sus[i][j] = get_id[t % 7];
                    t /= 7;
                    if (sus[i][j].first == -1) {
                        x = i, y = j;
                    }
                    if (sus[i][j].first == -1 && a[i][j] == 'E') {
                        k++;
                    }
                    if (sus[i][j].first == 0 && a[i][j] == 'W') {
                        k++;
                    }
                    if (sus[i][j].first == 1 && a[i][j] == 'B') {
                        k++;
                    }
                    if (sus[i][j].first == 2 && a[i][j] == 'R') {
                        k++;
                    }
                }
            }
            if (k == 9) {
                ans = d;
                break;
            }
            if (d == 21) {
                continue;
            }
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dx) + abs(dy) == 1 && x + dx >= 0 && x + dx < 3 && y + dy >= 0 && y + dy < 3) {
                        int t;
                        if (abs(dx) == 1) {
                            t = -1;
                        } else {
                            t = 1;
                        }
                        pair<int, int> nw = transf(sus[x + dx][y + dy].first, sus[x + dx][y + dy].second, t), temp = sus[x + dx][y + dy];
                        sus[x][y] = nw; sus[x + dx][y + dy] = make_pair(-1, -1);
                        int nw_h = h - id_pair[(temp.first + 1) * 4 + temp.second + 1] * pw[(x + dx) * 3 + y + dy] + id_pair[(nw.first + 1) * 4 + nw.second + 1] * pw[x * 3 + y];
                        auto it = mp.find(nw_h);
                        if (it == mp.end()) {
                            mp[nw_h] = d + 1;
                            q[qs++] = nw_h;
                        }
                       /* if (mp[nw_h] == -1) {
                            mp[nw_h] = d + 1;
                            q[qs++] = nw_h;
                        }*/
                        sus[x][y] = make_pair(-1, -1); sus[x + dx][y + dy] = temp;
                    }
                }
            }
            if (ct % 10000 == 0) {
                //cout << ct << " " << d << endl;
            }
        }
        if (ans != -1) {
            cout << ans << endl;
        } else {
            ans = 31;
            for (int mask = 0; mask < 256; mask++) {
                for (int i = 0, k = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (a[i][j] == 'E') {
                            sus[i][j] = make_pair(-1, -1);
                        } else {
                            sus[i][j] = comb[c[a[i][j]]][((mask & (1 << k)) ? 1 : 0)];
                            k++;
                        }
                    }
                }
                ans = min(ans, bfs(sus));
            }
            if (ans <= 30) {
                cout << ans << endl;
            } else {
                cout << -1 << endl;
            }
        }
       /* for (int i = 0; i < qs; i++) {
            mp[q[i]] = -1;
        }*/
        mp.clear();
        cin >> x >> y;
    }
    return 0;
}
