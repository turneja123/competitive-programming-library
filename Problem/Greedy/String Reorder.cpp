//https://cses.fi/problemset/task/1743
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int ans[N];
int freq[26];

int main() {
    IOS;
    string s;
    cin >> s;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        freq[s[i] - 'A']++;
    }
    int can = (n + 1) / 2;
    multiset<int> st;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > can) {
            cout << -1;
            return 0;
        }
        if (freq[i] > 0) {
            st.insert(freq[i]);
        }
    }
    int last = -1, m = n;
    for (int i = 0; i < n; i++) {
        m--;
        int can = (m + 1) / 2;
        for (int j = 0; j < 26; j++) {
            if (freq[j] > 0 && last != j) {
                st.erase(st.find(freq[j]));
                freq[j]--;
                st.insert(freq[j]);
                if (*st.rbegin() > can) {
                    st.erase(st.find(freq[j]));
                    freq[j]++;
                    st.insert(freq[j]);
                } else {
                    ans[i] = j;
                    last = j;
                    break;
                }
            }
        }
        char c = 'A' + ans[i];
        cout << c;
    }

    return 0;
}
