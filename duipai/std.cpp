#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr)
#define rep(i, j, k) for(int i = j; i <= k; ++i)
#define pre(i, j, k) for(int i = j; i >= k; --i)
#define PII pair<int, int>
#define fi first
#define se second
#define inf 0x3fffffff

using namespace std;

const int N = 1e5 + 5;
const double eps = 1e-8;

struct Cars {
	double d, v, a;
	#define d(p) b[p].d
	#define v(p) b[p].v
	#define a(p) b[p].a
} b[N];

struct node {
	double l, r;
	#define l(p) c[p].l
	#define r(p) c[p].r
	
	bool operator < (const node &a) const {return r == a.r ? l < a.l : r < a.r;}
} c[N];

int n, m, res;
double L, V, p[N];

void init() {
	res = 0;
//	cin >> n >> m >> L >> V;
	scanf("%d %d %lf %lf", &n, &m, &L, &V);
	rep(i, 1, n) scanf("%lf %lf %lf", &d(i), &v(i), &a(i)), l(i) = r(i) = -1;
	rep(i, 1, m) scanf("%lf", &p[i]);
}




void sol() {
	init(); 
	rep(i, 1, n) {
		if(a(i) == 0) {
//			cout << i << '\n';
			if(v(i) > V) l(i) = d(i), r(i) = L;
		}
		else if(a(i) > 0) {
			if(v(i) > V) l(i) = d(i), r(i) = L;
			else {
				double lt = V - v(i);
				double t = lt / a(i);
				double sum = v(i) * t + 0.5 * a(i) * t * t;
				l(i) = d(i) + sum + eps, r(i) = L;
			}
		}
		else if(a(i) < 0) {
			if(v(i) > V) {
//				cout << i << ' ';
				a(i) = fabs(a(i));
				double lmt = v(i) / a(i);
				double lms = 0.5 * a(i) * lmt * lmt;
				
				double lt = V;
				double t = lt / a(i);
				double sum = 0.5 * a(i) * t * t;
				l(i) = d(i), r(i) = d(i) + (lms - sum) - eps;
			}
		}
	}
//	cerr<<1;
//	return;
//	exit(0);
	
	int tot = n; n = 0;
	rep(i, 1, tot) {
//		printf("%.3lf %.3lf\n", d(i), r(i));
		if(l(i) > r(i) || (l(i) == r(i) && r(i) == -1)) continue;
		int id = lower_bound(p + 1, p + 1 + m, l(i)) - p;
		if(id == m + 1) continue;
		if(p[id] > r(i)) continue;
		++n;
		l(n) = l(i), r(n) = r(i); r(n) = min(r(n), L);
	}
	
//	cout << n << ' '; 
	printf("%d ", n);
	if(n == 0) return printf("%d\n", m), void();
	sort(c + 1, c + 1 + n);
//	rep(i, 1, n) printf("%.3lf %.3lf\n", l(i), r(i));
	int id = upper_bound(p + 1, p + 1 + m, r(1)) - p - 1;
	double pos = p[id];
//	cout << pos << '\n';
	rep(i, 2, n) {
		if(l(i) <= pos && pos <= r(i)) continue;
		else {
			id = upper_bound(p + 1, p + 1 + m, r(i)) - p - 1;
			pos = p[id];
//			cout << i << ' ' << pos << '\n';
			++res;
		}
	}
	printf("%d\n", m - res - 1);
//	cout << m - res - 1;
//	cout << '\n';
//	exit(0);
}


signed main() {
//	FASTIO;
	
// 	freopen("detect.in", "r", stdin);
// 	freopen("detect.out", "w", stdout); 
	
	int _; cin >> _;
	while(_--) sol();
	
	
	
	return 0;
}