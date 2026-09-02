//https://codeforces.com/contest/1423/problem/K
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int ok[N];
int nx[N];
int ans[N];
int add[N];

int main() {
    IOS;
    ans[1]++;
    for (int i = 2; i < N; i++) {
        nx[i] = N;
        if ((ll)i * i < N) {
            nx[i] = i * i;
        }
    }
    for (int i = 2; i < N; i++) {
        for (int j = i; j < N; j += i) {
            int x = j + i;
            if (x >= N) {
                continue;
            }
            int g = __gcd(x, j);
            vector<int> v{g, j / g, x / g};
            sort(v.begin(), v.end());
            if (v[0] + v[1] > v[2]) {
                ok[x] = 1;
                nx[j] = min(nx[j], x);
            }
        }
    }
    for (int i = 2; i < N; i++) {
        if (!ok[i]) {
            add[i]++;
            if (nx[i] < N) {
                add[nx[i]]--;
            }
        }
        ans[i] = ans[i - 1] + add[i];
    }

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cout << ans[x] << endl;
    }
    return 0;
}
