//https://codeforces.com/contest/1542/problem/C
#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

bool composite[N];
vector<long long> nums;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < 64; i++) {
        nums.push_back(i);
    }
    for (int i = 2; i < 64; i++) {
        for (int j = i * 2; j < 64; j += i) {
            nums[j] /= nums[i];
        }
    }
    int t;
    cin >> t;
    while (t--) {
        long long n, ans = 0;
        cin >> n;
        for (long long i = 2; n > 0; i++) {
            long long m = n / nums[i];
            ans = (ans + ((n - m) * i) % M) % M;
            n = m;
        }
        cout << ans << endl;
    }
    return 0;
}
