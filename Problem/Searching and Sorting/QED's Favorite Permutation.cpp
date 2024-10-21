//https://codeforces.com/contest/2030/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int need[N];
int diff[N];
int ct[N];
string s;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            if (a[i] > i) {
                diff[i]++;
                diff[a[i]]--;
            } else if (a[i] < i) {
                diff[a[i]]++;
                diff[i]--;

            }
        }
        cin >> s;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'R') {
                ct[i]++;
            } else {
                ct[i - 1]++;
            }
        }
        int bad = 0, sum = 0;
        for (int i = 0; i < n; i++) {
            sum += diff[i];
            if (sum > 0) {
                need[i] = true;
            }
            if (need[i] && ct[i] == 0) {
                bad++;
            }
        }
        for (int j = 0; j < q; j++) {
            int i;
            cin >> i;
            i--;
            if (s[i] == 'R') {
                ct[i]--;
                if (ct[i] == 0 && need[i]) {
                    bad++;
                }
                ct[i - 1]++;
                if (ct[i - 1] == 1 && need[i - 1]) {
                    bad--;
                }
                s[i] = 'L';
            } else {
                ct[i - 1]--;
                if (ct[i - 1] == 0 && need[i - 1]) {
                    bad++;
                }
                ct[i]++;
                if (ct[i] == 1 && need[i]) {
                    bad--;
                }
                s[i] = 'R';
            }
            if (bad == 0) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
        for (int i = 0; i < n; i++) {
            diff[i] = 0;
            need[i] = 0;
            ct[i] = 0;
        }
    }


    return 0;
}
