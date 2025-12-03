//https://cses.fi/problemset/task/3192
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 30;

int vals[N];

class Basis {
public:
    vector<int> basis;
    int sz;

    Basis() : basis(vector<int>(K, 0)), sz(0) {}

    void insert_vector(int a) {
        for (int i = K - 1; i >= 0; i--) {
            int c = a & (1 << i);
            if (!c) {
                continue;
            }
            if (!basis[i]) {
                basis[i] = a;
                sz++;
                return;
            }
            a ^= basis[i];
        }
        return;
    }

    int get_kth(int k) {
        int ans = 0, s = 1 << sz;
        for (int i = K - 1; i >= 0; i--) {
            if (!basis[i]) {
                continue;
            }
            if ((s / 2 < k && (ans & 1 << i) == 0) || (s / 2 >= k && (ans & 1 << i) > 0)) {
                ans ^= basis[i];
            }
            if (s / 2 < k) {
                k -= s / 2;
            }
            s /= 2;
        }
        return ans;
    }

    int order_of_key(int x) {
        int ct = 1, ans  = 0, cur = 0;
        for (int i = K - 1; i >= 0; --i) {
            int k = (x >> i) & 1, j = (cur >> i) & 1;
            if (basis[i]) {
                int need = j ^ k;
                if (need) {
                    cur ^= basis[i];
                }
                ans *= 2;
                if (k) {
                    ans += ct;
                }
            } else {
                if (j < k) {
                    ans += ct;
                    ct = 0;
                } else if (j > k) {
                    ct = 0;
                }
            }
        }
        return ans;
    }
};

int main() {
    IOS;
    Basis b;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        b.insert_vector(a);
    }
    for (int i = 1, j = k; j > 0 && i <= k; i++) {
        int x = b.get_kth(i), p = n - b.sz;
        if (p > 20) {
            while (j--) {
                cout << x << " ";
            }
            break;
        }
        for (int y = 0; y < 1 << p && j > 0; y++, j--) {
            cout << x << " ";
        }
    }
    return 0;
}
