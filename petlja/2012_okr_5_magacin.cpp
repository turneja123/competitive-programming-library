#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];

multiset<int> st;

int main() {
    IOS;
    int n, k;
    ll sum = 0;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    sort(a, a + n);
    int j = n - 1;
    ll mid = sum / (ll)n;
    for (int i = 0; i < j;) {
        int pot = (a[j] - mid) / k;
        int need = (mid - a[i]) / k;
        int c = min(pot, need);
        a[i] += c * k;
        a[j] -= c * k;
        if ((a[j] - mid) / k == 0) {
            j--;
        }
        if ((mid - a[i]) / k == 0) {
            i++;
        }
    }
    for (int i = 0; i < n; i++) {
        st.insert(a[i]);
    }
    int ans = *st.rbegin() - *st.begin();
    int it = 0;
    while (1) {
        int mx = *st.rbegin();
        int mn = *st.begin();
        st.erase(st.find(mx));
        st.erase(st.find(mn));
        mx -= k;
        mn += k;
        st.insert(mx);
        st.insert(mn);
        int cur = *st.rbegin() - *st.begin();
        if (cur > ans || it > 2000000) {
            break;
        } else {
            ans = cur;
        }
        it++;
    }
    cout << ans << endl;
    return 0;
}
