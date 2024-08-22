//https://atcoder.jp/contests/abc330/tasks/abc330_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

const int N = 2e5 + 5;
const int B = 450;

int a[N];
int ct[N];
int freq[N];

int query() {
    int j = 0;
    while (ct[j] == B) {
        j++;
    }
    for (int i = B * j; i < B * (j + 1); i++) {
        if (freq[i] == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] < N) {
            freq[a[i]]++;
            if (freq[a[i]] == 1) {
                ct[a[i] / B]++;
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int j, x;
        cin >> j >> x;
        j--;
        if (a[j] < N) {
            freq[a[j]]--;
            if (freq[a[j]] == 0) {
                ct[a[j] / B]--;
            }
        }
        a[j] = x;
        if (a[j] < N) {
            freq[a[j]]++;
            if (freq[a[j]] == 1) {
                ct[a[j] / B]++;
            }
        }
        cout << query() << endl;
    }
    return 0;
}
