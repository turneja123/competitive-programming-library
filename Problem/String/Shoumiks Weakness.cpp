//https://www.spoj.com/problems/WEAKSMK/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int ans[N];
vector<pair<int, int>> queries[N];
vector<pair<int, int>> events[N];

int parent[N];
int sz[N];
int ct[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    ct[sz[a]]--;
    ct[sz[b]]--;
    sz[a] += sz[b];
    ct[sz[a]]++;
    parent[b] = a;
}

struct SuffixArray {
	string S; int n;
	vector<int> sa, isa, lcp;
	void init(string _S) {
	     S = _S;
	     n = S.size() + 1;
	     genSa(); genLcp();
    }
	void genSa() {
		sa = vector<int>(n);
		isa = vector<int>(n);
		sa[0] = n - 1;
		iota(1 + sa.begin(), sa.end(), 0);
		sort(1 + sa.begin(), sa.end(), [&](int a, int b) { return S[a] < S[b]; });
		for (int i = 1; i < n; i++) {
            int a = sa[i - 1], b = sa[i];
			isa[b] = i > 1 && S[a] == S[b] ? isa[a] : i;
        }
		for (int len = 1; len < n; len *= 2) {
			vector<int> s(sa), is(isa), pos(n);
			iota(pos.begin(), pos.end(), 0);
			for (int t : s) {
                int T = t - len;
                if (T >= 0) {
                    sa[pos[isa[T]]++] = T;
                }
            }
			for (int i = 1; i < n; i++) {
                int a = sa[i - 1], b = sa[i];
				isa[b] = is[a] == is[b] && is[a + len] == is[b + len] ? isa[a] : i;
            }
		}
	}
	void genLcp() {
		lcp = vector<int>(n - 1); int h = 0;
		for (int b = 0; b < n - 1; b++) {
            int a = sa[isa[b] - 1];
			while (a + h < n - 1 && S[a + h] == S[b + h]) {
                ++h;
			}
			lcp[isa[b] - 1] = h;
			if (h) {
                h--;
			}
        }
	}
};

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        SuffixArray sa;
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;
        sa.init(s);
        for (int i = 0; i < q; i++) {
            int m, k;
            cin >> m >> k;
            if (k > n || m > n || k == 0) {
                ans[i] = 0;
                continue;
            }
            queries[m].push_back(make_pair(k, i));
        }
        for (int i = 1; i < n; i++) {
            events[sa.lcp[i]].push_back(make_pair(sa.sa[i], sa.sa[i + 1]));
        }
        for (int i = n; i >= 1; i--) {
            parent[n - i] = n - i;
            sz[n - i] = 1;

            ct[1]++;
            for (auto [u, v] : events[i]) {
                int x = dsu_find(u), y = dsu_find(v);
                if (x != y) {
                    dsu_unite(x, y);
                }
            }
            for (auto [k, ind] : queries[i]) {
                ans[ind] = ct[k];
            }
        }
        for (int i = 0; i < q; i++) {
            cout << ans[i] << endl;
        }
        for (int i = 0; i <= n; i++) {
            events[i].clear();
            queries[i].clear();
            ct[i] = 0;
        }
    }

    return 0;
}
