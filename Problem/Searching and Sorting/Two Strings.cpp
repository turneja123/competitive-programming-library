//https://www.spoj.com/problems/HARSTR/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int pref[N][26];

bool chk(vector<int> &a, vector<int> &b) {
    for (int i = 0; i < 26; i++) {
        if (b[i] > a[i]) {
            return false;
        }
    }
    return true;
}

bool lexi(vector<int> &a, vector<int> &b) {
    for (int i = 0; i < 26; i++) {
        if (a[i] > b[i]) {
            return true;
        }
        if (b[i] > a[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    IOS;
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    vector<int> freqa(26, 0);
    for (int i = 0; i < n; i++) {
        freqa[a[i] - 'a']++;
    }
    for (int i = 0; i < m; i++) {
        if (i != 0) {
            for (int j = 0; j < 26; j++) {
                pref[i][j] += pref[i - 1][j];
            }
        }
        pref[i][b[i] - 'a']++;
    }
    int best = 0; vector<int> ans(26, 0);
    for (int i = 0; i < m; i++) {
        int l = 0, r = i + 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            vector<int> freq(26, 0);
            for (int j = 0; j < 26; j++) {
                freq[j] += pref[m - 1][j];
                freq[j] -= pref[i][j];
                if (mid > 0) {
                    freq[j] += pref[mid - 1][j];
                }
            }
            if (chk(freqa, freq)) {
                l = mid + 1;
                if (m - (i - mid + 1) > best) {
                    best = m - (i - mid + 1);
                    ans = freq;
                } else if (m - (i - mid + 1) == best) {
                    if (lexi(freq, ans)) {
                        ans = freq;
                    }
                }
            } else {
                r = mid - 1;
            }
        }
    }
    if (best == 0) {
        cout << '-';
    } else {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < ans[i]; j++) {
                char c = 'a' + i;
                cout << c;
            }
        }
    }

    return 0;
}
