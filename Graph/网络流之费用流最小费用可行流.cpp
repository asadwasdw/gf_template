#include<bits/stdc++.h>
#define int long long 
using namespace std;
typedef long long ll;
typedef pair<int,int>PII;
const int mod=998244353;
const int INF  = 0x3f3f3f3f3f3f3f3f;
const ll INFll  = 0x3f3f3f3f3f3f3f3f;
#define endl "\n" 
//vector<vector<int>>edg(N);

/*



*/


const int N=1e6 + 10, M = 2e6 + 10; // 随便开， 下面有优化
int S, T, cnt, numS, numT, p, q, n, m;
int h[N], e[M], f[M], w[M], ne[M], idx;
int d[N]; // 到某个点单位流量的最小花费
int pre[N]; // 记录每个点的来路的编号
int incf[N]; // 到每个点的流量
bool st[N];
int F[N]; // 记录到每个点的流量

void add(int a, int b, int c, int d) { // a -> b 容量是c, 单位价格是 d
    // cout << a << " " << b << " " << c << " " << d << endl;
    e[idx] = b, f[idx] = c, w[idx] = d,  ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, w[idx] =-d, ne[idx] = h[b], h[b] = idx ++;
}

bool spfa(int opt) {
    // 0 最小值
    // 1 最大值
    queue<int> q;
    memset(incf, 0, sizeof(int)  * T * 4);
    memset(d, (opt == 0 ? 0x3f : -0x3f), sizeof(int)  * T * 4);
    q.push(S), d[S] = 0, incf[S] = INF;

    while(q.size()) {
        int u = q.front(); q.pop();
        st[u] = false;
        // cout << u << endl;
        for(int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if(f[i] && (opt == 0 ? d[v] > d[u] + w[i] : d[v] < d[u] + w[i])) {
                d[v] = d[u] + w[i];
                incf[v] = min(incf[u], f[i]);
                pre[v] = i;
                if(!st[v]) {
                    st[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return incf[T] > 0;
}

PII EK(int opt) { 
    int flow, cost;
    flow = cost = 0;
    while(spfa(opt)) {
        int t = incf[T]; // 此时流量
        flow += t, cost += t * d[T];
        for(int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
            F[i] += t;
        }
    }
    return {flow , cost};
}

void clear() {
    memset(h, -1, sizeof h);
    idx = 0;
    cnt = 0;
}

int newnode() { return cnt ++; }

vector<int> createNode(int k) {
    vector<int> res;
    while(k --) {
        res.push_back(newnode());
    }
    return res;
}

// 以上是费用流
// 往下是带下界的费用流

struct bound_mcmf {
    int cntv,cnte;
    int from[M],to[M];
	ll lower[M],upper[M];
	ll cost[M];
	ll dflow[M];//入流-出流
    int hash_id[M];

    void adde(int u, int v, ll l, ll r, ll c) {
        // printf("%d->%d [%d,%d] cost=%d\n",u,v,l,r,c);
        cnte++;
        from[cnte] = u, to[cnte] = v, lower[cnte] = l, upper[cnte] = r, cost[cnte] = c;
    }

    ll bound_EK(int opt) {
        cntv = T;
        ll ans = 0;
        adde(T, S, 0, INF, 0);
        S = cntv + 1, T = cntv + 2;
        for(int i = 1; i <= cnte; i ++) {
            add(from[i], to[i], upper[i] - lower[i], cost[i]);
            dflow[from[i]] -= lower[i];
            dflow[to[i]] += lower[i];
            ans += cost[i] * lower[i];
        }

        ll sum = 0;

        for(int i = 1; i <= cntv; i ++) {
            if(dflow[i] < 0) {
                add(i, T, -dflow[i], 0ll);
            }
            else if(dflow[i] > 0ll) {
                add(S, i, dflow[i], 0ll);
                sum += dflow[i]; // 计算理应的最大流量
            }
        }


        PII ANS = EK(0);
 
        if(ANS.first == sum) {
            ans += ANS.second;
            f[idx - 1] = f[idx - 2] = 0; // 删除最后一条边  暂时不知道有什么用
            return ans;
        }
        else return -1;
    }

}bound_mcmf;

int id[N][2];
int a[N];

void solve()
{
    cin >> n >> m;
    S = newnode();
    for(int i = 1; i <= n; i ++) {
        id[i][0] = newnode();
        id[i][1] = newnode();
        if(i <= n)cin >> a[i];
    }
    T = newnode(); 

    // 如果是一个有源汇的，就要连接S - >T
    // bound_mcmf.adde(S, id[1][0],0, INF, 0); // 无源汇不能建边
    // bound_mcmf.adde(id[n][1], T,0, INF, 0);

    // 24.7.22 发现ST实际上并不重要， 只是用来限制一个总的流量，可以认为是原图中普通的一个点。如果跑出来的流量不是理应的流量，那么可能写错了
    
    for(int i = 1; i <= n; i ++) {
        if(i + 1 <= n) bound_mcmf.adde(id[i][1], id[i + 1][0], 0, INF, 0);
        bound_mcmf.adde(id[i][0], id[i][1], a[i], INF, 0);
    }

    while(m --) {
        int u , v, w;
        cin >> u >> v >> w;
        bound_mcmf.adde(id[v][1], id[u][0], 0, INF, w);
    }

    cout << bound_mcmf.bound_EK(0) << endl;
}


signed main()
{
    clear();
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout << setprecision(11) << fixed;
    int t;t=1;
    //cin>>t;
    for(int i=1;i<=t;i++){
        //printf("Case %d: ",i);
        solve();
    }
}