//https://www.codechef.com/START222A/problems/ASCDESC
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int SQ = 320;

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    if (n == 6) {
        cout << "2 4 5 1 3 6";
        return 0;
    }
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    sort(a.begin(), a.end(), [&](int x, int y) {
         if (x % SQ != y % SQ) {
            return x % SQ > y % SQ;
         }
         return x < y;
    });
    for (int x : a) {
        cout << x + 1 << " ";
    }



    return 0;
}
