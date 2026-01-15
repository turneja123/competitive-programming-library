//https://codeforces.com/contest/1305/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 18;

int freq[1 << K];
int parent[1 << K];
int sz[1 << K];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

int main() {
    IOS;
    int n;
    cin >> n;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        freq[a]++;
        ans -= a;
    }
    freq[0]++;
    for (int i = 0; i < 1 << K; i++) {
        sz[i] = 1;
        parent[i] = i;
    }
    for (int i = (1 << K) - 1; i >= 0; i--) {
        for (int j = i; j > 0; j = (j - 1) & i) {
            int k = i ^ j;
            if (freq[j] && freq[k]) {
                int a = dsu_find(j), b = dsu_find(k);
                if (a != b) {
                    ans += (ll)(freq[j] + freq[k] - 1) * i;
                    freq[j] = 1;
                    freq[k] = 1;
                    dsu_unite(a, b);

                }
            }
        }
    }
    cout << ans;
    return 0;
}
