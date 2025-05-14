//https://basecamp.eolymp.com/en/problems/11838
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


bool chk(vector<int> &a) {
    for (int i = 2; i < a.size(); i++) {
        if ((a[i] + a[i - 1] + a[i - 2]) % 3 == 0) {
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
        int n;
        cin >> n;
        if (n == 4) {
            cout << "3 4 1 2" << endl;
            continue;
        }
        if (n == 5) {
            cout << "3 4 1 2 5" << endl;
            continue;
        }
        vector<int> ans;
        vector<int> have[3];
        for (int i = 1; i <= n; i++) {
            have[i % 3].push_back(i);
        }
        int j = 1;
        while (1) {
            if (have[j].size() < 2) {
                break;
            }
            ans.push_back(have[j].back());
            have[j].pop_back();
            ans.push_back(have[j].back());
            have[j].pop_back();
            j = (j + 1) % 3;
        }
        if (have[0].size() == 1 && have[1].size() == 1 && have[2].size() == 1) {
            assert(ans.back() % 3 == 0);
            ans.push_back(have[1].back());
            ans.push_back(have[0].back());
            ans.insert(ans.begin(), have[2].back());
        } else {
            vector<int> hv;
            if (have[0].size()) {
                hv.push_back(have[0].back());
            }
            if (have[1].size()) {
                hv.push_back(have[1].back());
            }
            if (have[2].size()) {
                hv.push_back(have[2].back());
            }
            if (hv.size() == 1) {
                ans.push_back(hv.back());
                if (!chk(ans)) {
                    ans.pop_back();
                    ans.insert(ans.begin(), hv.back());
                }
            } else if (hv.size() == 2) {
                ans.push_back(hv[0]);
                ans.insert(ans.begin(), hv.back());
                if (!chk(ans)) {
                    ans.pop_back();
                    ans.erase(ans.begin());
                    ans.push_back(hv.back());
                    ans.insert(ans.begin(), hv[0]);
                }
            }
        }
        assert(chk(ans));
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
