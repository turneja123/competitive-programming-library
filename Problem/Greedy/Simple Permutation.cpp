//https://codeforces.com/contest/2089/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

bool is_prime[N];
vector<int> primes;

vector<int> attempt(int p, int n) {
    vector<int> tmp;
    vector<int> ans(n, 0);
    vector<int> seen(n + 1, 0);
    ans[0] = p;
    seen[p] = true;
    int i = 1;
    for (; i < n; i++) {
        int x = p;
        if (i % 2 == 1) {
            x = p - (i + 1) / 2;
        } else {
            x = p + (i + 1) / 2;
        }
        if (x <= 0 || x > n) {
            break;
        }
        ans[i] = x;
        seen[x] = true;
    }
    for (int ptr = 1; i < n; i++) {
        while (seen[ptr]) {
            ptr++;
        }
        ans[i] = ptr;
        seen[ptr] = true;
    }
    int ct = 0; ll sum = 0;
    for (int i = 0; i < n; i++) {
        sum += ans[i];
        if (is_prime[(sum + i) / (i + 1)]) {
            ct++;
        }
    }
    if (ct >= n / 3 - 1) {
        return ans;
    }
    return tmp;
}

int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int i = lower_bound(primes.begin(), primes.end(), n / 2) - primes.begin();
        vector<int> ans;
        for (int j = max(0, i - 15); j < min(N, i + 15); j++) {
            int p = primes[j];
            vector<int> v = attempt(p, n);
            if (v.size() > 0) {
                ans = v;
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
