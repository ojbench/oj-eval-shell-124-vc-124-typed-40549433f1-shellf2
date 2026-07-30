#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n = 0;
    vector<long long> mn, lazy;

    void init(int n_, long long v) {
        n = n_;
        mn.assign(n * 4 + 5, v);
        lazy.assign(n * 4 + 5, 0);
    }

    inline void apply(int p, long long v) {
        mn[p] += v;
        lazy[p] += v;
    }

    inline void push(int p) {
        long long v = lazy[p];
        if (v != 0) {
            apply(p << 1, v);
            apply(p << 1 | 1, v);
            lazy[p] = 0;
        }
    }

    inline void pull(int p) {
        mn[p] = min(mn[p << 1], mn[p << 1 | 1]);
    }

    void add(int p, int l, int r, int ql, int qr, long long v) {
        if (ql <= l && r <= qr) {
            apply(p, v);
            return;
        }
        push(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) add(p << 1, l, mid, ql, qr, v);
        if (qr > mid) add(p << 1 | 1, mid + 1, r, ql, qr, v);
        pull(p);
    }

    long long queryMin(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return mn[p];
        push(p);
        int mid = (l + r) >> 1;
        long long res = LLONG_MAX;
        if (ql <= mid) res = min(res, queryMin(p << 1, l, mid, ql, qr));
        if (qr > mid) res = min(res, queryMin(p << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
};

int main() {
    int x = 0, p = 0;
    long long k = 0;
    if (scanf("%d%lld%d", &x, &k, &p) != 3) return 0;

    const int edges = max(0, x - 1);
    SegTree st;
    if (edges > 0) st.init(edges, k);

    string out;
    out.reserve((size_t)p * 2);

    for (int i = 0; i < p; ++i) {
        int u = 0, v = 0;
        long long n = 0;
        if (scanf("%d%d%lld", &u, &v, &n) != 3) return 0;

        if (u > v) swap(u, v);

        if (edges == 0 || u == v) {
            out.push_back('T');
            out.push_back('\n');
            continue;
        }

        int l = max(1, u);
        int r = min(edges, v - 1);
        if (l > r) {
            out.push_back('T');
            out.push_back('\n');
            continue;
        }

        if (st.queryMin(1, 1, edges, l, r) >= n) {
            st.add(1, 1, edges, l, r, -n);
            out.push_back('T');
        } else {
            out.push_back('N');
        }
        out.push_back('\n');
    }

    fputs(out.c_str(), stdout);
    return 0;
}
