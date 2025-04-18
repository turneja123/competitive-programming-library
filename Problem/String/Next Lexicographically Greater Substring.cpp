//https://www.spoj.com/problems/NEXTLEX/
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

bool comp(string &s, string &a, int j, int n) {
    int m = a.size();
    int i = 0;
    for (; i < m && j < n; i++, j++) {
        if (s[j] < a[i]) {
            return false;
        }
        if (s[j] > a[i]) {
            return true;
        }
    }
    if (j == n) {
        return false;
    }
    return true;
}

int main() {
    IOS;
    SuffixArray sa;
    string S;
    cin >> S;
    sa.init(S);
    int n = S.size();
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string a;
        cin >> a;
        int l = 1, r = n, ind = n + 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            bool f = comp(S, a, sa.sa[mid], n);
            if (!f) {
                l = mid + 1;
            } else {
                r = mid - 1;
                ind = mid;
            }
        }
        if (ind == n + 1) {
            cout << -1 << endl;
            continue;
        }
        string ans = "";
        for (int j = sa.sa[ind], k = 0; j < n; k++, j++) {
            ans += S[j];
            if (k == a.size() || S[j] != a[k]) {
                break;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
