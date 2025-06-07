//https://codeforces.com/contest/2018/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int pa[N], sa[N];
int ans = 0;

multiset<int> stp, sts;

void calc(int l, int r, int n) {
    if (l > r) {
        return;
    }
    if (l == r) {
        ans++;
        return;
    }
    if (a[l] < r - l + 1 && a[r] < r - l + 1) {
        return;
    }
    if (a[l] >= r - l + 1 && a[r] >= r - l + 1) {
        if (*stp.begin() + l > 0) {
            ans++;
        }
        if (*sts.begin() + n - 1 - r > 0) {
            ans++;
        }
        stp.erase(stp.find(pa[l]));
        stp.erase(stp.find(pa[r]));
        sts.erase(sts.find(sa[l]));
        sts.erase(sts.find(sa[r]));
        calc(l + 1, r - 1, n);
        return;
    }
    if (a[l] >= r - l + 1) {
        stp.erase(stp.find(pa[l]));
        sts.erase(sts.find(sa[l]));
        calc(l + 1, r, n);
    } else {
        stp.erase(stp.find(pa[r]));
        sts.erase(sts.find(sa[r]));
        calc(l, r - 1, n);
    }

}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            pa[i] = a[i] - i;
            sa[i] = a[i] - (n - 1 - i);
            stp.insert(pa[i]);
            sts.insert(sa[i]);
        }
        ans = 0;
        calc(0, n - 1, n);
        cout << ans << endl;
        stp.clear();
        sts.clear();
    }
    return 0;
}
