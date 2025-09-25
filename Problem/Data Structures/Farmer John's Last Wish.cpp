//https://codeforces.com/contest/2148/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int SQ = 400;

vector<int> divs[N];

int freq[N];
int ct[N];
int ct_block[N];
int a[N];


int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            for (int d : divs[a[i]]) {
                if (freq[d] != 0) {
                    ct[freq[d]]--;
                    ct_block[freq[d] / SQ]--;
                }
                freq[d]++;
                ct[freq[d]]++;
                ct_block[freq[d] / SQ]++;
            }
            int b = 0, best = -1, ans = 0;
            for (; b < n; b++) {
                if ((b + 1) * SQ - 1 > i) {
                    break;
                }
                if (ct_block[b] > 0) {
                    best = b;
                }
            }
            if (best != -1) {
                for (int j = best * SQ; j < (best + 1) * SQ; j++) {
                    if (ct[j] > 0) {
                        ans = j;
                    }
                }
            }
            for (int j = b * SQ; j < (b + 1) * SQ; j++) {
                if (j > i) {
                    break;
                }
                if (ct[j] > 0) {
                    ans = j;
                }
            }
            cout << ans << " ";
        }
        cout << endl;

        for (int i = 0; i < n; i++) {
            for (int d : divs[a[i]]) {
                ct[freq[d]] = 0;
                ct_block[freq[d] / SQ] = 0;
                freq[d] = 0;
            }
        }
    }


    return 0;
}
