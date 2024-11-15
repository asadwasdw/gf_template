#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
typedef pair<int,int>PII;
const int N=1e6+10;
const int mod=998244353;
const int INF  = 0x3f3f3f3f;
const ll INFll  = 0x3f3f3f3f3f3f3f3f;
#define endl "\n" 
#define x first
#define y second

//vector<vector<int>>adj(N);

int dp[N];
int a[N], w[N];

void solve()
{
    int n; 
    cin >> n;
    map<int,int> mp;
    for(int i = 1; i <= n; i ++) {
        cin >> a[i];
        if(a[i] == a[i - 1]) w[i] = a[i];
        else w[i] = 0;
        w[i] += w[i - 1];
    }

    for(int i = 1; i <= n; i ++) {
        dp[i] = dp[i - 1];
        if(mp[a[i]]) {
            dp[i] = max(dp[i],dp[mp[a[i]] + 1] + a[i] + w[i] - w[mp[a[i]]+ 1]);
        }
        mp[a[i]] = i;
    }

    cout << dp[n] << endl;
}


signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout << setprecision(11) << fixed;
    int t;t=1;
    cin>>t;
    for(int i=1;i<=t;i++){
        //printf("Case %d: ",i);
        solve();
    }
}