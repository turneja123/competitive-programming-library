//solution for https://www.spoj.com/problems/MODSEQ/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int a[N];
int nxt[N];
bool b[N];
bool md[N];

vector<int> ans;

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    int sumd = 0;
    int ct = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[a[i]] = true;
        if (!md[a[i] % k]) {
            md[a[i] % k] = true;
            sumd += a[i] % k;
            ct++;
        }
    }
    if (ct == k && sumd % k != 0) {
        cout << -1 << endl;
        return 0;
    }

    for (int i = 0; i < k; i++) {
        nxt[i] = i;
    }
    nxt[0] = k;

    int j = 0;
    for (int i = 0; i < k; i++) {
        if (md[i]) {
            while (b[nxt[i]]) {
                nxt[i] += k;
            }
            if (a[j] % k == i) {
                ans.push_back(a[j++]);
                continue;

            }
            ans.push_back(nxt[i]);
            nxt[i] += k;
        }
    }

    sumd %= k;
    if (ct != k) {
        int m = k - sumd;
        while (b[nxt[m]]) {
            nxt[m] += k;
        }
        if (a[j] % k == m) {
            ans.push_back(a[j++]);
        } else {
            ans.push_back(nxt[m]);
            nxt[m] += k;
        }
    }

    for (int i = ans.size(); i < k; i++) {
        while (b[nxt[0]]) {
            nxt[0] += k;
        }
        ans.push_back(nxt[0]);
        nxt[0] += k;
    }
    int i = 0;
    while (j < n) {
        int m = ans[i % k] % k;
        while (b[nxt[m]]) {
            nxt[m] += k;
        }
        if (a[j] % k == m) {
            ans.push_back(a[j++]);
            i++;
            continue;
        }
        ans.push_back(nxt[m]);
        nxt[m] += k;
        i++;
    }
    cout << ans.size() << endl;
    for (int x : ans) {
        cout << x << " ";
    }

    return 0;
}
