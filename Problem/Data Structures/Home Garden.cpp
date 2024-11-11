//https://atcoder.jp/contests/abc379/tasks/abc379_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct VeniceSet {
	multiset<long long, greater<long long>> S;
	long long inc = 0;
	void add(long long v) {
		S.insert(v - inc);
	}
	void remove(long long v) {
		S.erase(S.find(v - inc));
	}
	void updateAll(long long v) {
		inc += v;
	}
	long long getMax() {
		return *S.begin() + inc;
	}
	int size() {
		return S.size();
	}
};

int main() {
    IOS;
    VeniceSet st;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            st.add(0);
        } else if (t == 2) {
            int x;
            cin >> x;
            st.updateAll(x);
        } else {
            int x, ans = 0;
            cin >> x;
            while (st.size()) {
                long long k = st.getMax();
                if (k >= x) {
                    ans++;
                    st.remove(k);
                } else {
                    break;
                }
            }
            cout << ans << endl;
        }
    }

    return 0;
}
