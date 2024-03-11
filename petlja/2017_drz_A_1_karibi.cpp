#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;

int n, m, a, b;
char c[N][N];
pair <int,int> hor[N][N];
pair <int,int> ver[N][N];

void init_horizontal() {
    for (int i = 0; i < n; i++) {
        int start = 0;
        for (int j = 0; j < m; j++) {
            if (c[i][j] == '1') {
                hor[i][j] = {-1, -1};
                for (int k = start; k < j; k++) {
                    hor[i][k] = {k - start, j - start};
                }
                start = j + 1;
            } else if (j == m - 1) {
                for (int k = start; k < m; k++) {
                    hor[i][k] = {k - start, m - start};
                }
            }
        }
    }
}

void init_vertical() {
    for (int j = 0; j < m; j++) {
        int start = 0;
        for (int i = 0; i < n; i++) {
            if (c[i][j] == '1') {
                ver[i][j] = {-1, -1};
                for (int k = start; k < i; k++) {
                    ver[k][j] = {k - start, i - start};
                }
                start = i + 1;
            } else if (i == n - 1) {
                for (int k = start; k < n; k++) {
                    ver[k][j] = {k - start, n - start};
                }
            }
        }
    }
}

int calc_total() {
    int total = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
        {
            if (hor[i][j].second - hor[i][j].first >= b) {
                total++;
            }
            if (ver[i][j].second - ver[i][j].first >= b) {
                total++;
            }
        }
    }
    return total;
}


int calc_diff(int l, int r) {
    int total = max(0, r - b + 1);
    int f = max(0, l - b + 1);
    int s = max(0, r - l - b);
    return total - f - s;
}

int main()
{
    IOS;
    cin >> n >> m >> a >> b;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> c[i][j];
        }
    }

    init_horizontal();
    init_vertical();
    int total = calc_total();
    int sol = total;

    for (int i = 0; i < n; i++) {
        int cur = 0;
        for (int j = 0; j < a; j++) {
            cur += calc_diff(ver[i][j].first, ver[i][j].second);
        }
        for (int j = 0; j < m; j++) {
            int l = j;
            int r = j + a;
            if (r > m) {
                break;
            }
            if (hor[i][j].second - hor[i][j].first >= a) {
                int tot = max(0, hor[i][j].second - b + 1);
                int f = max(0, hor[i][j].first - b + 1);
                int s = max(0, hor[i][j].second - hor[i][j].first - a - b + 1);
                sol = min(sol, total - cur - (tot - f - s));
            }
            if (r != m) {
                cur -= calc_diff(ver[i][l].first, ver[i][l].second);
                cur += calc_diff(ver[i][r].first, ver[i][r].second);
            }
        }
    }

    for (int j = 0; j < m; j++) {
        int cur = 0;
        for (int i = 0; i < a; i++) {
            cur += calc_diff(hor[i][j].first, hor[i][j].second);
        }
        for (int i = 0; i < n; i++) {
            int l = i;
            int r = i + a;
            if (r > n) {
                break;
            }
            if (ver[i][j].second - ver[i][j].first >= a) {
                int tot = max(0, ver[i][j].second - b + 1);
                int f = max(0, ver[i][j].first - b + 1);
                int s = max(0, ver[i][j].second - ver[i][j].first - a - b + 1);
                sol = min(sol, total - cur - (tot - f - s));
            }
            if (r != n) {
                cur -= calc_diff(hor[l][j].first, hor[l][j].second);
                cur += calc_diff(hor[r][j].first, hor[r][j].second);
            }
        }
    }

    cout << sol;
    return 0;


}
