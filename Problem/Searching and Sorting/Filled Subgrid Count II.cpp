//https://cses.fi/problemset/task/3414
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

int a[N][N];
int sz[N][N];

vector<int> col[26][N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            a[i][j] = s[j] - 'A';
            col[a[i][j]][j].push_back(i);
        }
        int last = 0;
        for (int j = 1; j < n; j++) {
            if (a[i][j] != a[i][last]) {
                for (int l = last; l < j; l++) {
                    sz[i][l] = j - l;
                }
                last = j;
            }
        }
        for (int l = last; l < n; l++) {
            sz[i][l] = n - l;
        }
    }
    for (int c = 0; c < k; c++) {
        ll ans = 0;
        for (int j = 0; j < n; j++) {
            int last = -2; ll sum = 0;
            stack<pair<int, int>> st;
            for (int i : col[c][j]) {
                if (last != i - 1) {
                    while (st.size()) {
                        auto [d, y] = st.top();
                        sum -= d * y;
                        st.pop();
                    }
                }
                int x = 1;
                while (st.size() && st.top().first >= sz[i][j]) {
                    auto [d, y] = st.top();
                    x += y;
                    sum -= d * y;
                    st.pop();
                }
                sum += x * sz[i][j];
                st.push({sz[i][j], x});
                ans += sum;
                last = i;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
