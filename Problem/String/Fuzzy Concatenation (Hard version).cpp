//https://codeforces.com/contest/2196/problem/E2
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <iterator>
#pragma GCC target("popcnt")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

class BITSET {
public:
    using ubig = unsigned long long;
    int sz;
    vector<ubig> blocks;
    BITSET(int n) : sz(n) {
        int len = (n + 8 * (int)sizeof(ubig) - 1) / (8 * (int)sizeof(ubig));
        blocks.assign(len, 0ULL);
    }
    void set(int i) {
        int block = i / (8 * (int)sizeof(ubig));
        int offset = i % (8 * (int)sizeof(ubig));
        blocks[block] |= (1ULL << offset);
    }
    BITSET& set() {
        for (auto &blk : blocks)
            blk = ~0ULL;
        int extra = (int)blocks.size() * 8 * (int)sizeof(ubig) - sz;
        if (extra > 0) {
            ubig mask = ~0ULL >> extra;
            blocks.back() &= mask;
        }
        return *this;
    }
    BITSET& set(int l, int r) {
        if (l < 0) l = 0;
        if (r >= sz) r = sz - 1;
        if (l > r) return *this;
        const int B = 8 * sizeof(ubig);
        int startBlock = l / B;
        int endBlock   = r / B;
        int startOff   = l % B;
        int endOff     = r % B;

        if (startBlock == endBlock) {
            ubig mask = ((~0ULL >> (B - (r - l + 1))) << startOff);
            blocks[startBlock] |= mask;
        } else {
            ubig firstMask = (~0ULL << startOff);
            blocks[startBlock] |= firstMask;
            for (int b = startBlock + 1; b < endBlock; ++b)
                blocks[b] = ~0ULL;
            ubig lastMask = (~0ULL >> (B - 1 - endOff));
            blocks[endBlock] |= lastMask;
        }
        int extra = (int)blocks.size() * B - sz;
        if (extra > 0) {
            ubig tailMask = ~0ULL >> extra;
            blocks.back() &= tailMask;
        }
        return *this;
    }
    bool test(int i) const {
        int block = i / (8 * (int)sizeof(ubig));
        int offset = i % (8 * (int)sizeof(ubig));
        return (blocks[block] >> offset) & 1ULL;
    }
    BITSET& reset() {
        fill(blocks.begin(), blocks.end(), 0ULL);
        return *this;
    }
    void reset(int i) {
        int block = i / (8 * (int)sizeof(ubig));
        int offset = i % (8 * (int)sizeof(ubig));
        blocks[block] &= ~(1ULL << offset);
    }
    BITSET& reset(int l, int r) {
        if (l < 0)       l = 0;
        if (r >= sz)     r = sz - 1;
        if (l > r)       return *this;
        const int B = 8 * sizeof(ubig);
        int startBlock = l / B;
        int endBlock   = r / B;
        int startOff   = l % B;
        int endOff     = r % B;
        if (startBlock == endBlock) {
            ubig mask = ((~0ULL >> (B - (r - l + 1))) << startOff);
            blocks[startBlock] &= ~mask;
        } else {
            ubig firstMask = (~0ULL << startOff);
            blocks[startBlock] &= ~firstMask;
            for (int b = startBlock + 1; b < endBlock; ++b)
                blocks[b] = 0ULL;
            ubig lastMask = (~0ULL >> (B - 1 - endOff));
            blocks[endBlock] &= ~lastMask;
        }
        return *this;
    }
    BITSET& flip() {
        for (auto &blk : blocks)
            blk = ~blk;
        int extra = (int)blocks.size() * 8 * (int)sizeof(ubig) - sz;
        if (extra > 0) {
            ubig mask = ~0ULL >> extra;
            blocks.back() &= mask;
        }
        return *this;
    }
    void flip(int i) {
        int block = i / (8 * (int)sizeof(ubig));
        int offset = i % (8 * (int)sizeof(ubig));
        blocks[block] ^= (1ULL << offset);
    }
    int count() const {
        int cnt = 0;
        for (auto blk : blocks)
            cnt += __builtin_popcountll(blk);
        return cnt;
    }
    bool any() const {
        for (auto blk : blocks)
            if (blk != 0) return true;
        return false;
    }
    bool none() const {
        return !any();
    }
    bool all() const {
        int fullBlocks = sz / (8 * (int)sizeof(ubig));
        for (int i = 0; i < fullBlocks; i++)
            if (blocks[i] != ~0ULL) return false;
        int remaining = sz % (8 * (int)sizeof(ubig));
        if (remaining > 0) {
            ubig mask = (1ULL << remaining) - 1;
            if (blocks[fullBlocks] != mask) return false;
        }
        return true;
    }
    BITSET extract(int l, int r) const { // turn off every bit not in range [l, r]
        BITSET res(sz);
        if (l < 0) l = 0;
        if (r >= sz) r = sz - 1;
        if (l > r) return res;
        const int B = 8 * sizeof(ubig);

        int startBlock = l / B, endBlock = r / B;
        int startOff = l % B, endOff = r % B;

        if (startBlock == endBlock) {
            ubig mask = ((~0ULL >> (B - (r - l + 1))) << startOff);
            res.blocks[startBlock] = blocks[startBlock] & mask;
        } else {
            ubig firstMask = ~0ULL << startOff;
            res.blocks[startBlock] = blocks[startBlock] & firstMask;
            for (int b = startBlock + 1; b < endBlock; ++b)
                res.blocks[b] = blocks[b];
            ubig lastMask = (~0ULL >> (B - 1 - endOff));
            res.blocks[endBlock] = blocks[endBlock] & lastMask;
        }
        int extra = (int)blocks.size() * B - sz;
        if (extra > 0) {
            ubig tailMask = ~0ULL >> extra;
            res.blocks.back() &= tailMask;
        }
        return res;
    }
    string to_string() const {
        string s;
        s.resize(sz);
        for (int i = 0; i < sz; i++)
            s[sz - 1 - i] = test(i) ? '1' : '0';
        return s;
    }
    BITSET& operator|=(const BITSET& other) {
        assert(blocks.size() == other.blocks.size());
        for (size_t i = 0; i < blocks.size(); i++)
            blocks[i] |= other.blocks[i];
        return *this;
    }
    BITSET& operator&=(const BITSET& other) {
        assert(blocks.size() == other.blocks.size());
        for (size_t i = 0; i < blocks.size(); i++)
            blocks[i] &= other.blocks[i];
        return *this;
    }
    BITSET& and_not(const BITSET& other) {
        assert(blocks.size() == other.blocks.size());
        for (size_t i = 0; i < blocks.size(); i++)
            blocks[i] &= ~other.blocks[i];
        return *this;
    }
    BITSET& operator^=(const BITSET& other) {
        assert(blocks.size() == other.blocks.size());
        for (size_t i = 0; i < blocks.size(); i++)
            blocks[i] ^= other.blocks[i];
        int extra = (int)blocks.size() * 8 * (int)sizeof(ubig) - sz;
        if (extra > 0) {
            ubig mask = ~0ULL >> extra;
            blocks.back() &= mask;
        }
        return *this;
    }
    BITSET operator|(const BITSET& other) const {
        BITSET res(*this);
        res |= other;
        return res;
    }
    BITSET operator&(const BITSET& other) const {
        BITSET res(*this);
        res &= other;
        return res;
    }
    BITSET operator^(const BITSET& other) const {
        BITSET res(*this);
        res ^= other;
        return res;
    }
    BITSET operator~() const {
        BITSET res(*this);
        res.flip();
        return res;
    }
    BITSET& operator<<=(int shift) {
        if(shift >= sz) {
            fill(blocks.begin(), blocks.end(), 0ULL);
            return *this;
        }
        const int B = 8 * (int)sizeof(ubig);
        if (shift == 1) {
            ubig carry = 0;
            for (size_t i = 0; i < blocks.size(); i++) {
                ubig ncarry = blocks[i] >> (B - 1);
                blocks[i] = (blocks[i] << 1) | carry;
                carry = ncarry;
            }
            int extra = (int)blocks.size() * B - sz;
            if (extra > 0) {
                ubig mask = ~0ULL >> extra;
                blocks.back() &= mask;
            }
            return *this;
        }
        int blockShift = shift / B;
        int bitShift = shift % B;
        int nblocks = blocks.size();
        vector<ubig> newBlocks(nblocks, 0ULL);
        for (int i = nblocks - 1; i >= 0; i--) {
            int srcIndex = i - blockShift;
            if (srcIndex < 0) continue;
            newBlocks[i] |= blocks[srcIndex] << bitShift;
            if (bitShift > 0 && srcIndex - 1 >= 0)
                newBlocks[i] |= blocks[srcIndex - 1] >> (B - bitShift);
        }
        blocks.swap(newBlocks);
        int extra = (int)blocks.size() * B - sz;
        if (extra > 0) {
            ubig mask = ~0ULL >> extra;
            blocks.back() &= mask;
        }
        return *this;
    }
    BITSET operator<<(int shift) const {
        BITSET res(*this);
        res <<= shift;
        return res;
    }
    BITSET& operator>>=(int shift) {
        if (shift >= sz) {
            fill(blocks.begin(), blocks.end(), 0ULL);
            return *this;
        }
        const int B = 8 * (int)sizeof(ubig);
        int blockShift = shift / B;
        int bitShift = shift % B;
        int nblocks = blocks.size();
        vector<ubig> newBlocks(nblocks, 0ULL);
        for (int i = 0; i < nblocks; i++) {
            int srcIndex = i + blockShift;
            if (srcIndex >= nblocks) continue;
            newBlocks[i] |= blocks[srcIndex] >> bitShift;
            if (bitShift > 0 && srcIndex + 1 < nblocks)
                newBlocks[i] |= blocks[srcIndex + 1] << (B - bitShift);
        }
        blocks.swap(newBlocks);
        int extra = (int)blocks.size() * B - sz;
        if (extra > 0) {
            ubig mask = ~0ULL >> extra;
            blocks.back() &= mask;
        }
        return *this;
    }
    BITSET operator>>(int shift) const {
        BITSET res(*this);
        res >>= shift;
        return res;
    }

