//https://usaco.org/index.php?page=viewproblem2&cpid=1547
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 1e9 + 7;

ll dp[N];
ll pw[N];
int enter[N];

pair<int, int> a[N];
vector<int> pos;

int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 2 % M;
    }
    int n, d;
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        if (a[i].second == 1) {
            pos.push_back(a[i].first);
        }
    }
    int mul = 0; ll sum = 0, sum_behind = 0;
    for (int i = 0, j = 0, l = 0; i < n; i++) {
        if (a[i].second == 0) {
            while (l < j && a[i].first - pos[l] > d) {
                dp[l] = dp[l] * pw[mul - enter[l]] % M;
                sum = (sum - dp[l] + M) % M;
                sum_behind = (sum_behind + dp[l]) % M;
                l++;
            }
            mul++;
            sum = sum * 2 % M;
        } else {
            enter[j] = mul;
            dp[j] = (1 + sum + sum_behind) % M;
            sum = (sum + dp[j]) % M;
            j++;
        }
    }
    cout << (sum_behind + sum) % M;


    return 0;
}
