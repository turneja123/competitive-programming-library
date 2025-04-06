//https://usaco.org/index.php?page=viewproblem2&cpid=768
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 20;

int table[K][N];
int l[N];
int r[N];
int val[N];
long long ans[N];
string s[N];

void build(int n, vector<int> &a) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = a[i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = min(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    return min(table[k][l], table[k][r - (1 << k) + 1]);
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
			while (a + h < n - 1 && S[a + h] == S[b + h] && S[a + h] != '~') {
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
    freopen("standingout.in", "r", stdin);
    freopen("standingout.out", "w", stdout);
    SuffixArray sa;
    string S = "";
    int m;
    cin >> m;
    vector<int> idx, sz;
    for (int i = 0; i < m; i++) {
        cin >> s[i];
        int n = s[i].size();
        for (int j = 0; j < n; j++) {
            idx.push_back(i);
            sz.push_back(n - j);
        }
        S += s[i];
        S += '~';
        idx.push_back(N - 1);
        sz.push_back(0);
    }
    sa.init(S);
    int n = S.size();
    build(n, sa.lcp);
    stack<int> st;
    for (int i = 1; i <= n; i++) {
        val[i] = idx[sa.sa[i]];
        while (st.size() && val[st.top()] == val[i]) {
            st.pop();
        }
        if (st.empty()) {
            l[i] = -1;
        } else {
            l[i] = st.top();
        }
        st.push(i);
    }

    while (st.size()) {
        st.pop();
    }
    for (int i = n; i > 0; i--) {
        while (st.size() && val[st.top()] == val[i]) {
            st.pop();
        }
        if (st.empty()) {
            r[i] = -1;
        } else {
            r[i] = st.top();
        }
        st.push(i);
    }

    for (int i = 1; i <= n; i++) {
        if (val[i] == N - 1) {
            continue;
        }
        int mx = 0;
        mx = max(mx, query(i - 1, i - 1));
        if (r[i] != -1) {
            mx = max(mx, query(i, r[i] - 1));
        }
        ans[val[i]] += sz[sa.sa[i]] - mx;
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
