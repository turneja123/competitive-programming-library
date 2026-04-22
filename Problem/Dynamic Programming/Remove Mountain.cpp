//https://repovive.com/contests/5/problems/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int M = 998244353;


int a[N];
int L[N], R[N];
int dp[N];

vector<int> add[N];

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
        stack<int> st;
        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && a[i] < a[st.top()]) {
                st.pop();
            }
            if (st.size()) {
                R[i] = st.top();
            } else {
                R[i] = n;
            }
            if (R[i] != n) {
                add[R[i]].push_back(i);
            }
            st.push(i);
        }
        while (st.size()) {
            st.pop();
        }
        st.push(0);
        dp[0] = 1;
        for (int i = 1; i < n; i++) {
            dp[i] = 0;
            while (st.size() && a[i] < a[st.top()]) {
                st.pop();
            }
            if (st.size()) {
                L[i] = st.top();
            } else {
                L[i] = -1;
            }
            st.push(i);

            int b = 1;
            for (int j : add[i]) {
                dp[i] = (dp[i] + dp[j]) % M;
                if (j == i - 1) {
                    b = 0;
                }
            }
            if (L[i] == i - 1) {
                b = 0;
            }
            if (L[i] != -1) {
                dp[i] = (dp[i] + dp[L[i]]) % M;
            }
            if (b) {
                dp[i] = (dp[i] + dp[i - 1]) % M;
            }
        }
        cout << dp[n - 1] << endl;
        for (int i = 0; i < n; i++) {
            add[i].clear();
        }
    }



    return 0;
}
