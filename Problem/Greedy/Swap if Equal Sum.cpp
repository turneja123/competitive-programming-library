//https://atcoder.jp/contests/arc203/tasks/arc203_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int b[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int cta = 0, ctb = 0;
        int c = 1;
        int posa = 0, posb = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] == 1) {
                cta++;
                posa = i;
            }
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            if (a[i] != b[i]) {
                c = 0;
            }
            if (b[i] == 1) {
                ctb++;
                posb = i;
            }
        }
        if (cta != ctb) {
            cout << "No" << endl;
        } else if (cta == 1 && !c) {
            if (posa == 0 || posa == n - 1 || posb == 0 || posb == n - 1) {
                cout << "No" << endl;
            } else {
                cout << "Yes" << endl;
            }
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}
