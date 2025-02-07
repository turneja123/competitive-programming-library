//https://codeforces.com/contest/2059/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;

vector<int> a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> v;
        for (int i = 0; i < n; i++) {
            a[i].clear();
            a[i].resize(n);
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
            }
            int c = 0;
            for (int j = n - 1; j >= 0; j--) {
                if (a[i][j] != 1) {
                    break;
                }
                c++;
            }
            v.push_back(c);
        }
        sort(v.begin(), v.end(), greater<int>());
        int need = 0;
        while (v.size()) {
            while (v.size() && v.back() < need) {
                v.pop_back();
            }
            if (v.empty()) {
                break;
            }
            need++;
            v.pop_back();
        }
        cout << need << endl;
    }
    return 0;
}
