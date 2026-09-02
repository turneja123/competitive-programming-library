//https://codeforces.com/contest/1600/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
vector<int> pref;
vector<int> suf;

int i_win(int l, int r, int mx) {
    if (l == r) {
        return 1;
    }
    int ans = 0;
    if (a[r] >= a[l]) {
        int j = lower_bound(suf.begin(), suf.end(), r) - suf.begin() - 1;
        int sz = r - suf[j];
        if (sz % 2 == 1) {
            ans = 1;
        }

    }
    if (a[l] >= a[r]) {
        int j = upper_bound(pref.begin(), pref.end(), l) - pref.begin();
        int sz = pref[j] - l;
        if (sz % 2 == 1) {
            ans = 1;
        }
    }
    if (a[r] > a[l] && a[l] > mx) {
        ans |= !i_win(l + 1, r, a[l]);
    }
    if (a[l] > a[r] && a[r] > mx) {
        ans |= !i_win(l, r - 1, a[r]);
    }
    return ans;
}

int main() {
    IOS;


    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        if (a[i] <= a[i - 1]) {
            pref.push_back(i);
        }
    }
    for (int i = 0; i < n - 1; i++) {
        if (a[i] <= a[i + 1]) {
            suf.push_back(i);
        }
    }
    if (i_win(0, n - 1, -1)) {
        cout << "Alice";
    } else {
        cout << "Bob";
    }


    return 0;
}
