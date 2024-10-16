//https://www.spoj.com/problems/RGBRED/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

const int N = 1e5 + 5;

int a[N];
int freq[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        freq[0] = 0, freq[1] = 0, freq[2] = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'R') {
                a[i] = 0;
            } else if (s[i] == 'G') {
                a[i] = 1;
            } else {
                a[i] = 2;
            }
            freq[a[i]]++;
        }
        vector<int> freqs;
        for (int j = 0; j < 3; j++) {
            if (freq[j] > 0) {
                freqs.push_back(freq[j]);
            }
        }
        if (freqs.size() == 1) {
            cout << n << endl;
        } else {
            int md = freqs[0] % 2, ans = 2;
            for (int j = 0; j < 3; j++) {
                if (freq[j] % 2 != md) {
                    ans = 1;
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}
