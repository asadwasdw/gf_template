
const int N = 400 * 1200 + 10, M = 1e7 + 10;
int n, m, S, T;
int idx, h[N], ne[M], e[M], f[M], w[M];
bool vis[N];
int dis[N], cur[N];

void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, w[idx] =-d, ne[idx] = h[b], h[b] = idx ++;
}

bool SPFA(void) //用 SPFA 代替 BFS
{
    queue<int> q;
    memset(dis, 0x3f, sizeof dis);
    q.emplace(S);
    dis[S] = 0;
    cur[S] = h[S];
    while (q.size()) {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (f[i] && dis[v] > dis[u] + w[i]) {
                dis[v] = dis[u] + w[i];
                cur[v] = h[v];
                if (!vis[v]) {
                    vis[v] = 1;
                    q.emplace(v);
                }
            }
        }
    }
    return dis[T] != 0x3f3f3f3f;
}
int find(int u, int limit, int &cost)
{
    if (u == T) {
        cost += dis[T] * limit;
        return limit;
    }
    vis[u] = 1; //特判
    int flow = 0;
    for (int i = cur[u]; flow < limit && ~i; i = ne[i]){
        int v = e[i];
        // 最短路分层图
        if (f[i] && dis[v] == dis[u] + w[i] && !vis[v]) { //还是这个特判，并且求的增广路必须同时是最短路
            cur[u] = i;
            int t = find(v, min(f[i], limit - flow), cost);
            if (!t) dis[v] = INF;
            flow += t, f[i] -= t, f[i ^ 1] += t;
        }
    }
    vis[u] = 0;
    return flow;
}
int flow, cost;
int dinic()
{
    flow = 0, cost = 0;
    while (SPFA())
        flow += find(S, INF, cost);
    return 0;
}