//bbc18q
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct Sparse {
    vector<int> a;
    vector<vector<int>> table;
    int n;

    Sparse(vector<int> _a) {
        a = _a;
        n = a.size();
        table.resize(20, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            table[0][i] = a[i];
        }
        for (int j = 1; j < 20; j++) {
            for (int i = 0; i < n; i++) {
                int r = i + (1 << j) - 1;
                if (r < n) {
                    int mid = i + (1 << (j - 1)) - 1;
                    table[j][i] = min(table[j - 1][i], table[j - 1][mid + 1]);
                }
            }
        }
    }

    int query(int l, int r) {
        int j = 31 - __builtin_clz(r - l + 1);
        return min(table[j][l], table[j][l + (r - l + 1 - (1 << j))]);
    }

};

int main() {
    IOS;
    int n, q;
    cin >> n;
    vector<int> a(n);
    vector<int> a_rising_pos(n), a_falling_pos(n);
    vector<int> a_rising_neg(n), a_falling_neg(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a_rising_pos[i] = a[i] + 2 * i;
        a_falling_pos[i] = a[i] + 2 * (n - 1 - i);

        a_rising_neg[i] = -a[i] + 2 * i;
        a_falling_neg[i] = -a[i] + 2 * (n - 1 - i);
    }
    Sparse sparse(a);
    Sparse sparse_rising_pos(a_rising_pos);
    Sparse sparse_falling_pos(a_falling_pos);

    Sparse sparse_rising_neg(a_rising_neg);
    Sparse sparse_falling_neg(a_falling_neg);
    cin >> q;
    while (q--) {
        int i, xi, j, xj;
        cin >> i >> xi >> j >> xj;
        i--, j--;
        int l = min(i, j), r = max(i, j);
        if (xi <= xj) {
            int mn = min(xi, sparse.query(l, r));
            int ans = r - l + xj - mn;
            cout << ans << endl;
            continue;
        }
        int mn = min(xi, sparse.query(l, r));
        if (mn <= xj) {
            int ans = r - l + xj - mn;
            cout << ans << endl;
            continue;
        }
        int ans = r - l + mn - xj;

        int lf = 0, rt = l, spl = -1;
        while (lf <= rt) {
            int mid = (lf + rt) / 2;
            int x = sparse.query(mid, l);
            if (x < xj) {
                spl = mid;
                lf = mid + 1;
            } else {
                rt = mid - 1;
            }
        }
        ans = min(ans, r - l + sparse_falling_pos.query(spl + 1, l) - 2 * (n - 1 - l) - xj);
        if (spl != -1) {
            ans = min(ans, r - l + sparse_falling_neg.query(spl, spl) - 2 * (n - 1 - l) + xj);
        }

        lf = r, rt = n - 1, spl = n;
        while (lf <= rt) {
            int mid = (lf + rt) / 2;
            int x = sparse.query(r, mid);
            if (x < xj) {
                spl = mid;
                rt = mid - 1;
            } else {
                lf = mid + 1;
            }
        }
        ans = min(ans, r - l + sparse_rising_pos.query(r, spl - 1) - 2 * r - xj);
        if (spl != n) {
            ans = min(ans, r - l + sparse_rising_neg.query(spl, spl) - 2 * r + xj);
        }
        cout << ans << endl;
    }
    return 0;
}
