//https://codeforces.com/contest/1100/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int K = 20;

int vals[N];

class Basis {
public:
    vector<int> basis;
    vector<int> node;

    Basis() : basis(vector<int>(K, 0)), node(vector<int>()) {}

    vector<int> get_basis() {
        return basis;
    }

    vector<int> get_node() {
        return node;
    }

    void insert_vector(int a, int j) {
        for (int i = K - 1; i >= 0; i--) {
            int c = a & (1 << i);
            if (!c) {
                continue;
            }
            if (!basis[i]) {
                basis[i] = a;
                node.push_back(j);
                return;
            }
            a ^= basis[i];
        }
        return;
    }

    bool exists(long long a) {
        for (int i = K - 1; i >= 0; i--) {
            int c = a & (1 << i);
            if (!c) {
                continue;
            }
            if (!basis[i]) {
                return false;
            }
            a ^= basis[i];
        }
        return true;
    }

    int get_max() {
        int ans = 0;
        for (int i = K - 1; i >= 0; i--) {
            int c = ans & (1 << i);
            if (!c) {
                ans ^= basis[i];
            }
        }
        return ans;
    }

    void inherit(Basis &b, int a, int j) {
        vector<int> parent_node = b.get_node();
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
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
        if (i == 0) {
            b[i].insert_vector(vals[i], i);
        } else {
            b[i].inherit(b[i - 1], vals[i], i);
        }
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        Basis cur;
        vector<int> node = b[r].get_node();
        for (int i = 0; i < node.size(); i++) {
            if (node[i] >= l) {
                cur.insert_vector(vals[node[i]], node[i]);
            }
        }

        cout << cur.get_max() << endl;
    }
    return 0;
}
