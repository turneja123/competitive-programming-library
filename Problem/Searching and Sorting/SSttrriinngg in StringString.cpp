//https://atcoder.jp/contests/abc346/tasks/abc346_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<int> pos[26];

int main() {
    IOS;
    long long n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    for (int i = 0; i < s.size(); i++) {
        pos[s[i] - 'a'].push_back(i);
    }
    long long l = 1, r = 1e18, ans = 0;
    while (l <= r) {
        long long mid = (l + r) / 2;
        long long i = 0, j = 0; int can = 1;
        for (int k = 0; k < t.size(); k++) {
            int c = t[k] - 'a';
            if (pos[c].size() == 0) {
                can = 0;
                break;
            }
            long long sum = mid;
            int p = lower_bound(pos[c].begin(), pos[c].end(), j) - pos[c].begin();
            if (pos[c].size() - p >= sum) {
                j = pos[c][p + sum - 1] + 1;
                if (j == s.size()) {
                    i++;
                    j = 0;
                }
                continue;
            }
            if (j != 0) {
                sum -= pos[c].size() - p;
                i++, j = 0;
            }
            i += (long long)sum / pos[c].size();
            if (i > n) {
                break;
            }
            long long ind = (long long)sum % pos[c].size();
            if (ind == 0) {
                i--;
                j = pos[c][pos[c].size() - 1] + 1;
                if (j == s.size()) {
                    i++;
                    j = 0;
                }
            } else {
                j = pos[c][ind - 1] + 1;
            }
        }
        if (!can) {
            ans = 0;
            break;
        }
        //cout << mid << " " << i << " " << j << endl;
        if (i < n) {
            ans = mid;
            l = mid + 1;
        } else if (i == n && j == 0) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans;

    return 0;
}
