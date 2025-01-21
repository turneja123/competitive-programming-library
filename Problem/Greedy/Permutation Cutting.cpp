//https://dmoj.ca/problem/yac9p1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N], b[N];
int pa[N], pb[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n; i++) {
        pa[a[i]] = a[i + 1];
        pb[b[i]] = b[i + 1];
    }
    int ans = n;
    for (int i = 1; i <= n; i++) {
        if (pa[i] == pb[i] && pa[i] != 0 && pb[i] != 0) {
            ans--;
        }
    }
    cout << ans;
    return 0;
}
