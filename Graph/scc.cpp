vector<vector<int>>adj(N);
int dfn[N], low[N], dfncnt, in_s[N], in[N];
stack<int>s;
int scc[N], sc, sz[N];

void tarjan(int u) {
    low[u] = dfn[u] = ++dfncnt;
    s.push(u), in_s[u] = 1;

    for(auto v : adj[u]) {
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(in_s[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if(dfn[u] == low[u]) {
        ++sc;
        while(s.top() != u) {
            scc[s.top()] = sc;
            sz[sc] ++;
            in_s[s.top()] = 0;
            s.pop();
        }

        scc[s.top()] = sc;
        sz[sc] ++;
        in_s[s.top()] = 0;
        s.pop();
    }
}
