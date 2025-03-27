//https://judge.yosupo.jp/problem/longest_common_substring
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

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
    SuffixArray sa;
    string a, b;
    cin >> a >> b;
    a += '~';
    b += '~' + 1;
    string s = a + b;
    int n = a.size(), m = b.size(), N = n + m;
    sa.init(s);
    int cta = 0, ctb = 0, ans = 0;
    pair<int, int> ival = {0, 0};
    pair<pair<int, int>, pair<int, int>> out = {{0, 0}, {0, 0}};
    multiset<int> st;
    for (int i = 1, l = 0; i <= N; i++) {
        while (l < N && !(cta && ctb)) {
            if (sa.sa[l + 1] < n) {
                cta++;
            } else {
                ctb++;
            }
            st.insert(sa.lcp[l]);
            l++;
        }
        if (!(cta && ctb)) {
            break;
        }
        st.erase(st.find(sa.lcp[i - 1]));
        if (*st.begin() > ans) {
            ans = *st.begin();
            ival = make_pair(i, l);
        }
        if (sa.sa[i] < n) {
            cta--;
        } else {
            ctb--;
        }
    }
    if (ans) {
        for (int i = ival.first; i <= ival.second; i++) {
            if (sa.sa[i] < n) {
                out.first = make_pair(sa.sa[i], sa.sa[i] + ans);
            } else {
                out.second = make_pair(sa.sa[i] - n, sa.sa[i] - n + ans);
            }
        }
    }
    cout << out.first.first << " " << out.first.second << " " << out.second.first << " " << out.second.second;
    return 0;
}
