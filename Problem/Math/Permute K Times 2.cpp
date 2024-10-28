//https://atcoder.jp/contests/abc377/tasks/abc377_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int p[N];
bool vis[N];
int ans[N];

long long modPow(long long a, long long y, long long M) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

int main() {
    IOS;
    int n; long long k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        p[a[i]] = i;
    }

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            int u = i; vector<int> pos;
            while (!vis[u]) {
                vis[u] = true;
                pos.push_back(u);
                u = p[u];
            }
            int l = pos.size();
            long long m = (modPow(2, k, l) - 1 + l) % l;
            for (int j = 0; j < pos.size(); j++) {
                ans[pos[(j + m) % l]] = a[pos[j]];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << " ";
    }

    return 0;
}
