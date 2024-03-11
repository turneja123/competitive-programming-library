//solution for https://dmoj.ca/problem/2drmq
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const int M = 11;

int table[M][M][N][N];
int lg[N];

void init(std::vector<std::vector<int>> arr) {
    lg[1] = 0;
    for (int i = 2; i < N; i++) {
        lg[i] = lg[i / 2] + 1;
    }
    int n = arr.size(), m = n;
    int K = ceil(log2(n)) + 1;
    for (int x = 0; x < K; x++) {
        for (int y = 0; y < K; y++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (i + (1 << x) - 1 > n || j + (1 << y) - 1 > m) {
                        continue;
                    }
                    if (x == 0 && y == 0) {
                        table[0][0][i][j] = arr[i][j];
                    } else if (x > 0) {
                        table[x][y][i][j] = min(table[x - 1][y][i][j], table[x - 1][y][i + (1 << (x - 1))][j]);
                    } else if (y > 0) {
                        table[x][y][i][j] = min(table[x][y - 1][i][j], table[x][y - 1][i][j + (1 << (y - 1))]);
                    }
                }
            }
        }
    }
}

int query(int a, int b, int c, int d) {
    int x1 = a, y1 = c, x2 = b, y2 = d;
    int x = lg[x2 - x1 + 1], y = lg[y2 - y1 + 1];
    return min(min(table[x][y][x1][y1], table[x][y][x2 - (1 << x) + 1][y1]),
               min(table[x][y][x1][y2 - (1 << y) + 1], table[x][y][x2 - (1 << x) + 1][y2 - (1 << y) + 1]));
}

int main() {
    IOS;

    return 0;
}
