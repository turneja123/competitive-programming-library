//https://basecamp.eolymp.com/en/problems/11857
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e7 + 5;

bool seen[N];
int last[N];
int md[N];
int ans[N];

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    int mn = N, mx = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        seen[a] = true;
        mn = min(mn, a);
        mx = max(mx, a);
    }
    last[N - 1] = (seen[N - 1] ? N - 1 : -1);
    for (int i = N - 2; i >= 0; i--) {
        last[i] = (seen[i] ? i : last[i + 1]);
    }
    md[1] = 0;
    for (int i = 2; i < N; i++) {
        md[i] = i - 1;
        for (int j = 0; i * j < N; j++) {
            int nx = last[i * j];
            if (nx == -1) {
                break;
            }
            if (md[i] == 0) {
                break;
            }
            if (nx < i * (j + 1)) {
                md[i] = min(md[i], nx - i * j);
            }
        }
    }
    for (int i = 1; i < N; i++) {
        ans[i - md[i]] = i;
    }
    for (int i = 1; i < N; i++) {
        ans[i] = max(ans[i], ans[i - 1]);
    }
    while (q--) {
        long long c;
        cin >> c;
        if (c + mn > mx) {
            cout << c + mn << endl;
        } else {
            cout << ans[c] << endl;
        }
    }
    return 0;
}
