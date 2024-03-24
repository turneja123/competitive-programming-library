//https://www.spoj.com/problems/LUDIC1/
#pragma GCC optimize("Ofast,fast-math")
#pragma GCC optimization("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e9;
const int M = 2200000;
const int L = 5e7;
const int lim = 800;
const int SM = 10;

vector<pair<int, int>> query;
vector<int> ans;

void print() {
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << endl;
    }
    return;
}

pair<int, int> ludic[L];
pair<int, int> small_ludic[SM];

int segtree[4 * M];
int lazy[4 * M];
int segtree_light[4 * lim];
int lazy_light[4 * lim];
int idx = -1;
int j = 0;

int global_light = 0;
int global_heavy = 0;

vector<int> small_ans = {1, 2, 3, 3, 4, 4, 5, 5, 5, 5, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 16};

void apply(int node, int l, int r) {
	if (!lazy[node]) {
        return;
    }
    segtree[node] += lazy[node];
    if (l != r) {
        lazy[2 * node + 1] += lazy[node];
        lazy[2 * node + 2] += lazy[node];
    }
    lazy[node] = 0;
}

void incUpdate(int node, int l, int r, int rq) {
    if (rq > M) {
        return;
    }
    if (l > rq || 0 > r) {
        return;
    }
    if (r <= rq) {
        lazy[node] += -1;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    int ln = node * 2 + 1, rn = node * 2 + 2;
    incUpdate(ln, l, mid, rq);
    if (mid + 1 <= rq) {
        incUpdate(rn, mid + 1, r, rq);
    }
   // apply(2 * node + 1, l, mid);
   // apply(2 * node + 2, mid + 1, r);
    segtree[node] = min(segtree[ln] + lazy[ln], segtree[rn] + lazy[rn]);
}

void update(int l, int r, int val, int node) {
    if (l == r) {
        segtree[node] += val;
        lazy[node] = 0;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    int ln = node * 2 + 1, rn = node * 2 + 2;
    if (idx <= mid) {
        update(l, mid, val, ln);
    } else {
        update(mid + 1, r, val, rn);
    }
    segtree[node] = min(segtree[ln] + lazy[ln], segtree[rn] + lazy[rn]);
}

void seg_query(int l, int r, int node) {
    apply(node, l, r);
    if (segtree[node] + global_heavy != 0) {
        idx = -1;
        return;
    }
    if (l == r) {
        idx = l;
        segtree[node] += ludic[idx + lim + 1].second;
        lazy[node] = 0;
        return;
    }
    int mid = (l + r) / 2, ln = (node << 1) + 1, rn = (node << 1) + 2;
    if (segtree[ln] + lazy[ln] + global_heavy == 0) {
        seg_query(l, mid, ln);
    } else {
        lazy[ln] += -1;
        seg_query(mid + 1, r, rn);
    }
    segtree[node] = min(segtree[ln] + lazy[ln], segtree[rn] + lazy[rn]);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = N;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = min(segtree[node * 2 + 1], segtree[node * 2 + 2]);
}

//-----------------------------------------------

void apply_light(int node, int l, int r) {
	if (!lazy_light[node]) {
        return;
    }
    segtree_light[node] += lazy_light[node];
    if (l != r) {
        lazy_light[2 * node + 1] += lazy_light[node];
        lazy_light[2 * node + 2] += lazy_light[node];
    }
    lazy_light[node] = 0;
}

void incUpdate_light(int node, int l, int r, int rq) {
    if (rq > lim) {
        return;
    }
    if (l > rq || 0 > r) {
        return;
    }
    if (r <= rq) {
        lazy_light[node] += -1;
        return;
    }
    apply_light(node, l, r);
    int mid = (l + r) / 2;
    int ln = node * 2 + 1, rn = node * 2 + 2;
    incUpdate_light(ln, l, mid, rq);
    if (mid + 1 <= rq) {
        incUpdate_light(rn, mid + 1, r, rq);
    }
    //apply_light(2 * node + 1, l, mid);
    //apply_light(2 * node + 2, mid + 1, r);
    segtree_light[node] = min(segtree_light[ln] + lazy_light[ln], segtree_light[rn] + lazy_light[rn]);
}

void update_light(int l, int r, int val, int node) {
    if (l == r) {
        segtree_light[node] += val;
        lazy_light[node] = 0;
        return;
    }
    apply_light(node, l, r);
    int mid = (l + r) / 2;
    int ln = node * 2 + 1, rn = node * 2 + 2;
    if (idx <= mid) {
        update_light(l, mid, val, ln);
    } else {
        update_light(mid + 1, r, val, rn);
    }
    segtree_light[node] = min(segtree_light[ln] + lazy_light[ln], segtree_light[rn] + lazy_light[rn]);
}

void seg_query_light(int l, int r, int node) {
    apply_light(node, l, r);
    if (segtree_light[node] + global_light != 0) {
        idx = -1;
        return;
    }
    if (l == r) {
        idx = l;
        segtree_light[node] += ludic[idx].second;
        lazy_light[node] = 0;
        return;
    }
    int mid = (l + r) / 2, ln = (node << 1) + 1, rn = (node << 1) + 2;
    if (segtree_light[ln] + lazy_light[ln] + global_light == 0) {
        seg_query_light(l, mid, ln);
    } else {
        lazy_light[ln] += -1;
        seg_query_light(mid + 1, r, rn);
    }
    segtree_light[node] = min(segtree_light[ln] + lazy_light[ln], segtree_light[rn] + lazy_light[rn]);
}

void build_light(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree_light[node] = N;
        return;
    }
    int mid = (l + r) / 2;
    build_light(l, mid, node * 2 + 1);
    build_light(mid + 1, r, node * 2 + 2);
    segtree_light[node] = min(segtree_light[node * 2 + 1], segtree_light[node * 2 + 2]);
}

void mark_query(int i, int ct) {
    if (j >= query.size()) {
        return;
    }
    if (query[j].first == i) {
        ans[query[j].second] = ct + 15;
        j++;
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        query.push_back(make_pair(n, i));
    }
    sort(query.begin(), query.end());
    ans.resize(t);
    for (int i = 0; i < small_ans.size(); i++) {
        if (j < t && query[j].first == i + 1) {
            ans[query[j].second] = small_ans[i];
            j++;
        }
    }
    if (j == t) {
        print();
        return 0;
    }
    build(0, M, 0);
    build_light(0, lim, 0);
    int ct = 0;
    ludic[ct].first = 47;
    ludic[ct].second = 46;
    idx = 0;
    update_light(0, lim, 46 - N, 0);
    int mx = 0;
    small_ludic[0] = make_pair(3, 7), small_ludic[1] = make_pair(2, 11), small_ludic[2] = make_pair(5, 13), small_ludic[3] = make_pair(10, 17), small_ludic[4] = make_pair(17, 23);
    small_ludic[5] = make_pair(20, 25), small_ludic[6] = make_pair(25, 29), small_ludic[7] = make_pair(34, 37), small_ludic[8] = make_pair(39, 41), small_ludic[9] = make_pair(42, 43);

    for (int i = 48; i <= N; i++) {
        if (i % 2 == 0 || i % 6 == 3) {
            mark_query(i, ct);
            continue;
        }
        if (i % 30 == 5 || i % 30 == 19) {
            mark_query(i, ct);
            continue;
        }
        bool flag = true;
        for (int k = 0; k < SM && flag; k++) {
            small_ludic[k].first--;
            if (small_ludic[k].first == 0) {
                small_ludic[k].first = small_ludic[k].second;
                flag = false;
            }
        }
        if (!flag) {
            mark_query(i, ct);
            continue;
        }
        seg_query_light(0, lim, 0);
        if (idx != -1) {
            mark_query(i, ct);
            continue;
        }
        if (ct <= lim){
            incUpdate_light(0, 0, lim, ct);
            ct++;
            ludic[ct].first = i;
            ludic[ct].second = i - 1;
            if (ct == lim + 1) {
                idx = ct - lim - 1;
                update(0, M, i - 1 - N, 0);
            } else {
                idx = ct;
                update_light(0, lim, i - 1 - N, 0);
            }
            mark_query(i, ct);
            continue;
        }
        seg_query(0, M, 0);
        if (idx == -1) {
            if (ct - lim - 1 <= M) {
                incUpdate(0, 0, M, ct - lim - 1);
            } else {
                global_heavy -= 1;
            }
            ct++;
            ludic[ct].first = i;
            ludic[ct].second = i - 1;
            if (ct - lim - 1 <= M) {
                idx = ct - lim - 1;
                update(0, M, i - 1 - N, 0);
            }
        }
        mark_query(i, ct);
        global_light -= 1;
    }
    print();
    return 0;
}
