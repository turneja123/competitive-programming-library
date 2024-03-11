//solution for https://dmoj.ca/problem/year2016p8
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

ll a[N];
ll segtree[4 * N];
ll setVal[4 * N];
bool setValid[4 * N];

set<pair<int, int>> st;
set<pair<int, int>> heap;
vector<pair<int, int>> purge;

void compose(int parent, int child) {
    if (setValid[parent]) {
        setValid[child] = 1;
        setVal[child] = setVal[parent];
    }
}

void apply(int node, int l, int r) {
    if (setValid[node]) {
        segtree[node] = (r - l + 1) * setVal[node];
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    setValid[node] = false;
}

void setUpdate(int node, int l, int r, int lq, int rq, ll val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        setValid[node] = true;
        setVal[node] = val;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
}

ll getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
}


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        a[i] = -1;
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r;
            cin >> l >> r;
            l--, r--;

            int groupl = getSum(0, n - 1, l, l, 0);
            int groupr = getSum(0, n - 1, r, r, 0);
            auto it = st.lower_bound({l, -1});
            for (it; it != st.end(); ++it) {
                if (it->first > r) {
                    break;
                }
                purge.push_back({it->first, it->second});
            }

            if (groupl != -1) {
                auto findl = st.lower_bound({l, N});
                findl--;
                int lstart = findl->first;
                int lsize = findl->second;
                int newsize = l - lstart;
                if (newsize != 0) {
                    st.insert({lstart, newsize});
                    heap.insert({newsize, -lstart});
                }
                if (groupl != groupr) {
                    st.erase({lstart, lsize});
                    heap.erase({lsize, -lstart});
                }
            }

            if (groupr != -1) {
                auto findr = st.lower_bound({r, N});
                findr--;
                int rstart = findr->first;
                int rsize = findr->second;
                int newsize = rstart + rsize - 1 - r;
                if (newsize != 0) {
                    st.insert({r + 1, newsize});
                    heap.insert({newsize, -(r + 1)});
                    setUpdate(0, 0, n - 1, r + 1, r + 1 + newsize - 1, r + 1);
                }
                st.erase({rstart, rsize});
                heap.erase({rsize, -rstart});
            }

            for (int i = 0; i < purge.size(); i++) {
                st.erase({purge[i].first, purge[i].second});
                heap.erase({purge[i].second, -purge[i].first});
            }

            purge.clear();
            setUpdate(0, 0, n - 1, l, r, -1);

            if (heap.empty()) {
                cout << 0 << endl;
            } else {
                cout << heap.rbegin()->first << endl;
            }
        }

        if (t == 1) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            int groupl = getSum(0, n - 1, l, l, 0);
            int groupr = getSum(0, n - 1, r, r, 0);

            if (groupl != -1 && groupl == groupr) {
                cout << heap.rbegin()->first << endl;
                continue;
            }

            int behindl = -1;
            if (l != 0) {
                behindl = getSum(0, n - 1, l - 1, l - 1, 0);
            }
            if (behindl == -1) {
                behindl = l;
            }

            int behindr = -1;
            if (r != n - 1) {
                behindr = getSum(0, n - 1, r + 1, r + 1, 0);
                if (behindr != -1) {
                    auto it = st.lower_bound({behindr, -1});
                    behindr = it->first + it->second - 1;
                }
            }
            if (behindr < r) {
                behindr = r;
            }

            auto it = st.lower_bound({behindl, -1});
            for (it; it != st.end(); ++it) {
                if (it->first > behindr) {
                    break;
                }
                purge.push_back({it->first, it->second});
            }

            for (int i = 0; i < purge.size(); i++) {
                st.erase({purge[i].first, purge[i].second});
                heap.erase({purge[i].second, -purge[i].first});
            }
            purge.clear();
            st.insert({behindl, behindr - behindl + 1});
            heap.insert({behindr - behindl + 1, -behindl});
            setUpdate(0, 0, n - 1, behindl, behindr, behindl);

            if (heap.empty()) {
                cout << 0 << endl;
            } else {
                cout << heap.rbegin()->first << endl;
            }
        }

        if (t == 2) {
            if (heap.empty()) {
                continue;
            }
            int l = -heap.rbegin()->second;
            int lsize = heap.rbegin()->first;
            heap.erase({lsize, -l});
            st.erase({l, lsize});
            setUpdate(0, 0, n - 1, l, l + lsize - 1, -1);
        }
    }

    return 0;
}
