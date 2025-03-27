//https://cses.fi/problemset/task/2108
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
    string s;
    cin >> s;
    sa.init(s);
    int n = s.size();
    vector<int> ct(n, 0);
    vector<long long> pref(n, 0);
    for (int i = 1; i <= n; i++) {
        ct[i - 1] = n - sa.sa[i] - sa.lcp[i - 1];
    }
    for (int i = 0; i < n; i++) {
        pref[i] = (i == 0 ? ct[i] : pref[i - 1] + ct[i]);
    }
    long long k;
    cin >> k;
    int j = lower_bound(pref.begin(), pref.end(), k) - pref.begin();
    if (j != 0) {
        k -= pref[j - 1];
    }
    string ans = s.substr(sa.sa[j + 1], sa.lcp[j] + k);
    cout << ans;

    return 0;
}
