//https://codeforces.com/contest/873/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

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

int parent[N];
int sz[N];
long long sum[N];
long long ans = 0;

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b, int l) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    sum[a] += sum[b];
    ans = max(ans, (long long)l * sum[a]);
    parent[b] = a;
}

int main() {
    IOS;
    SuffixArray sa;
    int n;
    cin >> n;
    string s;
    cin >> s;
    string f;
    cin >> f;
    reverse(s.begin(), s.end());
    reverse(f.begin(), f.end());
    sa.init(s);
    for (int i = 0; i < n; i++) {
        sz[i] = 1;
        parent[i] = i;
        if (f[i] == '0') {
            sum[i] = 1;
            ans = max(ans, (long long)n - i);
        } else {
            sum[i] = 0;
        }
    }
    vector<tuple<int, int, int>> events;
    for (int i = 1; i < n; i++) {
        events.push_back(make_tuple(sa.lcp[i], sa.sa[i], sa.sa[i + 1]));
    }
    sort(events.begin(), events.end());
    reverse(events.begin(), events.end());
    for (auto [l, x, y] : events) {
        x = dsu_find(x), y = dsu_find(y);
        if (x != y) {
            dsu_unite(x, y, l);
        }
    }
    cout << ans;
    return 0;
}
