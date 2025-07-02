//https://ocpc2025s.eolymp.space/en/compete/m9rs3cu3vp6lv7kjgk9aaqsa1s/problem/3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const long long M = 1e9 + 7;
const long long P = 26, Q = 53;

long long modInverse(long long a) {
    long long res = 1;
    long long y = M - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

int A[N], B[N];
int a[N], b[N];
long long pw_q[N], pw_p[N];

vector<int> events[N];

int main() {
    IOS;
    long long invq = modInverse(Q), invp = modInverse(P);
    pw_p[0] = 1, pw_q[0] = 1;
    for (int i = 1; i < N; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
    }
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (st.size() && A[st.top()] < A[i]) {
            st.pop();
        }
        if (st.size()) {
            a[i] = st.top();
            a[i] = a[i] - i - 1;
            if (a[i] >= m) {
                a[i] = N;
            }
        } else {
            a[i] = N;
        }

        st.push(i);
    }
    while (st.size()) {
        st.pop();
    }
    for (int i = m - 1; i >= 0; i--) {
        while (st.size() && B[st.top()] < B[i]) {
            st.pop();
        }
        if (st.size()) {
            b[i] = st.top();
            b[i] = b[i] - i - 1;
        } else {
            b[i] = N;
        }
        st.push(i);
    }

    for (int i = 0; i < n; i++) {
        if (a[i] != N) {
            events[i + a[i]].push_back(i);
        }
    }
    long long pb = 0, qb = 0;
    for (int i = 0; i < m; i++) {
        if (b[i] == m - 1 - i) {
            b[i] = N;
        }
        pb = (pb + pw_p[i] * (b[i] + 1)) % M;
        qb = (qb + pw_q[i] * (b[i] + 1)) % M;
    }
    vector<int> ans;
    long long pa = 0, qa = 0;
    for (int i = n - m, k = 0; i < n; i++, k++) {
        if (a[i] == n - 1 - i) {
            a[i] = N;
        }
        pa = (pa + pw_p[k] * (a[i] + 1)) % M;
        qa = (qa + pw_q[k] * (a[i] + 1)) % M;
    }
    if (pa == pb && qa == qb) {
        ans.push_back(n - m);
    }
    for (int i = n - m - 1; i >= 0; i--) {
        pa = (pa - pw_p[m - 1] * (a[i + m] + 1) % M + M) % M * P % M;
        qa = (qa - pw_q[m - 1] * (a[i + m] + 1) % M + M) % M * Q % M;
        for (int j : events[i + m - 1]) {
            if (j > i && j <= i + m - 1) {
                pa = (pa - pw_p[j - i] * (a[j] + 1) % M + M) % M;
                qa = (qa - pw_q[j - i] * (a[j] + 1) % M + M) % M;
                a[j] = N;
                pa = (pa + pw_p[j - i] * (a[j] + 1) % M + M) % M;
                qa = (qa + pw_q[j - i] * (a[j] + 1) % M + M) % M;
            } else {
                a[j] = N;
            }
        }
        pa = (pa + a[i] + 1) % M;
        qa = (qa + a[i] + 1) % M;
        if (pa == pb && qa == qb) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] + 1 << " ";
    }
    return 0;
}
