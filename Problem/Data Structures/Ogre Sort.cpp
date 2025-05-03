//https://algotester.com/en/ArchiveProblem/DisplayWithFile/71141
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int a[N];
int pos[N];

struct BIT {
    int n;
    vector<long long> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, long long val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    void upd(int l, int r, long long val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    long long query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
};

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    BIT bit(n);
    int r = n;
    for (int i = n; i > 0; i--) {
        if (r == a[i]) {
            r--;
        }
    }
    cout << r << " " << r << endl;
    for (int i = r; i > 0; i--) {
        int j = bit.query(pos[i]) + pos[i];
        cout << j << " " << 1 << endl;
        bit.upd(1, pos[i], 1);
    }
    return 0;
}
