//https://atcoder.jp/contests/abc393/tasks/abc393_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1200005;

int a[N];
int freq[N];
int subs[N];
int ans[N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        freq[a[i]]++;
    }
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            subs[i] += freq[j];
        }
    }
    for (int i = 1; i < N; i++) {
        if (subs[i] < k) {
            continue;
        }
        for (int j = i; j < N; j += i) {
            ans[j] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[a[i]] << endl;
    }
    return 0;
}
