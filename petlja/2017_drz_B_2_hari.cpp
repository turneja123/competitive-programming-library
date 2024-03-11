#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

set <int> st;
unordered_map <int,int> mp;

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        st.insert(a[i]);
    }
    int ct = 0;
    for (auto it = st.begin(); it != st.end(); ++it) {
         mp.insert({*it, ct++});
    }
    for (int i = 0; i < n; i++) {
        auto it = mp.find(a[i]);
        a[i] = it->second;
    }

    int sol = 0;
    vector <int> divs;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            divs.push_back(i);
        }
    }
    for (int l = 0; l < divs.size(); l++) {
        int freq[n] = { };
        int d = divs[l];
        bool b = true;
        for (int i = 0; i < n / d; i++) {
            vector <int> seen;
            for (int j = d * i; j < min(n, d * (i + 1)); j++) {
                freq[a[j]]++;
                seen.push_back(a[j]);
            }
            for (auto it = seen.begin(); it != seen.end(); ++it) {
                if (freq[*it] > k)
                    b = false;
                freq[*it] = 0;
            }
        }
        if (b) {
            sol++;
        }
    }
    cout << sol;
    return 0;
}
