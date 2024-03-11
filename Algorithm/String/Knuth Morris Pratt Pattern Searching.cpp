//https://cses.fi/problemset/task/1753/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

void LPS(string pat, int m, int lps[]) {
    int len = 0;
    int i = 1;
    lps[0] = 0;
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = len;
                i++;
            }
        }
    }
}

int KMP(string pat, string txt) {
    int m = pat.length();
    int n = txt.length();
    int lps[m];
    int j = 0;
    LPS(pat, m, lps);
    int i = 0;
    int res = 0;
    while (i < n) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == m) {
            j = lps[j - 1];
            res++;
        } else if (i < n && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i = i + 1;
            }
        }
    }
    return res;
}

int main() {
    IOS;
    string a, b;
    cin >> a >> b;
    cout << KMP(b, a);
    return 0;

}
