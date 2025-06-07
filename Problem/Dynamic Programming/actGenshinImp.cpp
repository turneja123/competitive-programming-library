//https://codeforces.com/gym/105698/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const long long M = 998244353;

string s[N];
int dp1[N][N];
int dp2[N][N];
map<pair<int, int>, int> dp1_i[N][N];
map<pair<int, int>, int> dp1_n[N][N];
map<tuple<int, int, int, int>, int> dp1_in[N][N];

map<pair<int, int>, int> dp2_i[N][N];
map<pair<int, int>, int> dp2_n[N][N];
map<tuple<int, int, int, int>, int> dp2_in[N][N];

bool seen[N][N];

vector<pair<int, int>> moves{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
string a = "", b = "";
int n, m;
int gox, goy;

void calc1(int x, int y, int i, int xi, int yi, int xn, int yn) {
    seen[x][y] = true;
    if (i == 7) {
        dp1[x][y]++;
        dp1_i[x][y][{xi, yi}]++;
        dp1_n[x][y][{xn, yn}]++;
        dp1_in[x][y][{xi, yi, xn, yn}]++;
        seen[x][y] = false;
        return;
    }
    for (int j = 0; j < 4; j++) {
        auto [dx, dy] = moves[j];
        if (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && !seen[x + dx][y + dy] && s[x + dx][y + dy] == a[i]) {
            if (a[i] == 'i') {
                calc1(x + dx, y + dy, i + 1, x + dx, y + dy, xn, yn);
            } else if (a[i] == 'n') {
                calc1(x + dx, y + dy, i + 1, xi, yi, x + dx, y + dy);
            } else {
                calc1(x + dx, y + dy, i + 1, xi, yi, xn, yn);
            }
        }
    }
    seen[x][y] = false;
}

void calc2(int x, int y, int i, int xi, int yi, int xn, int yn) {
    seen[x][y] = true;
    if (i == 6) {
        dp2[gox][goy]++;
        dp2_i[gox][goy][{xi, yi}]++;
        dp2_n[gox][goy][{xn, yn}]++;
        dp2_in[gox][goy][{xi, yi, xn, yn}]++;
        seen[x][y] = false;
        return;
    }
    for (auto [dx, dy] : moves) {
        if (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && !seen[x + dx][y + dy] && s[x + dx][y + dy] == b[i]) {
            if (b[i] == 'i') {
                calc2(x + dx, y + dy, i + 1, x + dx, y + dy, xn, yn);
            } else if (b[i] == 'n') {
                calc2(x + dx, y + dy, i + 1, xi, yi, x + dx, y + dy);
            } else {
                calc2(x + dx, y + dy, i + 1, xi, yi, xn, yn);
            }
        }
    }
    seen[x][y] = false;
}


int main() {
    IOS;
    string e = "genshinimpact";
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    long long ans = 0;
    for (int k = 0; k < 13; k++) {
        int i = 0;
        a = "", b = "";
        for (; i < 7; i++) {
            a += e[(i + k) % 13];
        }
        for (; i < 13; i++) {
            b += e[(i + k) % 13];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dp1[i][j] = 0;
                dp2[i][j] = 0;
                dp1_i[i][j].clear();
                dp2_i[i][j].clear();
                dp1_n[i][j].clear();
                dp2_n[i][j].clear();
                dp1_in[i][j].clear();
                dp2_in[i][j].clear();
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (s[i][j] == a[0]) {
                    calc1(i, j, 1, ((a[0] == 'i') ? i : -1), ((a[0] == 'i') ? j : -1), ((a[0] == 'n') ? i : -1), ((a[0] == 'n') ? j : -1));

                }
                if (s[i][j] == b[0]) {
                    gox = i, goy = j;
                    calc2(i, j, 1, ((b[0] == 'i') ? i : -1), ((b[0] == 'i') ? j : -1), ((b[0] == 'n') ? i : -1), ((b[0] == 'n') ? j : -1));
                }
            }
        }
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                if (dp1[x][y] == 0) {
                    continue;
                }
                for (auto it = dp1_in[x][y].begin(); it != dp1_in[x][y].end(); ++it) {
                    auto [xi, yi, xn, yn] = it->first;
                    for (auto [dx, dy] : moves) {
                        if (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m) {
                            int ct = dp2[x + dx][y + dy];
                            auto fi = dp2_i[x + dx][y + dy].find({xi, yi});
                            if (fi != dp2_i[x + dx][y + dy].end() && xi != -1) {
                                ct -= fi->second;
                            }
                            auto fn = dp2_n[x + dx][y + dy].find({xn, yn});
                            if (fn != dp2_n[x + dx][y + dy].end() && xn != -1) {
                                ct -= fn->second;
                            }
                            auto fin = dp2_in[x + dx][y + dy].find(it->first);
                            if (fin != dp2_in[x + dx][y + dy].end() && xi != -1 && xn != -1) {
                                ct += fin->second;
                            }
                            ans = (ans + (long long)it->second * ct) % M;
                        }
                    }
                }
            }
        }
    }
    cout << ans;

    return 0;
}
