//https://www.spoj.com/problems/NSUBSTR/
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
    string S;
    cin >> S;
    sa.init(S);
    int n = S.size();
    vector<int> ans(n, 1), a(n), l(n), r(n);
    for (int i = 0; i < n; i++) {
        a[i] = sa.lcp[i];
    }
    stack<int> s;
    for (int i = 0; i < n; i++) {
        while (s.size() && a[s.top()] > a[i]) {
            r[s.top()] = i - 1;
            s.pop();
        }
        s.push(i);
    }
    while (s.size()) {
        r[s.top()] = n - 1;
        s.pop();
    }
    for (int i = n - 1; i >= 0; i--) {
        while (s.size() && a[s.top()] > a[i]) {
            l[s.top()] = i + 1;
            s.pop();
        }
        s.push(i);
    }
    while (s.size()) {
        l[s.top()] = 0;
        s.pop();
    }
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            ans[a[i] - 1] = max(ans[a[i] - 1], r[i] - l[i] + 2);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }


    return 0;
}
