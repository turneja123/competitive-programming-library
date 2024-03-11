#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e7 + 105;

bool composite[N];
int ans[N];
vector<int> primes;

int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        if (!composite[i]) {
            for (int j = i + i; j < N; j += i) {
                composite[j] = true;
            }
            primes.push_back(i);
        }
    }
    ans[4] = 2;
    ans[5] = 2;
    int j = 1;
    for (int i = 6; i < N - 100; i++) {
        ans[i] = ans[i - 1];
        if (composite[i]) {
            ans[i]++;
            if (i == 2 * primes[j]) {
                ans[i]++, j++;
            }
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        cout << ans[n] << endl;
    }

    return 0;
}
