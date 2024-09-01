//https://www.codechef.com/problems/KBFLIP
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int pref[N];

struct VeniceSet {
	multiset<int> S;
	int inc = 0;
	void add(int v) {
		S.insert(v - inc);
	}
	void remove(int v) {
		S.erase(S.find(v - inc));
	}
	void updateAll(int v) {
		inc += v;
	}
	int getMin() {
		return *S.begin() + inc;
	}
	int size() {
		return S.size();
	}
};


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        int x = 0, y = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                x++;
            } else {
                y++;
            }
        }
        if (x > y) {
            for (int i = 0; i < n; i++) {
                if (s[i] == '0') {
                    s[i] = '1';
                } else {
                    s[i] = '0';
                }
            }
            swap(x, y);
        }
        VeniceSet st;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                pref[i]--;
            } else {
                pref[i]++;
            }
            if (i != 0) {
                pref[i] += pref[i - 1];
            }
            if (i < k) {
                st.add(pref[i]);
            }
        }
        int targ = n / 2 + n % 2 - x, l = k, ans = x;
        for (int i = 0; i < n; i++) {
            auto it = st.S.lower_bound(targ - st.inc);
            if (it != st.S.end()) {
                ans = max(ans, n - (x + *it + st.inc));
            }
            if (it != st.S.begin()) {
                it--;
                ans = max(ans, x + *it + st.inc);
            }
            st.remove(pref[i] + st.inc);
            if (s[i] == '0') {
                st.updateAll(1);
            } else {
                st.updateAll(-1);
            }
            if (l < n) {
                st.add(pref[l] + st.inc);
                l++;
            }
            pref[i] = 0;

        }
        cout << ans << endl;

    }

    return 0;
}
