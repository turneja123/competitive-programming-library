//https://codeforces.com/contest/2064/problem/D
#include bitsstdc++.h
#include extpb_dsassoc_container.hpp

using namespace std;
using namespace __gnu_pbds;

#define endl n
#define IOS ios_basesync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;
const int MAX = 13000000;
const int K = 30;

struct Node {
    int left;
    int right;
    int val;
    Node()  left(-1), right(-1), val(0) {}
};

Node nodes[MAX];
int idx = 0;
int ans[N];

int query(int node, int d, int val, int ans) {
    if (d == -1) {
        return ans;
    }
    int c = val & (1  d);
    if (c == 0) {
        if (nodes[node].left != -1 && nodes[nodes[node].left].val  0) {
            return query(nodes[node].left, d - 1, val, ans);
        } else {
            return query(nodes[node].right, d - 1, val, ans ^ (1  d));
        }
    } else {
        if (nodes[node].right != -1 && nodes[nodes[node].right].val  0) {
            return query(nodes[node].right, d - 1, val, ans);
        } else {
            return query(nodes[node].left, d - 1, val, ans ^ (1  d));

        }
    }
}

void add(int node, int d, int val, int ad) {
    nodes[node].val += ad;
    if (d  0) {
        return;
    }
    int c = val & (1  d);
    if (c == 0) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].left, d - 1, val, ad);
        return;
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].right, d - 1, val, ad);
        return;
    }
}


int main() {
    IOS;
    int t;
    cin  t;
    while (t--) {
        nodes[idx++] = Node();
        int n, q;
        cin  n  q;
        vectorint s(n);
        for (int i = 0; i  n; i++) {
            cin  s[i];
        }
        reverse(s.begin(), s.end());
        vectorpairint, int queries(q);
        setpairint, int rem;

        for (int i = 0; i  q; i++) {
            cin  queries[i].first;
            queries[i].second = i;
            rem.insert(make_pair(queries[i].first, i));
            add(0, K, queries[i].first, 1);
        }
        int sum = 0;
        for (int i = 0; i  n; i++) {
            while (rem.size()) {
                int mn = query(0, K, sum, 0);
                if (mn = s[i]) {
                    break;
                }
                int cur = mn ^ sum;
                auto it = rem.lower_bound(make_pair(cur, -1));
                ans[it-second] = i;
                rem.erase(it);
                add(0, K, cur, -1);
            }
            sum ^= s[i];
        }
        while (rem.size()) {
            auto it = rem.begin();
            ans[it-second] = n;
            rem.erase(it);
        }
        for (int i = 0; i  q; i++) {
            cout  ans[i]   ;
        }
        cout  endl;
        idx = 0;
    }
    return 0;
}
