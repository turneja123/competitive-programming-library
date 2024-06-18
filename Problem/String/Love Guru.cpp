//https://www.spoj.com/problems/LOVEGURU/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const long long P = 26;
const long long Q = 53;
const unsigned long long M = 1e9 + 7;

struct chash {
    long long operator()(pair<long long, long long> x) const { return x.first* M + x.second; }
};
gp_hash_table<pair<long long, long long>, bool, chash> mp;

int main() {
	IOS;
	int t, k;
	cin >> t >> k;
	while (t--) {
        string a, b;
        cin >> a >> b;
        if (a.size() < k || b.size() < k) {
            cout << "No" << endl;
            continue;
        }
        long long p_pow = 1;
        long long q_pow = 1;
        long long p = 0, q = 0;
        for (int j = k - 1; j >= 0; j--) {
            long long c = (a[j] - 'a') + 1;
            p = (p + c * p_pow) % M;
            q = (q + c * q_pow) % M;

            if (j != 0) {
                p_pow = (p_pow * P) % M;
                q_pow = (q_pow * Q) % M;
            }
        }
        mp[make_pair(p, q)] = true;
        for (int j = k; j < a.size(); j++) {
            long long c = (a[j] - 'a') + 1, c_prev = (a[j - k] - 'a') + 1;
            p = (((p - c_prev * p_pow % M + M) % M) * P + c) % M;
            q = (((q - c_prev * q_pow % M + M) % M) * Q + c) % M;
            mp[make_pair(p, q)] = true;
        }
        p_pow = 1, q_pow = 1, p = 0, q = 0;
        string ans = "No";
        for (int j = k - 1; j >= 0; j--) {
            long long c = (b[j] - 'a') + 1;
            p = (p + c * p_pow) % M;
            q = (q + c * q_pow) % M;

            if (j != 0) {
                p_pow = (p_pow * P) % M;
                q_pow = (q_pow * Q) % M;
            }
        }
        if (mp.find(make_pair(p, q)) != mp.end()) {
            ans = "Yes";
        }
        for (int j = k; j < b.size(); j++) {
            long long c = (b[j] - 'a') + 1, c_prev = (b[j - k] - 'a') + 1;
            p = (((p - c_prev * p_pow % M + M) % M) * P + c) % M;
            q = (((q - c_prev * q_pow % M + M) % M) * Q + c) % M;
            if (mp.find(make_pair(p, q)) != mp.end()) {
                ans = "Yes";
            }
        }
        cout << ans << endl;
        mp.clear();

	}
	return 0;
}
