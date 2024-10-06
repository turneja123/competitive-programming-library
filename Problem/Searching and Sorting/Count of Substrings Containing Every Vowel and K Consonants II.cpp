//https://leetcode.com/contest/weekly-contest-417/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/
const int N = 2e5 + 5;
int pref[26][N];
class Solution {
public:
    bool v[26];
    int ct[26];
    vector<char> vow{'a', 'e', 'i', 'o', 'u'};


    long long countOfSubstrings(string s, int k) {
        for (char c : vow) {
            v[c - 'a'] = true;
            pref[c - 'a'][0] = 0;
        }
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if (i != 0) {
                for (char c : vow) {
                    pref[c - 'a'][i] = pref[c - 'a'][i - 1];
                }
            }
            if (v[s[i] - 'a']) {
                pref[s[i] - 'a'][i]++;
            }
        }
        long long ans = 0; int mx = 0;
        for (int i = 0; i < n; i++) {
            int l = mx, r = i, rt = -1, lf = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                bool has = true; int ct = i - mid + 1;
                for (char c : vow) {
                    int x = pref[c - 'a'][i] - ((mid == 0) ? 0 : pref[c - 'a'][mid - 1]);
                    if (x == 0) {
                        has = false;
                    }
                    ct -= x;
                }
                if (ct > k) {
                    mx = mid + 1;
                }
                if (!has && ct > k) {
                    break;
                }
                if (!has || ct < k) {
                    r = mid - 1;
                } else if (ct == k) {
                    rt = mid;
                    l = mid + 1;
                } else {
                    l = mid + 1;
                }
            }
            if (rt == -1) {
                continue;
            }
            l = mx, r = rt;
            while (l <= r) {
                int mid = (l + r) / 2;
                bool has = true; int ct = i - mid + 1;
                for (char c : vow) {
                    int x = pref[c - 'a'][i] - ((mid == 0) ? 0 : pref[c - 'a'][mid - 1]);
                    if (x == 0) {
                        has = false;
                    }
                    ct -= x;
                }
                if (ct > k) {
                    mx = mid + 1;
                }
                if (!has && ct > k) {
                    break;
                }
                if (!has || ct < k) {
                    r = mid - 1;
                } else if (ct == k) {
                    lf = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            ans += rt - lf + 1;
        }
        return ans;
    }
};
