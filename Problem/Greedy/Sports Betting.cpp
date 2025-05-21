//https://codeforces.com/contest/2097/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        int last = a[0], ct = 1;
        vector<pair<int, int>> blocks;
        for (int i = 1; i < n; i++) {
            if (last != a[i]) {
                blocks.push_back(make_pair(last, ct));
                last = a[i];
                ct = 0;
            }
            ct++;
        }
        blocks.push_back(make_pair(last, ct));
        string ans = "No";
        int rem = 0;
        for (int i = 0; i < blocks.size(); i++) {
            auto [x, f] = blocks[i];
            if (i > 0 && x - blocks[i - 1].first > 1) {
                rem = 0;
            }
            if (rem == 0) {
                if (f >= 4) {
                    ans = "Yes";
                    break;
                }
                if (f >= 2) {
                    rem = 1;
                } else {
                    rem = 0;
                }
            } else {
                if (f >= 2) {
                    ans = "Yes";
                    break;
                }
                if (f >= 1) {
                    rem = 1;
                } else {
                    rem = 0;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
