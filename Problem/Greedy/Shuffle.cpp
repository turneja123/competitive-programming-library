//https://eolymp.com/en/compete/qn51qrti910ch6lpn4ju3memsk/problem/4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];
int is_prime[N];

vector<int> try_1(vector<int> pr, vector<int> all_pr, int n) {
    vector<int> ans(n + 1, -1);
    int r = n;
    for (int i : pr) {
        ans[i] = a[r--];
    }
    for (int i : all_pr) {
        ans[i] = a[r--];
    }
    for (int i = 1; i <= n; i++) {
        if (ans[i] == -1) {
            ans[i] = a[r--];
        }
    }
    return ans;
}

vector<int> try_2(vector<int> pr, vector<int> all_pr, int n) {
    vector<int> ans(n + 1, -1);
    int l = 1, r = n;
    for (int i : pr) {
        ans[i] = a[r--];
    }
    reverse(all_pr.begin(), all_pr.end());
    for (int i : all_pr) {
        ans[i] = a[r--];
        for (int j = 2 * i; j <= n; j += i) {
            if (ans[j] == -1) {
                ans[j] = a[l++];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (ans[i] == -1) {
            ans[i] = a[r--];
        }
    }
    return ans;
}

int calc(vector<int> &ans) {
    int sol = 0, n = ans.size() - 1;
    for (int i = 1; i <= n; i++) {
        if (is_prime[i]) {
            int mx1 = ans[i], mx2 = -10000;
            for (int j = 2 * i; j <= n; j += i) {
                if (ans[j] > mx1) {
                    mx2 = mx1;
                    mx1 = ans[j];
                } else if (ans[j] > mx2) {
                    mx2 = ans[j];
                }
            }
            sol = max(sol, mx1 + mx2);
        }
    }
    return sol;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    for (int i = 2; i <= n; i++) {
        is_prime[i] = 1;
    }
    vector<int> pr{1};
    vector<int> all_pr;

    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            int ok = 1;
            for (int j = 2 * i; j <= n; j += i) {
                is_prime[j] = 0;
                ok = 0;
            }
            if (ok) {
                pr.push_back(i);
            } else {
                all_pr.push_back(i);
            }

        }
    }
    vector<int> ans; int best = 7;
    vector<vector<int>> all{try_1(pr, all_pr, n), try_2(pr, all_pr, n)};
    for (auto v : all) {
        if (calc(v) < best) {
            ans = v;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }


    return 0;
}
