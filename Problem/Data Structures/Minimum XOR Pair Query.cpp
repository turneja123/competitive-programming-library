//https://atcoder.jp/contests/abc308/tasks/abc308_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 3e5 + 5;

multiset<int> st;
vector<pair<int, int>> queries;
pair<int, int> compr[N];

int a[N];
int val[N];
int segtree[4 * N];

int ind = -1;

void traverse(int l, int r, int k, int node) {
    if (segtree[node] < k) {
        ind = -1;
        return;
    }

    if (l == r) {
        ind = l;
        return;
    }
    int mid = (l + r) / 2;
    if (segtree[2 * node + 1] >= k) {
        traverse(l, mid, k, 2 * node + 1);
    } else {
        traverse(mid + 1, r, k - segtree[2 * node + 1], 2 * node + 2);
    }
    return;
}

int query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq || lq > rq) {
        return 0;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1) +query(mid + 1, r, lq, rq, 2 * node + 2);
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] += val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}


int main() {
    IOS;
    int n, s = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int t, x = -1;
        cin >> t;
        if (t != 3) {
            cin >> x;
            compr[s++] = make_pair(x, i);
        }
        queries.push_back(make_pair(t, x));
    }
    sort(compr, compr + s);
    int m = 0;
    for (int i = 0; i < s; i++) {
        if (i > 0 && compr[i].first > compr[i - 1].first) {
            m++;
        }
        val[m] = compr[i].first;
        a[compr[i].second] = m;
    }
    m++;
    for (int i = 0; i < n; i++) {
        int t = queries[i].first, x = a[i];
        if (t == 1) {
            update(0, m - 1, x, 1, 0);
            int ct = query(0, m - 1, x, x, 0);
            if (ct == 2) {
                st.insert(0);
            }
            if (ct == 1) {
                int l, r;
                int tot = query(0, m - 1, 0, x - 1, 0);
                if (tot == 0) {
                    l = -1;
                } else {
                    traverse(0, m - 1, tot, 0);
                    l = ind;
                }
                traverse(0, m - 1, tot + ct + 1, 0);
                r = ind;
                if (l != -1) {
                    st.insert(val[x] ^ val[l]);
                }
                if (r != -1) {
                    st.insert(val[x] ^ val[r]);
                }
                if (l != -1 && r != -1) {
                    st.erase(st.find(val[l] ^ val[r]));
                }
            }
        } else if (t == 2) {
            update(0, m - 1, x, -1, 0);
            int ct = query(0, m - 1, x, x, 0);
            if (ct == 1) {
                st.erase(st.find(0));
            }
            if (ct == 0) {
                int l, r;
                int tot = query(0, m - 1, 0, x - 1, 0);
                if (tot == 0) {
                    l = -1;
                } else {
                    traverse(0, m - 1, tot, 0);
                    l = ind;
                }
                traverse(0, m - 1, tot + ct + 1, 0);
                r = ind;
                if (l != -1) {
                    st.erase(st.find(val[x] ^ val[l]));
                }
                if (r != -1) {
                    st.erase(st.find(val[x] ^ val[r]));
                }
                if (l != -1 && r != -1) {
                    st.insert(val[l] ^ val[r]);
                }
            }

        } else {
            cout << *st.begin() << endl;
        }
    }


    return 0;
}
