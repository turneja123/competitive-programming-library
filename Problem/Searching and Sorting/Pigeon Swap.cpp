//https://atcoder.jp/contests/abc395/tasks/abc395_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int rea[N];
int label[N];
int ans[N];


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        label[i] = i;
        rea[i] = i;
        ans[i] = i;
    }

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b;
            cin >> a >> b;
            ans[a] = rea[b];
        } else if (t == 2) {
            int a, b;
            cin >> a >> b;
            int x = rea[a], y = rea[b];
            swap(label[x], label[y]);
            rea[label[x]] = x;
            rea[label[y]] = y;
        } else {
            int a;
            cin >> a;
            cout << label[ans[a]] << endl;
        }
    }
    return 0;
}