    int find_first() const {
        const int B = 8 * (int)sizeof(ubig);
        for (size_t b = 0; b < blocks.size(); b++) {
            if (blocks[b] != 0ULL) {
                int tz = __builtin_ctzll(blocks[b]);
                int pos = b * B + tz;
                if (pos < sz)
                    return pos;
                else
                    return -1;
            }
        }
        return -1;
    }
    int find_prev_set_bit(int pos) const {
        if(pos < 0) return -1;
        if(pos >= sz) pos = sz - 1;
        if(test(pos)) return pos;
        const int B = 8 * (int)sizeof(ubig);
        int block = pos / B, offset = pos % B;
        for (int b = block; b >= 0; b--) {
            ubig mask = (b == block) ? ((1ULL << offset) - 1ULL) : ~0ULL;
            ubig curr = blocks[b] & mask;
            if (curr != 0ULL) {
                int lz = __builtin_clzll(curr);
                return b * B + (B - 1 - lz);
            }
        }
        return -1;
    }
    int find_next_set_bit(int pos) const {
        if(pos < 0) pos = 0;
        if(pos < sz && test(pos)) return pos;
        const int B = 8 * (int)sizeof(ubig);
        int block = pos / B, offset = pos % B;
        ubig mask = ~((1ULL << (offset + 1)) - 1ULL);
        ubig curr = blocks[block] & mask;
        if(curr != 0ULL) {
            int tz = __builtin_ctzll(curr);
            int res = block * B + tz;
            return (res < sz ? res : -1);
        }
        for(size_t b = block + 1; b < blocks.size(); b++) {
            if(blocks[b] != 0ULL) {
                int tz = __builtin_ctzll(blocks[b]);
                int res = b * B + tz;
                return (res < sz ? res : -1);
            }
        }
        return -1;
    }
    bool operator==(const BITSET& other) const {
        return blocks == other.blocks;
    }
    bool operator!=(const BITSET& other) const {
        return !(*this == other);
    }
};

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        string a, b;
        cin >> a >> b;

        vector<BITSET> v(26, BITSET(n));
        for (int i = 0; i < n; i++) {
            v[a[i] - 'a'].set(i);
        }
        int ans = 0;
        for (int i = 0; i < m;) {
            BITSET x = v[b[i] - 'a'];
            BITSET y(n);
            y.set();
            ans++, i++;
            while (i < m) {
                x <<= 1;
                y <<= 1;
                BITSET nx_x = x;
                nx_x &= v[b[i] - 'a'];
                BITSET nx_y = y;
                nx_y &= v[b[i] - 'a'];
                BITSET tmp = x;
                tmp.and_not(v[b[i] - 'a']);
                nx_y |= tmp;
                x.blocks.swap(nx_x.blocks), y.blocks.swap(nx_y.blocks);
                if (!y.any()) {
                    break;
                }
                i++;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
