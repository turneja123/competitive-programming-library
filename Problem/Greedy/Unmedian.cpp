//https://www.codechef.com/problems/MEDIANT
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<int> a;
vector<pair<int, int>> ans;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        while (1) {
            int mx = -1, pos = -1;
            for (int i = 0; i < a.size(); i++) {
                if (a[i] >= mx) {
                    mx = a[i];
                    pos = i;
                }
            }
            if (pos >= a.size() - 2) {
                break;
            }
            if (a[pos + 1] >= a[pos + 2]) {
                a.erase(a.begin() + pos + 1);
            } else {
                a.erase(a.begin() + pos + 2);
            }
            ans.push_back(make_pair(pos, pos + 2));

        }
        while (a.size() > 2) {
            int mx = -1, pos = -1;
            for (int i = 0; i < a.size(); i++) {
                if (a[i] >= mx) {
                    mx = a[i];
                    pos = i;
                }
            }
            if (pos == a.size() - 1) {
                a.erase(a.begin() + pos - 1);
                ans.push_back(make_pair(pos - 2, pos));
                continue;
            }
            if (a[pos - 1] >= a[pos + 1]) {
                a.erase(a.begin() + pos - 1);
            } else {
                a.erase(a.begin() + pos + 1);
            }
            ans.push_back(make_pair(pos - 1, pos + 1));
        }
        if (a[0] <= a[1]) {
            cout << ans.size() << endl;
            for (int i = 0; i < ans.size(); i++) {
                cout << ans[i].first + 1 << " " << ans[i].second + 1 << endl;
            }
        } else {
            cout << -1 << endl;
        }
        ans.clear();
        a.clear();
    }
    return 0;
}
