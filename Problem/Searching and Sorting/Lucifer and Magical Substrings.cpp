//https://www.spoj.com/problems/MAGSUB1/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<int> primes{2, 3, 5, 7, 11, 13, 17, 19, 23};
bool is_prime[27];
int freq[26];

int main() {
    IOS;
    for (int p : primes) {
        is_prime[p] = true;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        long long ans = (long long)n * (n + 1) / 2;
        int l = 0, ct = 0;
        for (int i = 0; i < n; i++) {
            freq[s[i] - 'A']++;
            if (freq[s[i] - 'A'] == 1 && is_prime[s[i] - 'A' + 1]) {
                ct++;
            }
            while (l <= i && ct) {
                freq[s[l] - 'A']--;
                if (freq[s[l] - 'A'] == 0 && is_prime[s[l] - 'A' + 1]) {
                    ct--;
                }
                l++;
            }
            ans -= i - l + 1;
        }
        cout << ans << endl;
    }
    return 0;
}
