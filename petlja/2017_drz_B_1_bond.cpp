#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[2 * N];

int calc(int xx[6], int yy[6]) {
    int x[6];
    int y[6];
    for (int i = 0; i < 6; i++) {
        x[i] = xx[i];
        y[i] = yy[i];
    }
    int tot = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            int k = min(x[i], y[j]);
            if (i > j) {
                tot += k;
            }
            x[i] -= k;
            y[j] -= k;
        }
    }
    return tot;
}
int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i];
        a[i]--;
    }
    int cntb[6] = { };
    int cntc[6] = { };
    cntc[a[1]]++;
    int sol = 0;
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            cntc[a[2 * i]]++;
            cntc[a[2 * i + 1]]++;
        }
        cntb[a[i]]++;
        sol = max(sol, calc(cntb, cntc));
        cntc[a[i + 1]]--;
    }
    cout << sol;
    return 0;

}
