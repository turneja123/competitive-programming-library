//https://algotester.com/en/ArchiveProblem/DisplayWithFile/71136
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
            }
        }
        int need = n;
        for (int j = 1; j < m; j++) {
            multiset<int> st;
            vector<int> v;
            for (int i = 0; i < n; i++) {
                st.insert(a[i][j - 1]);
                v.push_back(a[i][j]);
            }
            sort(v.begin(), v.end(), greater<int>());
            for (int x : v) {
                auto it = st.upper_bound(x);
                if (it != st.end()) {
                    need--;
                    st.erase(it);
                }
            }
        }
        if (need <= 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
