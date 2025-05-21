//https://codeforces.com/contest/2026/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e4 + 5;
const int M = 2005;

int id[N];
int ans[N];

vector<tuple<int, int, int>> updates[N];
vector<pair<int, int>> queries[N];
array<int, M> T;

struct minstack {
	stack<pair<int, int>> st;
	stack<array<int, M>> dp;
	array<int, M> getmin() {return dp.top();}
	int get(int p) {return dp.top()[p];}
	bool empty() {return st.empty();}
	int size() {return st.size();}
	void push(pair<int, int> x) {
		auto [p, t] = x;
		if (!empty()) {
            T = getmin();
		} else {
            for (int i = 0; i < M; i++) {
                T[i] = 0;
            }
		}
		for (int i = M - 1 - p; i >= 0; i--) {
            T[i + p] = max(T[i + p], T[i] + t);
		}
		dp.push(T);
		st.push({p, t});
	}
	void pop() {st.pop(); dp.pop();}
	pair<int, int> top() {return st.top();}
	void swap(minstack &x) {st.swap(x.st); dp.swap(x.dp);}
};

struct mindeque {
	minstack l, r, t;
	void rebalance() {
		bool f = false;
		if (r.empty()) {f = true; l.swap(r);}
		int sz = r.size() / 2;
		while (sz--) {t.push(r.top()); r.pop();}
		while (!r.empty()) {l.push(r.top()); r.pop();}
		while (!t.empty()) {r.push(t.top()); t.pop();}
		if (f) l.swap(r);
	}
	int getmin(int p) {
	    if (l.empty() && r.empty()) {
            return 0;
	    }
		if (l.empty()) return r.get(p);
		if (r.empty()) return l.get(p);
		int best = 0;
		for (int i = 0; i <= p; i++) {
            best = max(best, l.get(i) + r.get(p - i));
		}
		return best;
	}
	bool empty() {return l.empty() && r.empty();}
	int size() {return l.size() + r.size();}
	void push_front(pair<int, int> x) {l.push(x);}
	void push_back(pair<int, int> x) {r.push(x);}
	void pop_front() {if (l.empty()) rebalance(); l.pop();}
	void pop_back() {if (r.empty()) rebalance(); r.pop();}
	pair<int, int> front() {if (l.empty()) rebalance(); return l.top();}
	pair<int, int> back() {if (r.empty()) rebalance(); return r.top();}
	void swap(mindeque &x) {l.swap(x.l); r.swap(x.r);}
};

mindeque deq;

void dfs(int u, int par) {
    for (auto [v, p, t] : updates[u]) {
        if (v != par) {
            if (p == -1) {
                dfs(v, u);
            } else if (p == -2) {
                pair<int, int> item = deq.front();
                deq.pop_front();
                dfs(v, u);
                deq.push_front(item);
            } else {
                deq.push_back(make_pair(p, t));
                dfs(v, u);
                deq.pop_back();
            }
        }
    }
    for (auto [p, j] : queries[u]) {
        ans[j] = deq.getmin(p);
    }
    return;
}

int main() {
    IOS;
    int n = 1, m = 1, qs = 0;
    int q;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            x--;
            id[n] = m;
            updates[id[x]].push_back(make_tuple(id[n], -1, -1));
            n++, m++;
        } else if (t == 2) {
            int x, p, t;
            cin >> x >> p >> t;
            x--;
            updates[id[x]].push_back(make_tuple(m, p, t));
            id[x] = m++;
        } else if (t == 3) {
            int x;
            cin >> x;
            x--;
            updates[id[x]].push_back(make_tuple(m, -2, -1));
            id[x] = m++;
        } else {
            int x, p;
            cin >> x >> p;
            x--;
            queries[id[x]].push_back(make_pair(p, qs++));
        }
    }
    dfs(0, 0);
    for (int i = 0; i < qs; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
