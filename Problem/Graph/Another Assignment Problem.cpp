//https://www.spoj.com/problems/ASSIGN4/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e18;
const int N = 205;

int a[N], b[N];
int rem_a[N], rem_b[N];
int c[N][N];
int x[N][N];

ll u[N], v_[N];
ll slack[N];
int from_[N];
int parent_l[N], parent_r[N];
bool S[N], T[N];

int main() {
    IOS;
    int tt;
    cin >> tt;
    while (tt--) {
        int n, m;
        cin >> n >> m;

        for (int i = 0; i < n; i++) {
            cin >> a[i];
            rem_a[i] = a[i];
        }
        for (int j = 0; j < m; j++) {
            cin >> b[j];
            rem_b[j] = b[j];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> c[i][j];
                x[i][j] = 0;
            }
        }

        for (int i = 0; i < n; i++) {
            u[i] = c[i][0];
            for (int j = 1; j < m; j++) {
                u[i] = min(u[i], (ll)c[i][j]);
            }
        }
        for (int j = 0; j < m; j++) {
            v_[j] = 0;
        }

        for (int root = 0; root < n; root++) {
            while (rem_a[root] > 0) {
                for (int i = 0; i < n; i++) {
                    S[i] = false;
                    parent_l[i] = -1;
                }
                for (int j = 0; j < m; j++) {
                    T[j] = false;
                    parent_r[j] = -1;
                    slack[j] = INF;
                    from_[j] = -1;
                }

                queue<int> q;
                S[root] = true;
                q.push(root);

                int target = -1;

                while (target == -1) {
                    while (!q.empty()) {
                        int i = q.front();
                        q.pop();
                        for (int j = 0; j < m; j++) {
                            if (T[j]) {
                                continue;
                            }
                            ll val = (ll)c[i][j] - u[i] - v_[j];
                            if (val < slack[j]) {
                                slack[j] = val;
                                from_[j] = i;
                            }
                        }
                    }

                    ll delta = INF;
                    for (int j = 0; j < m; j++) {
                        if (!T[j]) {
                            delta = min(delta, slack[j]);
                        }
                    }

                    for (int i = 0; i < n; i++) {
                        if (S[i]) {
                            u[i] += delta;
                        }
                    }
                    for (int j = 0; j < m; j++) {
                        if (T[j]) {
                            v_[j] -= delta;
                        } else {
                            slack[j] -= delta;
                        }
                    }

                    queue<int> rq;
                    for (int j = 0; j < m; j++) {
                        if (!T[j] && slack[j] == 0) {
                            T[j] = true;
                            parent_r[j] = from_[j];
                            rq.push(j);
                        }
                    }

                    while (!rq.empty() && target == -1) {
                        int j = rq.front();
                        rq.pop();

                        if (rem_b[j] > 0) {
                            target = j;
                            break;
                        }

                        for (int i = 0; i < n; i++) {
                            if (x[i][j] > 0 && !S[i]) {
                                S[i] = true;
                                parent_l[i] = j;
                                q.push(i);
                            }
                        }
                    }
                }

                int add = min(rem_a[root], rem_b[target]);

                int cur_j = target;
                while (true) {
                    int i = parent_r[cur_j];
                    if (i == root) {
                        break;
                    }
                    int prev_j = parent_l[i];
                    add = min(add, x[i][prev_j]);
                    cur_j = prev_j;
                }

                cur_j = target;
                while (true) {
                    int i = parent_r[cur_j];
                    x[i][cur_j] += add;
                    if (i == root) {
                        break;
                    }
                    int prev_j = parent_l[i];
                    x[i][prev_j] -= add;
                    cur_j = prev_j;
                }

                rem_a[root] -= add;
                rem_b[target] -= add;
            }
        }

        ll ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans += 1LL * x[i][j] * c[i][j];
            }
        }
        cout << ans << endl;
    }
    return 0;
}
