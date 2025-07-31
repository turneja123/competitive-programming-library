//https://www.codechef.com/problems/SEGPROD
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int K = 21;
long long M;

struct Data {
    long long x;
    Data() {
        x = 0;
    }
    Data(int _x) {
        x = _x;
    }
};

Data dat[K][N];
int mask[N];
int a[N];

Data combine(Data left, Data right) {
    Data data;
    data.x = left.x * right.x % M;
    return data;
}

void calc(int l, int r, int lev) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    dat[lev][mid] = Data(a[mid]);
    for (int i = mid - 1; i >= l; i--) {
        Data data = Data(a[i]);
        dat[lev][i] = combine(data, dat[lev][i + 1]);
    }
    dat[lev][mid + 1] = Data(a[mid + 1]);
    for (int i = mid + 2; i <= r; i++) {
        Data data = Data(a[i]);
        dat[lev][i] = combine(dat[lev][i - 1], data);
    }
    for (int i = mid + 1; i <= r; i++) {
        mask[i] ^= 1 << lev;
    }
    calc(l, mid, lev + 1);
    calc(mid + 1, r, lev + 1);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> M >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<int> b;
        for (int i = 0; i < q / 64 + 2; i++) {
            int x;
            cin >> x;
            b.push_back(x);
        }
        calc(0, n - 1, 0);
        int last = 0, l, r;
        for (int i = 0; i < q; i++) {
            if (i % 64 == 0) {
                l = (b[i / 64] + last) % n;
                r = (b[i / 64 + 1] + last) % n;
            } else {
                l = (l + last) % n;
                r = (r + last) % n;
            }
            if (l > r) {
                swap(l, r);
            }
            if (l == r) {
                last = (a[l] + 1) % M;
            } else {
                int k = __builtin_ctz(mask[l] ^ mask[r]);
                Data data = combine(dat[k][l], dat[k][r]);
                last = (data.x + 1) % M;
            }
        }
        cout << last << endl;
        for (int i = 0; i < n; i++) {
            mask[i] = 0;
        }
    }


    return 0;
}
