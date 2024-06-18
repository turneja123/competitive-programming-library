//https://www.spoj.com/problems/NONDEC/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const int M = 98765431;

int dp_left[3][10][N];
int dp_right[3][10][N];
int ans_left[10];
int pref[3][10][N];

long long ans = 0;

void calc_left(string &s, int sgn) {
    for (int d = 1; d < 10; d++) {
        dp_left[0][d][0] = 0;
        dp_left[1][d][0] = 0;
        dp_left[2][d][0] = 0;
        int c = s[0] - '0';

        if (c > d) {
            dp_left[0][d][0] = 1;
        } else if (c == d) {
            dp_left[2][d][0] = 1;
        } else {
            dp_left[1][d][0] = 1;
        }
        pref[0][d][0] = pref[0][d - 1][0] + dp_left[0][d][0];
        pref[1][d][0] = pref[1][d - 1][0] + dp_left[1][d][0];
        pref[2][d][0] = pref[2][d - 1][0] + dp_left[2][d][0];
    }
    for (int i = 1; i < s.size(); i++) {
        int c = s[i] - '0';
        for (int d = 1; d < 10; d++) {
            dp_left[0][d][i] = 0;
            dp_left[1][d][i] = 0;
            dp_left[2][d][i] = 0;
            if (c > d) {
                dp_left[0][d][i] = (pref[0][d][i - 1] + pref[2][d][i - 1]) % M;
                dp_left[1][d][i] = pref[1][d][i - 1];
            } else if (c == d) {
                dp_left[0][d][i] = pref[0][d][i - 1];
                dp_left[1][d][i] = pref[1][d][i - 1];
                dp_left[2][d][i] = pref[2][d][i - 1];
            } else {
                dp_left[1][d][i] = (pref[1][d][i - 1] + pref[2][d][i - 1]) % M;
                dp_left[0][d][i] = pref[0][d][i - 1];
            }
            pref[0][d][i] = pref[0][d - 1][i] + dp_left[0][d][i];
            pref[1][d][i] = pref[1][d - 1][i] + dp_left[1][d][i];
            pref[2][d][i] = pref[2][d - 1][i] + dp_left[2][d][i];
            pref[0][d][i] %= M;
            pref[1][d][i] %= M;
            pref[2][d][i] %= M;
        }
    }
    for (int i = 0; i < s.size(); i++) {
        for (int d = 1; d < 10; d++) {
            ans_left[d] += dp_left[0][d][i] * sgn;
            ans_left[d] += dp_left[2][d][i] * sgn;
            if (i != s.size() - 1) {
                ans_left[d] += dp_left[1][d][i] * sgn;
            }
            ans_left[d] = (ans_left[d] + 10 * M) % M;
        }
    }
}

void calc_right(string &s, int sgn) {
    for (int f = 1; f < 10; f++) {

        int pref_ans = 0;
        for (int d = 1; d <= f; d++) {
            pref_ans += ans_left[d];
        }
        pref_ans %= M;
        for (int d = 1; d < 10; d++) {
            dp_right[0][d][0] = 0;
            dp_right[1][d][0] = 0;
            dp_right[2][d][0] = 0;
            if (d == f) {
                int c = s[0] - '0';

                if (c > d) {
                    dp_right[0][d][0] = 1;
                } else if (c == d) {
                    dp_right[2][d][0] = 1;
                } else {
                    dp_right[1][d][0] = 1;
                }
            }

            pref[0][d][0] = pref[0][d - 1][0] + dp_right[0][d][0];
            pref[1][d][0] = pref[1][d - 1][0] + dp_right[1][d][0];
            pref[2][d][0] = pref[2][d - 1][0] + dp_right[2][d][0];
        }
        for (int i = 1; i < s.size(); i++) {
            int c = s[i] - '0';
            pref[0][f - 1][i] = 0;
            pref[1][f - 1][i] = 0;
            pref[2][f - 1][i] = 0;
            for (int d = f; d < 10; d++) {
                dp_right[0][d][i] = 0;
                dp_right[1][d][i] = 0;
                dp_right[2][d][i] = 0;
                if (c > d) {
                    dp_right[0][d][i] = (pref[0][d][i - 1] + pref[2][d][i - 1]) % M;
                    dp_right[1][d][i] = pref[1][d][i - 1];
                } else if (c == d) {
                    dp_right[0][d][i] = pref[0][d][i - 1];
                    dp_right[1][d][i] = pref[1][d][i - 1];
                    dp_right[2][d][i] = pref[2][d][i - 1];
                } else {
                    dp_right[1][d][i] = (pref[1][d][i - 1] + pref[2][d][i - 1]) % M;
                    dp_right[0][d][i] = pref[0][d][i - 1];
                }
                pref[0][d][i] = pref[0][d - 1][i] + dp_right[0][d][i];
                pref[1][d][i] = pref[1][d - 1][i] + dp_right[1][d][i];
                pref[2][d][i] = pref[2][d - 1][i] + dp_right[2][d][i];
                pref[0][d][i] %= M;
                pref[1][d][i] %= M;
                pref[2][d][i] %= M;
            }
        }
        for (int i = 0; i < s.size(); i++) {
            for (int d = f; d < 10; d++) {
                ans += (long long)pref_ans * dp_right[0][d][i] * sgn;
                ans += (long long)pref_ans * dp_right[2][d][i] * sgn;
                if (i != s.size() - 1) {
                    ans += (long long)pref_ans * dp_right[1][d][i] * sgn;
                }
                ans = (ans + (long long)M * M * 10) % M;
            }
        }
    }
}

bool check(string s) {
    for (int i = 1; i < s.size(); i++) {
        if (s[i - 1] > s[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        ans = 0;
        string a, b, c, d;
        cin >> a >> b >> c >> d;
        calc_left(b, 1);
        calc_left(a, -1);
        if (check(a)) {
            ans_left[a[a.size() - 1] - '0']++;
        }
        calc_right(d, 1);
        calc_right(c, -1);
        if (check(c)) {
            for (int d = 1; d < 10; d++) {
                int ch = c[0] - '0';
                if (ch < d) {
                    break;
                }
                ans += ans_left[d];
            }
        }
        cout << ans % M << endl;
        for (int d = 1; d < 10; d++) {
            ans_left[d] = 0;
        }
    }

    return 0;
}
