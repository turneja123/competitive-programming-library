//https://arena.petlja.org/sr-Latn-RS/competition/bubblecup17finals#tab_136689
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

int main() {
    IOS;
    int n;
    cin >> n;
    string s;
    cin >> s;
    if (s == "0" || s == "1" || s == "2") {
        cout << s;
    } else if (s == "7" || s == "9" || s == "3" || s == "4" || s == "8" || s == "6") {
        cout << 2;
    } else if (s == "5") {
        cout << 0;
    } else {
        for (int i = 0; i < n; i++) {
            cout << 0;
        }
    }

    return 0;
}
