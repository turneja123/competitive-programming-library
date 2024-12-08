//https://codeforces.com/contest/2042/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

tuple<int, int, int> a[N];
map<pair<int, int>, int> mp;

map<int, multiset<int>> edge;

multiset<int> st;

const int R = 1e9 + 5;
const int MAX = 1e7 + 5;

int ans[N];

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int query(int node, int l, int r, int lq, int rq) {
    if (r < lq || l > rq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node].val;
    }
    int mid = (l + r) / 2, ans = 0;
    if (nodes[node].left != -1) {
        ans = max(ans, query(nodes[node].left, l, mid, lq, rq));
    }
    if (nodes[node].right != -1) {
        ans = max(ans, query(nodes[node].right, mid + 1, r, lq, rq));
    }
    return ans;

}

void update(int node, int l, int r, int ind, int val) {
    if (l == r) {
        nodes[node].val = max(nodes[node].val, val);
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].left, l, mid, ind, val);
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].right, mid + 1, r, ind, val);
    }
    nodes[node].val = 0;
    if (nodes[node].left != -1) {
        nodes[node].val = max(nodes[node].val, nodes[nodes[node].left].val);
    }
    if (nodes[node].right != -1) {
        nodes[node].val = max(nodes[node].val, nodes[nodes[node].right].val);
    }
}

int main() {
    IOS;

    int t;
    cin >> t;
    while (t--) {
        mp.clear();
        edge.clear();
        st.clear();
        idx = 0;
        nodes[idx++] = Node();
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int l, r;
            cin >> l >> r;
            a[i] = make_tuple(l, r, i);
            mp[make_pair(l, r)]++;
        }
        sort(a, a + n);
        for (int i = 0, j = 0; i < n; i++) {
            auto [l, r, ind] = a[i];
            while (j < n && get<0>(a[j]) <= l) {
                update(0, 0, R - 1, get<1>(a[j]), get<0>(a[j]));
                st.insert(get<1>(a[j]));
                edge[get<1>(a[j])].insert(get<0>(a[j]));

                j++;
            }
            if (mp[make_pair(l, r)] > 1) {
                ans[ind] = 0;
                continue;
            }
            int lf = query(0, 0, R - 1, r + 1, R - 1);
            auto it = st.lower_bound(r);
            it++;
            if (it != st.end()) {
                int rt = *it;
                edge[r].erase(edge[r].find(l));
                if (edge[r].size() > 0) {
                    lf = max(lf, *edge[r].rbegin());
                    rt = r;
                }
                edge[r].insert(l);
                ans[ind] = rt - lf - (r - l);
            } else {
                ans[ind] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] << endl;
        }
    }
    return 0;
}
