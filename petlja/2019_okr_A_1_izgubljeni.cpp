#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;

int a[N];
int ans[N];
int ct[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n * (n + 1) / 2; i++) {
        cin >> a[i];
        ct[a[i]]++;
    }
    sort(a, a + n * (n + 1) / 2);
    ans[0] = a[0];
    ct[a[0]]--;
    int ind = 1;
    for (int i = 1; i < n * (n + 1) / 2; i++) {
        if (ct[a[i]] > 0) {
            ans[ind] = a[i];
            for (int j = 0; j <= ind; j++) {
                ct[ans[j] | a[i]]--;
            }
            ind++;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
