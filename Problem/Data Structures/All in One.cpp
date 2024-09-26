//https://www.spoj.com/problems/ALLIN1/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e6 + 5;

int read() {
    int x = 0, f = 1;
    char ch = getchar_unlocked();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar_unlocked();
    }
    return x * f;
}

void print(int x) {
    if (x < 0) {
        putchar_unlocked('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar_unlocked(x % 10 + '0');
}

int ind;
int seen[N];
int val[N];
tuple<int, int, int> queries[N];
vector<pair<int, int>> compr;

int segtree[4 * N];

void query(int l, int r, int node, int k) {
    if (l == r) {
        ind = l;
        return;
    }
    int mid = (l + r) / 2;
    if (segtree[2 * node + 1] < k) {
        query(mid + 1, r, 2 * node + 2, k - segtree[2 * node + 1]);
    } else {
        query(l, mid, 2 * node + 1, k);
    }

}

int sum(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return sum(l, mid, lq, rq, 2 * node + 1) + sum(mid + 1, r, lq, rq, 2 * node + 2);
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] = val;
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

int main(){
    //IOS;
    int j = 0;
    while (1) {
        int c, n;
        c = read();
        if (c == -1) {
            break;
        }
        n = read();
        queries[j] = make_tuple(n, -1, c);
        if (c != 4) {
            compr.push_back(make_pair(n, j));
        }
        j++;

    }
    sort(compr.begin(), compr.end());
    int m = 0;
    for (int i = 0; i < compr.size(); i++) {
        if (i > 0 && compr[i].first > compr[i - 1].first) {
            m++;
        }
        get<1>(queries[compr[i].second]) = m;
        val[m] = compr[i].first;
    }
    m++;
    for (int i = 0; i < j; i++) {
        int n = get<0>(queries[i]), c = get<2>(queries[i]), pos = get<1>(queries[i]);
        if (c == 1) {
            update(0, m - 1, pos, 1, 0);
            seen[pos]++;
        } else if (c == 2) {
            if (!seen[pos]) {
                continue;
            }
            update(0, m - 1, pos, 0, 0);
            seen[pos]--;
        } else if (c == 4) {
            if (n > segtree[0] || n == 0) {
                print(-1);
            } else {
                ind = -1;
                query(0, m - 1, 0, n);
                print(val[ind]);
            }
            putchar_unlocked('\n');
        } else {
            if (!seen[pos]) {
                print(-1);
                putchar_unlocked('\n');
                continue;
            }
            print(sum(0, m - 1, 0, pos, 0));
            putchar_unlocked('\n');
        }

    }
    return 0;
}
