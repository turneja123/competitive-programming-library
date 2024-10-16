//https://www.spoj.com/problems/ADAGAME2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

const int N = 1e5 + 5;

int a[N];
int grundy[N];
vector<int> mov;

void calc(int n) {
    grundy[0] = 0;
    for (int i = 1; i <= n; i++) {
        vector<bool> seen(mov.size() + 1, false);
        for (int j : mov) {
            if (j > i) {
                break;
            }
            seen[grundy[i - j]] = true;
        }
        for (int j = 0; j <= mov.size(); j++) {
            if (!seen[j]) {
                grundy[i] = j;
                break;
            }
        }
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        mov.resize(m);
        for (int i = 0; i < m; i++) {
            cin >> mov[i];
        }
        int mx = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mx = max(mx, a[i]);
        }
        sort(mov.begin(), mov.end());
        calc(mx);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum ^= grundy[a[i]];
        }
        if (sum > 0) {
            cout << "Ada" << endl;
        } else {
            cout << "Vinit" << endl;
        }
        mov.clear();
    }
    return 0;
}
