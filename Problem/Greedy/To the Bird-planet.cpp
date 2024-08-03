//https://www.spoj.com/problems/TTBRM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

const int N = 1e5 + 5;

int a[N], r[N];

int main(){
	IOS;
	int t;
	cin >> t;
	while (t--) {
        int n, c, d;
        cin >> n >> c >> d;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        stack<int> s;
        for (int i = 0; i < n; i++) {
            while (s.size() && a[s.top()] < a[i]) {
                r[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
        while (s.size()) {
            r[s.top()] = n;
            s.pop();
        }
        long long cur = 0, sum = (long long)n * d, ans = 0;
        for (int i = 0; i < n; i++) {
            if (r[i] == n) {
                long long add = min(sum, (long long)c - cur);
                if (add > 0) {
                    ans += (long long)add * a[i];
                    cur += add, sum -= add;
                }
            } else {
                long long k = min({(long long)d * (r[i] - i), (long long)c, sum + cur});
                if (k > cur) {
                    ans += (long long)a[i] * (k - cur);
                    sum -= k - cur, cur = k;
                }
            }
            cur -= d;
        }
        cout << ans << endl;
	}
	return 0;
}
