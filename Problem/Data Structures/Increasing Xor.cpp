//https://codeforces.com/contest/2143/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 20;

int vals[N];

class Basis {
public:
    vector<int> basis;
    vector<int> node;
    int sz;

    Basis() : basis(vector<int>(K, 0)), node(vector<int>()), sz(0) {}

    void insert_vector(int a, int j) {
        for (int i = K - 1; i >= 0; i--) {
            int c = a & (1 << i);
            if (!c) {
                continue;
            }
            if (!basis[i]) {
                basis[i] = a;
                sz++;
                node.push_back(j);
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

    void inherit(Basis &b, int a, int j) {
        vector<int> parent_node = b.node;
        insert_vector(a, j);
        for (int i = 0; i < parent_node.size(); i++) {
            insert_vector(vals[parent_node[i]], parent_node[i]);
        }
        return;
    }
};

Basis b[N];


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> vals[i];
        }
        for (int i = n - 1; i >= 0; i--) {
            if (i == n - 1) {
                b[i].insert_vector(vals[i], i);
            } else {
                b[i].inherit(b[i + 1], vals[i], i);
            }
        }
        for (int e = 0; e < q; e++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            Basis cur;
            vector<int> node = b[l].node;
            vector<int> v;
            for (int i = 0; i < node.size(); i++) {
                if (node[i] <= r) {
                    v.push_back(node[i]);
                }
            }
            sort(v.begin(), v.end());
            string ans = "YES";
            int last = -1;
            for (int i = 0; i < v.size(); i++) {
                cur.insert_vector(vals[v[i]], i);
                int j = cur.order_of_key(last + 1);
                int ival = (i == v.size() - 1 ? r + 1 : v[i + 1]) - v[i];
                if (j + ival > (1 << i + 1)) {
                    ans = "NO";
                    break;
                }
                last = cur.get_kth(j + ival);
            }
            cout << ans << endl;
        }
        for (int i = 0; i < n; i++) {
            b[i] = Basis();
        }
    }
    return 0;
}
