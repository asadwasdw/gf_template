struct gfDSU {
    int n;
    vector<int> f, sz;

    void init(int _n) {
        n = _n;
        f.resize(n + 1);
        sz.resize(n + 1);
        for(int i = 0; i <= n; i ++) f[i] = i, sz[i] = 1;
    }

    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return;
        sz[y] += sz[x];
        f[x] = y;
    }
    void debug() {
        for(int i = 0; i <= n; i ++) cout << f[i] << " \n"[i == n];
        for(int i = 0; i <= n; i ++) cout << sz[i] << " \n"[i == n];
    }
}dsu;
