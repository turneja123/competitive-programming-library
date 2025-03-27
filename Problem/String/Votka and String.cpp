//https://www.spoj.com/problems/VOTAS/
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

bool chk(vector<int> &a) {
    for (int i = 0; i < a.size(); i++) {
        if (!a[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        SuffixArray sa;
        string s;
        cin >> s;
        sa.init(s);
        int n = s.size();
        vector<int> ans(n + 1, 0);
        int l = sa.isa[0], r = l;
        for (int i = n; i >= 0; i--) {
            while (l > 0 && sa.lcp[l - 1] >= i) {
                l--;
            }
            while (r < n && sa.lcp[r] >= i) {
                r++;
            }
            ans[i] = r - l + 1;
        }

        int m;
        cin >> m;
        for (int i = 0; i < m; i++) {
            int j;
            cin >> j;
            if (j == 0) {
                cout << n << " ";
            } else if (j > n) {
                cout << 0 << " ";
            } else {
                cout << ans[j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
