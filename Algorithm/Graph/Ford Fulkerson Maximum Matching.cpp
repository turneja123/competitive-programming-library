#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
bool bigraf[N][N];

bool bpm(int u, bool seen[], int match[], int m) {
    for (int v = 0; v < m; v++) {
        if (bigraf[u][v] && !seen[v]) {
            seen[v] = true;
            if (match[v] < 0 || bpm(match[v], seen, match, m)) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        bigraf[x][y] = 1;
    }
    int match[m];
    memset(match, -1, sizeof(match));
    int sol = 0;
    for (int i = 0; i < m; i++) {
        bool seen[m] = { };
        if (bpm(i, seen, match, m)) {
            sol++;
        }
    }
    cout << sol;
    return 0;

}
