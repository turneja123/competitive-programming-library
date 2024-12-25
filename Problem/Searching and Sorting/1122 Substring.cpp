//https://atcoder.jp/contests/abc381/tasks/abc381_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int pref[N];
int freq[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    freq[a[0]]++;
    int ans = 0;
    for (int i = 1, l = 0; i < n; i++) {
        freq[a[i]]++;
        while (freq[a[i]] > 2) {
            freq[a[l]]--;
            l++;
        }
        if (a[i] != a[i - 1]) {
            pref[i]++;
        }
        pref[i] += pref[i - 1];
        if (a[i] == a[i - 1]) {
            int lf = l, rt = i, cur = i + 1;
            if ((rt - lf + 1) % 2 == 1) {
                lf++;
            }
            while (lf <= rt) {
                int mid = (lf + rt) / 2;
                int ind = mid;
                if ((i - mid + 1) % 2 == 1) {
                    ind++;
                }
                int ct = pref[i] - pref[ind] + 1;
                if (ct == (i - mid + 1) / 2) {
                    cur = ind;
                    rt = mid - 1;
                } else {
                    lf = mid + 1;
                }
            }
            ans = max(ans, i - cur + 1);
        }

    }
    cout << ans;
    return 0;
}
