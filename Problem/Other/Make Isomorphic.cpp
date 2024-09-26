//https://atcoder.jp/contests/abc371/tasks/abc371_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

bool g[10][10];
bool h[10][10];
int a[10][10];

int main(){
    IOS;
    int n, mg, mh;
    cin >> n >> mg;
    for (int i = 0; i < mg; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a][b] = true;
        g[b][a] = true;
    }
    cin >> mh;
    for (int i = 0; i < mh; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        h[a][b] = true;
        h[b][a] = true;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cin >> a[i][j];
            a[j][i] = a[i][j];
        }
    }
    int ans = 1e9;
    vector<int> pos;
    for (int i = 0; i < n; i++) {
        pos.push_back(i);
    }
    do {
        int cur = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (pos[i] == pos[j]) {
                    continue;
                }
                if ((g[i][j] && !h[pos[i]][pos[j]]) || (!g[i][j] && h[pos[i]][pos[j]])) {
                    cur += a[pos[i]][pos[j]];
                }
            }
        }
        ans = min(ans, cur / 2);
    } while (next_permutation(pos.begin(), pos.end()));
    cout << ans;
    return 0;
}
