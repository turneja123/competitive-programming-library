//https://atcoder.jp/contests/abc212/tasks/abc212_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct VeniceSet {
	multiset<long long> S;
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
	long long getMin() {
		return *S.begin() + inc;
	}
	int size() {
		return S.size();
	}
};

int main() {
	IOS;
	VeniceSet st;
    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            st.add(x);
        } else if (t == 2) {
            int x;
            cin >> x;
            st.updateAll(x);
        } else {
            long long mn = st.getMin();
            cout << mn << endl;
            st.remove(mn);
        }
    }


	return 0;
}
