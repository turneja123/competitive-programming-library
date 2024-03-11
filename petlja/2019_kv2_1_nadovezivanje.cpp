#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

bool comp(string a, string b) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i] > b[i]) {
            return 1;
        }
        if (b[i] > a[i]) {
            return 0;
        }
    }
    return 0;
}

int main() {
    IOS;
    string a, b, c;
    cin >> a >> b >> c;
    string sol[6];
    sol[0] = a + b + c;
    sol[1] = a + c + b;
    sol[2] = b + a + c;
    sol[3] = b + c + a;
    sol[4] = c + a + b;
    sol[5] = c + b + a;
    sort(sol, sol + 6, comp);
    cout << sol[0];
    return 0;

}
