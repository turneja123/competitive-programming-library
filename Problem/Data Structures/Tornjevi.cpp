//https://evaluator.hsin.hr/events/coci26_2/tasks/HONI252628tornjevi/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int B = 320;

int ans[N];
int a[N];
vector<tuple<int, int, int>> queries[B];


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'P') {
            a[i] = 1;
        }
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[l / B].push_back(make_tuple(r, l, i));
    }
    for (int i = 0; i < B; i++) {
        if (queries[i].empty()) {
            continue;
        }

        sort(queries[i].begin(), queries[i].end());

        int ptr = (i + 1) * B;
        int xu = 0, yu = 0, xd = 0, yd = 0;

        for (auto [r, l, ind] : queries[i]) {
            while (ptr <= r) {
                if (a[ptr] == 0) {
                    if (yu > 0) {
                        yu--;
                        xu++;
                    } else {
                        xu++;
                        xd++;
                    }
                } else {
                    if (xu > 0) {
                        xu--;
                        yu++;
                    } else {
                        yu++;
                        yd++;
                    }
                }
                ptr++;
            }
            tuple<int, int, int, int> restore = make_tuple(xu, yu, xd, yd);
            for (int j = min(r, (i + 1) * B - 1); j >= l; j--) {
                if (a[j] == 0) {
                    if (yd > 0) {
                        yd--;
                        xd++;
                    } else {
                        xd++;
                        xu++;
                    }
                } else {
                    if (xd > 0) {
                        xd--;
                        yd++;
                    } else {
                        yd++;
                        yu++;
                    }
                }
            }
            ans[ind] = xu + yu;
            tie(xu, yu, xd, yd) = restore;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }





    return 0;
}
