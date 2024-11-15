struct gfBIT {
    int n;
    vector<int> tr;

    void clear() {
        tr.clear();
        tr.resize(n + 10, 0); 
    }

    void init(int _n) {
        n = _n;
        clear();
    }

    int lowbit(int x) {
        return (x) & (-x);
    }

    void update(int x, int d) {
        for(int i = x; i <= n; i += lowbit(i)) tr[i] += d;
    }

    ll sum(int x) {
        ll ans = 0;
        for(int i = x; i > 0; i -= lowbit(i)) ans += tr[i];
        return ans;
    }

    ll get(int l, int r) {
        return sum(r) - sum(max(0,l - 1));
    }

    void debug() {
        cout << n << endl;
        for(int i = 1; i <= n; i ++) {
            cout << get(i, i) << " \n"[i == n];
        }
    }
}bit;
