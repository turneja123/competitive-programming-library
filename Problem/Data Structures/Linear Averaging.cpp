//https://qoj.ac/contest/2668/problem/15455
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

const int N = 1e6 + 5;
const int MAX = 2e7;
const ld INF = 1e18;

ll a[N];
ld ans[N];
vector<ll> add[N], rem[N];
ll mn[N], mx[N];


struct Line {
    ld k, b;
    ld f(ld x) {
        return k * x + b;
    }
    Line(ld k, ld b) : k(k), b(b) {}
};

struct Node {
    Line line;
    int left;
    int right;
    Node(Line line) : line(line), left(-1), right(-1) {}
    Node() : line(0, INF), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

void addl(int l, int r, int lq, int rq, int node, Line cur) {
    if (l > r || l > rq || r < lq) {
        return;
    }
    int mid = (l + r) / 2;
    if (l >= lq && r <= rq) {
        bool lf = cur.f(l) < nodes[node].line.f(l);
        bool md = cur.f(mid) < nodes[node].line.f(mid);
        if (md) {
            swap(nodes[node].line, cur);
        }
        if (l == r) {
            return;
        }
        if (lf != md) {
            if (nodes[node].left == -1) {
                nodes[node].left = idx;
                nodes[idx++] = Node(cur);
            } else {
                addl(l, mid, lq, rq, nodes[node].left, cur);
            }
        } else {
            if (nodes[node].right == -1) {
                nodes[node].right = idx;
                nodes[idx++] = Node(cur);
            } else {
                addl(mid + 1, r, lq, rq, nodes[node].right, cur);
            }
        }
        return;
    }
    if (l == r) {
        return;
    }
    if (max(l, lq) <= min(mid, rq)) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        addl(l, mid, lq, rq, nodes[node].left, cur);
    }
    if (max(mid + 1, lq) <= min(r, rq)) {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        addl(mid + 1, r, lq, rq, nodes[node].right, cur);
    }

    return;
}

ld query(int l, int r, int lq, int rq, int node, int x) {
    if (l > r || l > rq || r < lq) {
        return INF;
    }
    int mid = (l + r) / 2;
    if (l >= lq && r <= rq) {
        ld ans = nodes[node].line.f(x);
        if (l == r) {
            return ans;
        }
        if (x <= mid && nodes[node].left != -1) {
            ans = min(ans, query(l, mid, lq, rq, nodes[node].left, x));
        }
        if (x > mid && nodes[node].right != -1) {
            ans = min(ans, query(mid + 1, r, lq, rq, nodes[node].right, x));
        }
        return ans;
    }
    ld ans = INF;
    if (max(l, lq) <= min(mid, rq)) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        ans = min(ans, query(l, mid, lq, rq, nodes[node].left, x));
    }
    if (max(mid + 1, lq) <= min(r, rq)) {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        ans = min(ans, query(mid + 1, r, lq, rq, nodes[node].right, x));
    }
    return ans;
}

const ld eps = 1e-15;

int main() {
	IOS;
	nodes[idx++] = Node();
	cout << fixed;
	cout << setprecision(12);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) {
        ans[i] = INF;
	}
	for (int i = 0; i < n; i++) {
        cin >> a[i];
	}
	ll s = 0;
	for (int i = 0; i < k; i++) {
        s += a[i];
	}
	add[0].push_back(s);
	rem[k].push_back(s);
	for (int i = k; i < n; i++) {
        s -= a[i - k];
        s += a[i];
        add[i - k + 1].push_back(s);
        rem[i + 1].push_back(s);
	}
	multiset<ll> st;
	for (int i = 0; i < n; i++) {
        for (ll x : add[i]) {
            st.insert(x);
        }
        for (ll x : rem[i]) {
            st.erase(st.find(x));
        }
        mn[i] = *st.begin();
        mx[i] = *st.rbegin();
	}
	for (int i = 0; i < n; i++) {
        ll l = (mn[i] + k - 1) / k;
        ld l_ld = (ld)(mn[i]) / (ld)k;
        if (l < a[i]) {
            addl(0, m, l, a[i], 0, Line((ld)1.0 / (ld)(l_ld - a[i]), (ld)-a[i] / (ld)(l_ld - a[i])));
        } else if (l == a[i]) {
            ans[a[i]] = 1.0;
        }
        ll r = mx[i] / k;
        ld r_ld = (ld)(mx[i]) / (ld)k;
        if (a[i] < r) {
            addl(0, m, a[i], r, 0, Line((ld)1.0 / (ld)(r_ld - a[i]), (ld)-a[i] / (ld)(r_ld - a[i])));
        } else if (a[i] == r) {
            ans[a[i]] = 1.0;
        }
	}
	for (int i = 0; i < n; i++) {
        ans[a[i]] = 0.0;
	}
	for (int i = 1; i <= m; i++) {
        ld cur = query(0, m, 0, m, 0, i);
        ans[i] = min(ans[i], cur);
        if (ans[i] >= 1e15) {
            cout << -1 << endl;
        } else {
            cout << ans[i] + eps << endl;
        }
	}


	return 0;
}
