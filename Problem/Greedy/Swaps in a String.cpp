//https://www.codechef.com/START188A/problems/SWAPSTR
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int prefA[N], sufC[N];
int best[N];

int main() {
	IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        int last = -1;
        for (int i = 0; i < n; i++) {
            prefA[i] = (i == 0 ? 0 : prefA[i - 1]);
            if (s[i] == 'C') {
                last = i;
            } else if (s[i] == 'B') {
                best[i] = prefA[i] - (last == -1 ? 0 : prefA[last]);
            } else {
                prefA[i]++;
            }
        }
        last = n;
        long long ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            sufC[i] = (i == n - 1 ? 0 : sufC[i + 1]);
            if (s[i] == 'A') {
                last = i;
            } else if (s[i] == 'B') {
                best[i] = max(best[i], sufC[i] - (last == n ? 0 : sufC[last]));
                ans += best[i];
            } else {
                sufC[i]++;
            }
        }
        for (int i = 0; i < n; i++) {
            best[i] = 0;
            sufC[i] = 0;
            prefA[i] = 0;
        }
        cout << ans << endl;
    }
	return 0;
}
