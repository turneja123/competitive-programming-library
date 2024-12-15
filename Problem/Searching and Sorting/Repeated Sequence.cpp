//https://atcoder.jp/contests/abc384/tasks/abc384_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N];

int main() {
    IOS;
    int n; long long s;
    cin >> n >> s;
    long long sum = 0;
    set<long long> st;
    st.insert(0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        auto it = st.find(sum - s);
        if (it != st.end()) {
            cout << "Yes";
            return 0;
        }
        st.insert(sum);
    }
    if (sum == s) {
        cout << "Yes";
        return 0;
    }
    long long need = s % sum;
    if (need == 0 && s >= sum) {
        cout << "Yes";
        return 0;
    }
    for (int i = 0; i < 3 * n; i++) {
        sum += a[i % n];
        st.insert(sum);
        auto it = st.find(sum - need);
        if (it != st.end()) {
            cout << "Yes";
            return 0;
        }
    }
    cout << "No";
    return 0;
}
