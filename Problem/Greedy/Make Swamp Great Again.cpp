//https://algotester.com/en/ArchiveProblem/DisplayWithFile/71139
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int bad[N];
int ct[N];
int a[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        bad[a[i]] = 1;
        ct[a[i]]++;
    }
    for (int i = 0; i < n; i++) {
        int x = (i - 2 + n) % n, y = (i - 1 + n) % n, z = i;
        int mn = min({a[x], a[y], a[z]}), mx = max({a[x], a[y], a[z]});
        if (!(mn < a[i] && a[i] < mx)) {
            bad[a[i]] = 0;
        }

        x = (i - 1 + n) % n, y = i % n, z = (i + 1) % n;
        mn = min({a[x], a[y], a[z]}), mx = max({a[x], a[y], a[z]});
        if (!(mn < a[i] && a[i] < mx)) {
            bad[a[i]] = 0;
        }

        x = i % n, y = (i + 1) % n, z = (i + 2) % n;
        mn = min({a[x], a[y], a[z]}), mx = max({a[x], a[y], a[z]});
        if (!(mn < a[i] && a[i] < mx)) {
            bad[a[i]] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << n - ct[a[i]] + bad[a[i]] << " ";
    }

    return 0;
}
