#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int main() {
    IOS;
    int n;
    cin >> n;
    string sol = "DA";
    int mx = -1;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        bool pr = false;
        int mn = 2e9;
        for (int j = 0; j < s.size(); j++) {
            string a = "";
            string b = "";
            for (int p = 0; p < j; p++) {
                a += s[p];
            }
            for (int p = j; p < s.size(); p++) {
                b += s[p];
            }
            string nw = b + a;
            int br = stoi(nw);
            if (br < mn && br >= mx) {
                mn = br;
                pr = true;
            }
        }
        if (!pr) {
            sol = "NE";
        }
        mx = mn;
    }
    cout << sol;
    return 0;

}
