//https://basecamp.eolymp.com/en/compete/ef86c6tdpp7urd2s606psc6o6k/problem/3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int b[N];

int main() {
    IOS;
    int n;
    cin >> n;
    map<int, int> mpa, mpb;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mpa[a[i] - i] = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        mpb[b[i] - i] = i;
    }
    int ans = 0;
    for (auto [x, j] : mpa) {
        auto it = mpb.find(x);
        if (it != mpb.end()) {
            ans = max(ans, min(j, it->second) + 1);
        }
    }
    mpa.clear();
    mpb.clear();
    for (int i = n - 1; i >= 1; i--) {
        mpa[a[i] - (i - 1)]++;
        mpb[b[i] - (i - 1)]++;
    }
    for (int i = 1; i < n; i++) {
        mpa[a[i] - (i - 1)]--;
        mpb[b[i] - (i - 1)]--;
        auto ita = mpb.find((a[i - 1] - (i - 1)));
        if (ita != mpb.end() && ita->second > 0) {
            ans = max(ans, i);
        }
        auto itb = mpa.find((b[i - 1] - (i - 1)));
        if (itb != mpa.end() && itb->second > 0) {
            ans = max(ans, i);
        }
    }
    cout << ans;
    return 0;
}
