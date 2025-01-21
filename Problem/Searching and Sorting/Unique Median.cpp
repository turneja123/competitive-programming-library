//https://codeforces.com/contest/2056/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];
int pref[N];

map<int, int> odd;
map<int, int> even;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
        }
        long long ans = (long long)n * (n + 1) / 2;
        for (int j = 0; j < 10; j++) {
            int l = -1;
            for (int i = 0; i < n; i++) {
                if (i == 0) {
                    pref[i] = 0;
                } else {
                    pref[i] = pref[i - 1];
                }
                if (a[i] <= j) {
                    pref[i]++;
                    if (a[i] == j) {
                        while (l < i) {
                            if (l == -1) {
                                odd[1]++;
                            } else {
                                if (l % 2 == 0) {
                                    even[pref[l] - l / 2]++;
                                } else {
                                    odd[pref[l] - l / 2]++;
                                }
                            }
                            l++;
                        }
                    }
                }
                if (i % 2 == 0) {
                    ans -= even[pref[i] - i / 2];
                } else {
                    ans -= odd[pref[i] - i / 2];
                }
            }
            even.clear();
            odd.clear();
        }
        cout << ans << endl;
    }
    return 0;
}
