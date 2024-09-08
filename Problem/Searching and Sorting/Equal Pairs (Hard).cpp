//https://www.codechef.com/problems/MAXEQUAL
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];
long long freq[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        long long ans = 0, mx = 0, ct = n;
        multiset<int> st;
        vector<int> vals;
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            vals.push_back(y);
            x--;
            if (a[x] == 0) {
                ct--;
            } else {
                st.erase(st.find(freq[a[x]]));
                freq[a[x]]--;
                ans -= freq[a[x]];
                st.insert(freq[a[x]]);
            }
            a[x] = y;
            if (a[x] == 0) {
                ct++;
            } else {
                ans += freq[a[x]];
                if (freq[a[x]] != 0) {
                    st.erase(st.find(freq[a[x]]));
                }
                freq[a[x]]++;
                st.insert(freq[a[x]]);
            }
            mx = *st.rbegin();
            long long best = ans - mx * (mx - 1) / 2;
            mx += ct;
            best += mx * (mx - 1) / 2;
            cout << best << " ";
        }
        for (int i = 0; i < n; i++) {
            freq[vals[i]] = 0;
            a[i] = 0;
        }
        cout << endl;


    }
    return 0;
}
