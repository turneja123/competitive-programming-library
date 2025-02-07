//https://leetcode.com/contest/weekly-contest-435/problems/maximum-difference-between-even-and-odd-frequency-ii/
class Solution {
public:
    int maxDifference(string s, int k) {
        int n = s.size();
        int ans = -2 * n;
        for (int x = 0; x <= 4; x++) {
            for (int y = 0; y <= 4; y++) {
                vector<int> a(n);
                vector<int> px(n), py(n);
                for (int i = 0; i < n; i++) {
                    int c = s[i] - '0';
                    if (c == x) {
                        a[i] = 1;
                        px[i]++;
                    } else if (c == y) {
                        a[i] = -1;
                        py[i]++;
                    } else {
                        a[i] = 0;
                    }
                    if (i != 0) {
                        px[i] += px[i - 1];
                        py[i] += py[i - 1];
                    }
                }
                int fa = 0, fb = 0, s = 0;
                queue<tuple<int, int, int, int>> st;
                st.push(make_tuple(-1, 0, 0, 0));
                int mn[2][2];
                mn[0][0] = 2 * n;
                mn[0][1] = 2 * n;
                mn[1][0] = 2 * n;
                mn[1][1] = 2 * n;

                for (int i = 0; i < n; i++) {
                    if (a[i] == 1) {
                        fa = (fa + 1) % 2;
                    } else if (a[i] == -1) {
                        fb = (fb + 1) % 2;
                    }
                    s += a[i];
                    while (i - get<0>(st.front()) >= k) {
                        auto [j, fa, fb, s] = st.front();
                        int x = px[i] - (j == -1 ? 0 : px[j]);
                        int y = py[i] - (j == -1 ? 0 : py[j]);
                        if (x == 0 || y == 0) {
                            break;
                        }

                        mn[fa][fb] = min(mn[fa][fb], s);
                        st.pop();
                    }
                    if (!fa && !fb) {
                        ans = max(ans, s - mn[1][0]);
                    } else if (!fa && fb) {
                        ans = max(ans, s - mn[1][1]);
                    } else if (fa && !fb) {
                        ans = max(ans, s - mn[0][0]);
                    } else {
                        ans = max(ans, s - mn[0][1]);
                    }
                    st.push(make_tuple(i, fa, fb, s));
                }
            }
        }
        return ans;
    }
};
