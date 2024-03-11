//https://leetcode.com/problems/meeting-rooms-iii/
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        vector<pair<long long, long long>> v;
        for (int i = 0; i < meetings.size(); i++) {
            pair<long long, long long> p = make_pair(meetings[i][0], meetings[i][1]);
            v.push_back(p);
        }
        sort(v.begin(), v.end());
        vector<long long> ans(n, 0);
        vector<long long> rooms(n, 0);
    
        priority_queue<pair<long long, long long>> pq;
        priority_queue<pair<long long, long long>> waiting;

        for (int i = 0; i < v.size(); i++) {
            while (pq.size() && -pq.top().first <= v[i].first) {
                long long room = -pq.top().second;
                if (waiting.size()) {
                    ans[room]++;
                    rooms[room] = waiting.top().second + waiting.top().first - pq.top().first;
                    pq.push(make_pair(-rooms[room], -room));
                    waiting.pop();
                }
                pq.pop();
            }

            long long room = -1;
            for (int j = 0; j < n && room == -1; j++) {
                if (rooms[j] <= v[i].first) {
                    room = j;
                    ans[j]++;
                    rooms[j] = v[i].second;
                }
            }
            if (room == -1) {
                waiting.push(make_pair(-v[i].first, v[i].second));
            } else {
                pq.push(make_pair(-v[i].second, -room));

            }
        }
        while (pq.size()) {
            long long room = -pq.top().second;
            if (waiting.size()) {
                ans[room]++;
                rooms[room] = waiting.top().second + waiting.top().first - pq.top().first;
                pq.push(make_pair(-rooms[room], -room));
                waiting.pop();
            }
            pq.pop();
        }
        long long room = -1, mx = -1;
        for (int i = 0; i < n; i++) {
            if (ans[i] > mx) {
                mx = ans[i];
                room = i;
            }
        }
        return room;
    }
};