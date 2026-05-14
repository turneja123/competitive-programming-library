//https://codeforces.com/contest/2069/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int a, b, ab, ba;
        cin >> a >> b >> ab >> ba;

        int cta = 0, ctb = 0, n = s.size();


        vector<pair<int, int>> v;
        int j = 0;

        int ctab = 0, ctba = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] == 'A') {
                cta++;
            } else {
                ctb++;
            }

            if (i != 0 && s[i] == s[i - 1]) {
                if (s[j] == 'A' && (i - j) % 2 == 0) {
                    ctba += (i - j - 1) / 2;
                    v.push_back({0, (i - j) / 2});
                } else if (s[j] == 'B' && (i - j) % 2 == 0) {
                    ctba += (i - j) / 2;
                    v.push_back({2, (i - j - 1) / 2});
                } else {
                    ctba += (i - j) / 2;
                    v.push_back({1, (i - j) / 2});
                }
                j = i;
            }
        }
        int i = n;
        if (s[j] == 'A' && (i - j) % 2 == 0) {
            ctba += (i - j - 1) / 2;
            v.push_back({0, (i - j) / 2});
        } else if (s[j] == 'B' && (i - j) % 2 == 0) {
            ctba += (i - j) / 2;
            v.push_back({2, (i - j - 1) / 2});
        } else {
            ctba += (i - j) / 2;
            v.push_back({1, (i - j) / 2});
        }

        sort(v.begin(), v.end(), [&](auto a, auto b) {
             if (a.first != b.first) {
                return a.first < b.first;
             }
             if (a.first == 0) {
                return a.second < b.second;
             }
             return a.second > b.second;

        });
        string ans = "NO";
        if (cta - min(ctba, ba) <= a && ctb - min(ctba, ba) <= b) {
            ans = "YES";
        }

        for (auto [x, f] : v) {
            for (int i = 0; i < f; i++) {
                ctab++;
                ctba--;
                if (x == 0 && i == f - 1) {
                    ctba++;
                }
                if (x == 2 && i == 0) {
                    ctba--;
                }
                if (cta - min(ctba, ba) - min(ctab, ab) <= a && ctb - min(ctba, ba) - min(ctab, ab) <= b) {
                    ans = "YES";
                }

            }
        }

        cout << ans << endl;

    }

    return 0;
}
