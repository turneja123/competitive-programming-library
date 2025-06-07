//https://www.codechef.com/problems/SORTSUB7
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
        int l = 0, r = 0, cur = 0;
        queue<int> q;
        while (r < n) {
            if (a[r] >= cur) {
                if ((a[r] - 1) / 2 >= cur) {
                    cur++;
                } else {
                    cur = a[r] + 1;
                    q.push(r);
                }
            } else {
                break;
            }
            r++;
        }
        long long ans = r;
        l++;
        while (l < n) {
            while (q.size()) {
                int j = q.front();
                if (j <= l) {
                    q.pop();
                    continue;
                }
                if ((a[j] - 1) / 2 >= j - l) {
                    q.pop();
                } else {
                    break;
                }
            }
            if (q.empty()) {
                cur = r - l;
            }
            while (r < n) {
                if (a[r] >= cur) {
                    if ((a[r] - 1) / 2 >= cur) {
                        cur++;
                    } else {
                        cur = a[r] + 1;
                        q.push(r);
                    }
                } else {
                    break;
                }
                r++;
            }
            ans += r - l;
            l++;
        }
        cout << ans << endl;
    }
    return 0;
}
