//https://codeforces.com/contest/1997/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;
const int SQ = 450;

int a[N];
int sum_heavy[N];
bool can[SQ][N];
bool can_heavy[N];

vector<pair<int, int>> ivals;
tuple<int, int, int> queries[N];
string ans[N];


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    for (int k = 1; k < SQ; k++) {
        int j = 0, sum = 0, l = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] >= j) {
                can[k][i] = true;
                sum++;
            }
            if (sum == k) {
                if (k == SQ - 1) {
                    sum_heavy[j] = SQ - 1;
                    ivals.push_back(make_pair(l, i));
                }
                j++;
                sum = 0;
                l = i + 1;
            }
        }
        if (k == SQ - 1 && l != n) {
            sum_heavy[j] = sum;
            ivals.push_back(make_pair(l, n - 1));
        }
    }
    for (int i = 0; i < n; i++) {
        can_heavy[i] = can[SQ - 1][i];
    }
    for (int i = 0; i < q; i++) {
        int j, k;
        cin >> j >> k;
        queries[i] = make_tuple(k, j - 1, i);
    }
    sort(queries, queries + q);
    int cur = SQ - 1;
    for (int i = 0; i < q; i++) {
        int k = get<0>(queries[i]), ind = get<1>(queries[i]);
        if (k < SQ) {
            ans[get<2>(queries[i])] = ((can[k][ind]) ? "YES" : "NO");
            continue;
        }
        if (cur < k) {
            for (int j = 0; j < ivals.size(); j++) {
                int l = ivals[j].first;
                if (j != 0) {
                    while (ivals[j - 1].second >= l) {
                        if (a[l] >= j) {
                            sum_heavy[j]--;
                        }
                        l++;
                    }
                }
                ivals[j].first = l;
                if (l == n) {
                    continue;
                }
                int r = ivals[j].second;
                while (r < n - 1 && sum_heavy[j] < k) {
                    r++;
                    if (a[r] >= j) {
                        sum_heavy[j]++;
                        can_heavy[r] = true;
                    }
                }
                ivals[j].second = r;
            }
            while (ivals[ivals.size() - 1].first == n) {
                ivals.pop_back();
            }
            cur = k;
        }
        ans[get<2>(queries[i])] = ((can_heavy[ind]) ? "YES" : "NO");
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
