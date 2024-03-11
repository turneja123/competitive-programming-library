//https://dmoj.ca/problem/hhpc1p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];
int prefzero[N], freqa[N], freq[N], nearest[N], nearestneg[N], ans[N];

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < N - 1; i++) {
        nearest[i] = -1;
        nearestneg[i] = -1;
    }
    int l = -1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 0) {
            prefzero[i] += 1;
        } else {
            freq[abs(a[i])] += 1;
            freqa[i] = freq[abs(a[i])];
            if (a[i] > 0) {
                nearest[a[i]] = i;
                l = max(l, nearestneg[a[i]]);
            }
            if (a[i] < 0) {
                nearestneg[abs(a[i])] = i;
                l = max(l, nearest[abs(a[i])]);
            }
        }
        ans[i] = l;
        if (i > 0) {
            prefzero[i] += prefzero[i - 1];
        }
    }
    for (int i = 0; i < q; i++) {
        int lq, rq;
        cin >> lq >> rq;
        lq--, rq--;
        int zeroes = prefzero[rq];
        if (lq) {
            zeroes -= prefzero[lq - 1];
        }
        if (zeroes) {
            cout << "YES" << endl;
        } else if (a[rq] == a[lq] && freqa[rq] - freqa[lq] == rq - lq) {
            cout << "YES" << endl;
        } else if (ans[rq] >= lq ) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
