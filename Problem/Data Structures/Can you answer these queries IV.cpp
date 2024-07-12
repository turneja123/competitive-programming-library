//https://www.spoj.com/problems/GSS4/
#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N];
long long segtree[4 * N];
long long mx[4 * N];

long long query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        return 0;
    }
    if (mx[node] == 1) {
        return min(rq, r) - max(lq, l) + 1;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1) + query(mid + 1, r, lq, rq, 2 * node + 2);
}

void traverse(int l, int r, int node) {
    if (mx[node] == 1) {
        return;
    }
    if (l == r) {
        segtree[node] = sqrt(segtree[node]);
        mx[node] = segtree[node];
        return;
    }
    int mid = (l + r) / 2;
    traverse(l, mid, 2 * node + 1);
    traverse(mid + 1, r, 2 * node + 2);
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
    mx[node] = max(mx[2 * node + 1], mx[2 * node + 2]);
}

void update(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq || mx[node] == 1) {
        return;
    }

    int mid = (l + r) / 2;
    if (lq <= l && rq >= r) {
        if (l == r) {
            segtree[node] = sqrt(segtree[node]);
            mx[node] = segtree[node];
            return;
        }
        traverse(l, mid, 2 * node + 1);
        traverse(mid + 1, r, 2 * node + 2);
    } else {
        update(l, mid, lq, rq, 2 * node + 1);
        update(mid + 1, r, lq, rq, 2 * node + 2);
    }

    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
    mx[node] = max(mx[2 * node + 1], mx[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = a[l];
        mx[node] = a[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
    mx[node] = max(mx[2 * node + 1], mx[2 * node + 2]);
}

int main() {
	//IOS;
    int c = 1;
    int n;
    while(scanf("%d", &n)!=EOF) {
        printf("Case #"); printf("%d", c++); printf(":\n");
        int q;
        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        build(0, n - 1, 0);
        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            int t, l, r;
            scanf("%d%d%d", &t, &l, &r);
            if (l > r) {
                swap(l, r);
            }
            if (t == 0) {
                l--, r--;
                update(0, n - 1, l, r, 0);

            } else {
                l--, r--;
                printf("%lld\n", query(0, n - 1, l, r, 0));
            }
        }
        printf("\n");
    }

	return 0;
}
