struct gfLCA {
    int n, now, cur, tot;
    vector<array<int, 20>> fa, rev; 
    // int fa[N][20];
    vector<int> deep; 
    vector<int> dfn, fdfn, L, R, FL;
    vector<int> lg, depth; // RMQ

    void clear() {
        tot = now = 0;

        fa.resize(n + 10); // 重新设置向量的大小为 n
        fill(fa.begin(), fa.end(), array<int, 20>{0}); // 将所有元素初始化为 0

        rev.resize(2 * n + 10); 
        fill(rev.begin(), rev.end(), array<int, 20>{0}); 

        deep.resize(n + 10, 0);
        L.resize(n + 10, 0);
        FL.resize(n + 10, 0);
        R.resize(n + 10, 0);

        fdfn.resize(n + 10, 0);

        dfn.resize(2 * n + 10, 0);
        lg.resize(2 * n + 10, 0);
        depth.resize(2 * n + 10, 0);
    }

    void dfs(int u, int father) {
        L[u] = ++now;
        FL[L[u]] = u;

        dfn[++tot] = L[u];
        fdfn[u] = tot; 

        depth[tot] = deep[u] = deep[father] + 1;
        fa[u][0] = father;
        for(int i = 1; (1 << i) <= deep[u]; i ++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for(int v : adj[u]) {
            if(v == father) continue;
            dfs(v, u);
            dfn[++tot] = L[u];
            depth[tot] = deep[father] + 1;
        }
        R[u] = now;
    }

    void init(int _n, int root) {
        n = _n;
        clear();
        dfs(root, 0);
        for(int i = 2; i <= tot + 1; i ++) lg[i] = lg[i >> 1] + 1;
        for(int i = 1; i <= tot; i ++) rev[i][0] = dfn[i];
        for(int j = 1; j <= lg[tot]; j ++) {
            for(int i = 1; i + (1 << j) - 1 <= tot; i ++) {
                rev[i][j] = min(rev[i][j - 1], rev[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int LCA(int x, int y) {
        if(deep[x] < deep[y]) swap(x, y);
        for(int i = 19; i >= 0; i --) {
            if(deep[x] - (1 << i) >= deep[y])
                x = fa[x][i];
        }
        if(x == y) return x;
        for(int i = 19; i >= 0; i --) {
            if(fa[x][i] != fa[y][i]){
                x = fa[x][i];
                y = fa[y][i];
            }
        }
        return fa[x][0];
    }

    int RMQ(int l, int r) {
        l = fdfn[l], r = fdfn[r];
        if(l > r) swap(l, r);
        int k = lg[r - l + 1]; 
        int root = min(rev[l][k], rev[r - (1 << k) + 1][k]);
        root = FL[root];
        return root;
    }

    int len(int x, int y) {
        return deep[x] + deep[y] - 2 * deep[LCA(x, y)];
    }

    void debug() {
        // for(int i = 1; i <= n; i ++) cout << fa[i][0] << " \n"[i == n]; 
        // for(int i = 1; i <= n; i ++)   cout << L[i] << " \n"[i == n];
        for(int i = 1; i <= tot; i ++) cout << dfn[i] << " \n"[i == tot];
        for(int i = 1; i <= tot; i ++) cout << rev[i][1] << " \n"[i == tot];
    }
}lca;