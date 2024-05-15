//https://atcoder.jp/contests/abc353/tasks/abc353_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

string s[N];
int ind[N];

pair<long long, long long> hsh[N];
const long long M = 1e9 + 7;

struct chash {
    long long operator()(pair<long long, long long> x) const { return x.first* (long long)(1000000007) + x.second; }
};
gp_hash_table<pair<long long, long long>, int, chash> mp;

int main() {
	IOS;
	int n;
	cin >> n;
	set<int> st;
	for (int i = 0; i < n; i++) {
        cin >> s[i];
        st.insert(i);
	}
	long long ans = 0;
	long long P = 26;
    long long Q = 53;
    long long M = 1e9 + 7;

    long long p_pow = 1;
    long long q_pow = 1;
    long long p = 0, q = 0;
	while (st.size()) {
        vector<int> del;
        long long ct = 0;
        for (auto it = st.begin(); it != st.end(); ++it) {
            int i = *it, j = ind[i];
            if (j == s[i].size()) {
                del.push_back(i);
                continue;
            }
            long long c = s[i][j] - 'a' + 1;
            hsh[i].first = (hsh[i].first + p_pow * c) % M;
            hsh[i].second = (hsh[i].second + q_pow * c) % M;
            auto itt = mp.find(hsh[i]);
            if (itt != mp.end()) {
                ct += itt->second;
            }
            mp[hsh[i]]++;
            ind[i]++;
        }
        ans += ct;
        for (int x : del) {
            st.erase(x);
        }
        p_pow = (p_pow * P) % M;
        q_pow = (q_pow * Q) % M;
	}
	cout << ans;


	return 0;
}
