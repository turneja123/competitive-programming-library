//solution for https://www.spoj.com/problems/DQUERY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];
int freq[N];
int sz;

bool compare(tuple<int, int, int> tp1, tuple<int, int, int> tp2) {
    int block1 = get<0>(tp1) / sz;
    int block2 = get<0>(tp2) / sz;
    if (block1 != block2) {
        return block1 < block2;
    }
    int r1 = get<1>(tp1);
    int r2 = get<1>(tp2);
    return r1 < r2;
}

int main() {
    IOS;
    int n;
    cin >> n;
    sz = sqrt(n);
    if (sz * sz != n) {
        sz++;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    tuple<int, int, int> tp[q];
    int sol[q];
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        tp[i] = make_tuple(l, r, i);
    }
    sort(tp, tp + q, compare);
    int l = 0;
    int r = -1;
    int ct = 0;
    for (int i = 0; i < q; i++) {
        int cur = get<2>(tp[i]);
        int lcur = get<0>(tp[i]);
        int rcur = get<1>(tp[i]);
        while (r < rcur) {
            r++;
            freq[a[r]]++;
            if (freq[a[r]] == 1) {
                ct++;
            }
        }
        while (r > rcur) {
            freq[a[r]]--;
            if (freq[a[r]] == 0) {
                ct--;
            }
            r--;
        }
        while (l < lcur) {
            freq[a[l]]--;
            if (freq[a[l]] == 0) {
                ct--;
            }
            l++;
        }
        while (l > lcur) {
            l--;
            freq[a[l]]++;
            if (freq[a[l]] == 1) {
                ct++;
            }
        }
        sol[cur] = ct;
    }
    for (int i = 0; i < q; i++) {
        cout << sol[i] << endl;
    }
    return 0;
}
